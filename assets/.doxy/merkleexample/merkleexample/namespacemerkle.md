

# Namespace merkle



[**Namespace List**](namespaces.md) **>** [**merkle**](namespacemerkle.md)



[More...](#detailed-description)
















## Classes

| Type | Name |
| ---: | :--- |
| class | [**Hashable**](classmerkle_1_1_hashable.md) <br>_Inherit this class and implement addToHash() to define hashing of a custom class._  |
| class | [**Hasher**](classmerkle_1_1_hasher.md) <br>_SHA256 instance._  |
| class | [**MerkleMembershipProof**](classmerkle_1_1_merkle_membership_proof.md) <br>_Class holding a membership proof._  |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::array&lt; CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE &gt; | [**Hash**](#typedef-hash)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  [**Hash**](namespacemerkle.md#typedef-hash) | [**computeMerkleRoot**](#function-computemerkleroot) (T && leaves, const P proofs) <br>_Compute a Merkle Tree root (with proof iterator). Computes the root of the Merkle tree containing all_ `leaves` _and populates the__pre-allocated_ _container_`proofs` _with the corresponding membership proofs._ |
|  [**Hash**](namespacemerkle.md#typedef-hash) | [**computeMerkleRoot**](#function-computemerkleroot) (T && leaves, P & proofs) <br>_Compute a Merkle Tree root (with proof container). Computes the root of the Merkle tree containing all_ `leaves` _and populates_`proofs` _with the corresponding membership proofs._ |




























# Detailed Description


Project namespace


Main namespace 


    
## Public Types Documentation




### typedef Hash 

```C++
using merkle::Hash =  std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE>;
```



## Public Functions Documentation




### function computeMerkleRoot 

_Compute a Merkle Tree root (with proof iterator). Computes the root of the Merkle tree containing all_ `leaves` _and populates the__pre-allocated_ _container_`proofs` _with the corresponding membership proofs._
```C++
template<std::ranges::forward_range T, std::forward_iterator P>
Hash merkle::computeMerkleRoot (
    T && leaves,
    const P proofs
) 
```





**Parameters:**


* `leaves` range containing the set to be hashed. 
* `proofs` iterator to the container to be filled with membership proofs. _MUST_ be allocated with leaves.size() elements. 



**Returns:**

the root of the merkle tree 





        



### function computeMerkleRoot 

_Compute a Merkle Tree root (with proof container). Computes the root of the Merkle tree containing all_ `leaves` _and populates_`proofs` _with the corresponding membership proofs._
```C++
template<std::ranges::forward_range T, class P class P>
Hash merkle::computeMerkleRoot (
    T && leaves,
    P & proofs
) 
```





**Parameters:**


* `leaves` array containing the set to be hashed. 
* `proofs` container to be filled with membership proofs. Will be reallocated before filling. 



**Returns:**

the root of the merkle tree 





        

------------------------------
The documentation for this class was generated from the following file `MerkleLib/include/merklelib/crypto.hpp`

