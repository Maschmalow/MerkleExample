# Welcome to MerkleExample

Please note that this is a somewhat over-engineered example project, meaning that this code tends to trade readability
for convenience.

## Architecture

This library is header-only, which is required anyway because almost all the code is templated.
All the code is in the namespace [merkle](merkleexample/namespacemerkle.md)

- [crypto.hpp](merkleexample/crypto_8hpp.md) contains all crypto related code, in this case a wrapper
  around cryptopp hashing.
- [merkle.hpp](merkleexample/merkle_8hpp.md) contains the code to compute Merkle trees and verify membership proofs.

## Usage

### Merkle algorithms

The main algorithm to compute the root of a Merkle tree is [computeMerkleRoot()](merkleexample/namespacemerkle.md#public-functions). This algorithm requires an output
container to receive the [MerkleMembershipProof](merkleexample/classmerkle_1_1_merkle_membership_proof.md) for all elements.

```C++
  std::vector<int> leaves{ 0, 1, 2 };
  std::vector<MerkleMembershipProof> proofs;
  Hash root = computeMerkleRoot(leaves, proofs);
```

Then the `i`th proof for the `i`th element can be verified like so:

```C++
  proofs[i].verify(root, leaves[i]);
```

Note that adding an element to the input set will change its root and invalidate all membership proof, thus in a typical
usage scenario all the membership proofs will be needed right after computing the root. 

If the memory usage is too high, it would be possible to trade speed for memory by iterating all the tree nodes and outputting the proofs one at a time. 
This alternative would also support the use case where only some of the membership proofs are needed.

### Cryptographic operations

To obtain a [Hash](merkleexample/classmerkle_1_1_hash.md) from an object, use :

```C++
  // if all objects to be hashed are known upfront.
  Hasher::apply(obj1, obj2, ...);
  // if the state of the hash function needs to be kept around.
  Hasher h = Hasher();
  h.input(obj);
  Hash ret = h.end();
```

[Hasher](merkleexample/classmerkle_1_1_hasher.md) can hash any arithmetic type (`int`, `char`, etc) and array thereof in
a single call to the underlying hash function. Non-contiguous containers require one call per element. Additionally,
user-defined classes can support being hashed by inheriting [Hashable](merkleexample/classmerkle_1_1_hashable.md) and
implementing `void addToHash(Hasher& in) const`.

