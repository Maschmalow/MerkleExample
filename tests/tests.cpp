#include <catch2/catch.hpp>
#include <merklelib/merkle.hpp>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>


/**
 * Test
 */
TEST_CASE("test validity", "[merkle]") {

    for(uint32_t n =1; n<200; n++) {
        std::vector<std::int32_t> leaves(n);
        std::iota(leaves.begin(), leaves.end(), n);
        std::vector<merkle::MerkleMembershipProof> proofs;
        merkle::Hash root = merkle::computeMerkleRoot(leaves, proofs);
        for (auto i = 0; i < proofs.size(); i++)
            REQUIRE(proofs[i].verify(root, leaves[i]));
    }



}


merkle::Hash fromHexString(const std::string &source) {
    merkle::Hash ret;
    CryptoPP::StringSource(
            source, true,
            new CryptoPP::HexDecoder(new CryptoPP::ArraySink(ret.data(), ret.size())));

    return ret;
}


/**
 * Testing  concepts evaluation. This is mainly to prevent regression bugs.
 */
class ComplexClass : public merkle::Hashable {
public:
    std::vector<int> a;
    std::array<int, 3> b;
    std::deque<int> c;

    void addToHash(merkle::Hasher &hasher) const {
        hasher.input(a);
        hasher.input(b);
        hasher.input(c);
    }

    ComplexClass(const std::vector<int> &a, const std::array<int, 3> &b, const std::deque<int> &c) : a(a), b(b), c(c) {}
};


/*
 * All hash values except the one from ComplexClass have been computed using a third-party SHA256 implementation.
 */
TEST_CASE("test hashing", "[merkle]") {

    REQUIRE(merkle::Hasher::apply(std::string("The Blockhouse Technology Ltd. is a great company")) ==
            fromHexString("ab8c875b662e3b1d85318d9fbcda47f5cd6a02fa814a2ef991d65b637c392140"));
    REQUIRE(merkle::Hasher::apply(std::string()) ==
            fromHexString("e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"));
    REQUIRE(merkle::Hasher::apply(std::string(
            "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore "
            "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut "
            "aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum "
            "dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui "
            "officia deserunt mollit anim id est laborum.")) ==
            fromHexString("2d8c2f6d978ca21712b5f6de36c9d31fa8e96a4fa5d8ff8b0188dfb9e7c171bb"));
    REQUIRE(merkle::Hasher::apply(ComplexClass{
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8}
    }) == fromHexString("921c803abfa6ac88f44f7ab19198e5c137d1c7183e8e6912757a6263e8dee0a5"));
    REQUIRE(merkle::Hasher::apply(std::string("1"), std::string("1"), std::string("1"), std::string("1")) ==
            merkle::Hasher::apply(std::string("1111")));
    REQUIRE(merkle::Hasher::apply(std::string("1111")) ==
            fromHexString("0ffe1abd1a08215353c233d6e009613e95eec4253832a761af28ff37ac5a150c"));

}
