#pragma once
/** @file
 * @brief Merkle tree related functions and classes
 */

#include <numeric>
#include "merklelib/crypto.hpp"




/**
 *  MerkleLib namespace
 */
namespace merkle {


    /**
     * @brief Class holding a membership proof.
     */
    class MerkleMembershipProof {
    public:
        enum class NodeChoice {
            LEFT, RIGHT
        };

        MerkleMembershipProof() = default;

        void append(Hash h, NodeChoice c) {
            path.push_back({.value=h, .side=c});
        }

        /**
         * Return true iff this class instance is a valid membership proof for \p elem against the set digest \p root.
         */
        template<class T>
        bool verify(Hash root, const T& elem) const {

            auto recomputePath = [](const Hash& acc, const NodeHash& proof) -> Hash {
                if (proof.side == NodeChoice::RIGHT) // the hash value in path is on the right
                    return Hasher().input(acc).input(proof.value).end();
                else //currentNode.second == NodeChoice::LEFT
                    return Hasher().input(proof.value).input(acc).end();
            };

            return std::accumulate(path.begin(), path.end(), Hasher::apply(elem), recomputePath) == root;
        }

    private:
        struct NodeHash {
            Hash value;
            NodeChoice side;
        };

        std::vector<NodeHash> path;
    };


    /**
     * @brief Compute a Merkle Tree root (with proof iterator).
     * Computes the root of the Merkle tree containing all \p leaves and populates the *pre-allocated* container \p proofs with the corresponding membership proofs.
     * @param leaves range containing the set to be hashed.
     * @param proofs iterator to the container to be filled with membership proofs. *MUST* be allocated with leaves.size() elements.
     * @return the root of the merkle tree
     */
    template<std::ranges::forward_range T, std::forward_iterator P>
    requires std::same_as<MerkleMembershipProof, typename std::iterator_traits<P>::value_type>
    Hash computeMerkleRoot(T&& leaves, const P proofs) {
        const auto& begin = std::ranges::begin(leaves), end = std::ranges::end(leaves); //mostly for readability

        if (std::ranges::size(leaves) == 1) {
            return Hasher::apply(*begin);
        }

        // note that there is no *explicit* requirement in std::random_access_iterator<> to support division on iter_diff (which midpoint does).
        // But there are other parts, eg., in std::lower_bound() where this is done *and* random_access_iterator guarantees constant time operation.
        auto middle = begin + (end - begin) / 2;

        Hash left = computeMerkleRoot(std::ranges::subrange(begin, middle), proofs);
        Hash right = computeMerkleRoot(std::ranges::subrange(middle, end), proofs + (middle - begin));

        P it = proofs;
        for (auto i = begin; i < middle; i++) {
            it->append(right, MerkleMembershipProof::NodeChoice::RIGHT);
            it++;
        }
        for (auto i = middle; i < end; i++) {
            it->append(left, MerkleMembershipProof::NodeChoice::LEFT);
            it++;
        }

        return Hasher().input(left).input(right).end();
    }


    /**
     * @brief Compute a Merkle Tree root (with proof container).
     * Computes the root of the Merkle tree containing all \p leaves and populates \p proofs with the corresponding membership proofs.
     * @param leaves array containing the set to be hashed.
     * @param proofs container to be filled with membership proofs. Will be reallocated before filling.
     * @return the root of the merkle tree
     */
    template<std::ranges::forward_range T, class P>
        requires std::forward_iterator<std::ranges::iterator_t<P>>
    Hash computeMerkleRoot(T&& leaves, P& proofs) {
        proofs = P(leaves.size());
        return computeMerkleRoot(leaves, proofs.begin());
    }


}

