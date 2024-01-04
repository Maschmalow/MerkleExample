

# File merkle.hpp

[**File List**](files.md) **>** [**include**](dir_e5730d5bb186076c7325630a058c9a00.md) **>** [**merklelib**](dir_5209bc8e00a5022dcb375bc5a32c3450.md) **>** [**merkle.hpp**](merkle_8hpp.md)

[Go to the documentation of this file](merkle_8hpp.md)

```C++

#pragma once
#include <numeric>
#include "merklelib/crypto.hpp"




namespace merkle {


    class MerkleMembershipProof {
    public:
        enum class NodeChoice {
            LEFT, RIGHT
        };

        MerkleMembershipProof() = default;

        void append(Hash h, NodeChoice c) {
            path.push_back({.value=h, .side=c});
        }

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


    template<std::ranges::forward_range T, class P>
    Hash computeMerkleRoot(T&& leaves, P& proofs) {
        proofs = P(leaves.size());
        return computeMerkleRoot(leaves, proofs.begin());
    }


}


```

