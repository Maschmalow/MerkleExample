

# Class merkle::MerkleMembershipProof



[**ClassList**](annotated.md) **>** [**merkle**](namespacemerkle.md) **>** [**MerkleMembershipProof**](classmerkle_1_1_merkle_membership_proof.md)



_Class holding a membership proof._ 

* `#include <merkle.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**NodeChoice**](#enum-nodechoice)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**MerkleMembershipProof**](#function-merklemembershipproof) () = default<br> |
|  void | [**append**](#function-append) ([**Hash**](namespacemerkle.md#typedef-hash) h, [**NodeChoice**](classmerkle_1_1_merkle_membership_proof.md#enum-nodechoice) c) <br> |
|  bool | [**verify**](#function-verify) ([**Hash**](namespacemerkle.md#typedef-hash) root, const T & elem) const<br> |




























## Public Types Documentation




### enum NodeChoice 

```C++
enum merkle::MerkleMembershipProof::NodeChoice {
    LEFT,
    RIGHT
};
```



## Public Functions Documentation




### function MerkleMembershipProof 

```C++
merkle::MerkleMembershipProof::MerkleMembershipProof () = default
```






### function append 

```C++
inline void merkle::MerkleMembershipProof::append (
    Hash h,
    NodeChoice c
) 
```






### function verify 


```C++
template<class T class T>
inline bool merkle::MerkleMembershipProof::verify (
    Hash root,
    const T & elem
) const
```



return true iff this class instance is a valid membership proof for `elem` against the set digest `root` 


        

------------------------------
The documentation for this class was generated from the following file `MerkleLib/include/merklelib/merkle.hpp`

