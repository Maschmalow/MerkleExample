

# Class merkle::Hasher



[**ClassList**](annotated.md) **>** [**merkle**](namespacemerkle.md) **>** [**Hasher**](classmerkle_1_1_hasher.md)



_SHA256 instance._ [More...](#detailed-description)

* `#include <crypto.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Hasher**](#function-hasher) () = default<br> |
|  [**Hash**](namespacemerkle.md#typedef-hash) | [**end**](#function-end) () <br> |
|  [**Hasher**](classmerkle_1_1_hasher.md) & | [**input**](#function-input-14) (const T & in) <br> |
|  [**Hasher**](classmerkle_1_1_hasher.md) & | [**input**](#function-input-14) (const T & in) <br> |
|  [**Hasher**](classmerkle_1_1_hasher.md) & | [**input**](#function-input-34) (const T & in) <br> |
|  [**Hasher**](classmerkle_1_1_hasher.md) & | [**input**](#function-input-14) (const T & in) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Hash**](namespacemerkle.md#typedef-hash) | [**apply**](#function-apply) (const TArgs &... ins) <br> |


























# Detailed Description


A [**Hasher**](classmerkle_1_1_hasher.md) instance holds the state of the hash function. Use [**input()**](classmerkle_1_1_hasher.md#function-input-14) to feed data to the hash function and [**end()**](classmerkle_1_1_hasher.md#function-end) to get the hash. The hash can also be directly computed using the static member [**apply()**](classmerkle_1_1_hasher.md#function-apply). 


    
## Public Functions Documentation




### function Hasher 

```C++
merkle::Hasher::Hasher () = default
```






### function end 


```C++
inline Hash merkle::Hasher::end () 
```



End the hash inputs and return the hash value. 


        



### function input [1/4]


```C++
template<directlyHashable T>
inline Hasher & merkle::Hasher::input (
    const T & in
) 
```



arithmetic type are [**directlyHashable**](interfacedirectly_hashable.md) using the sizeof() operator. 


        



### function input [1/4]


```C++
template<contiguous_hashable T>
inline Hasher & merkle::Hasher::input (
    const T & in
) 
```



The hashing of a contiguous array of directlyHashable elements ([**contiguous\_hashable**](interfacecontiguous__hashable.md)) is done in a single call to the underlying hash function. 


        



### function input [3/4]


```C++
template<iterable T>
inline Hasher & merkle::Hasher::input (
    const T & in
) 
```



Anything [**iterable**](interfaceiterable.md) (excluding contiguous arrays of directlyHashable elements) is hashed element by element. 


        



### function input [1/4]


```C++
template<derived_hashable T>
inline Hasher & merkle::Hasher::input (
    const T & in
) 
```



A [**derived\_hashable**](interfacederived__hashable.md) instance calls its addToHash() member function. 


        
## Public Static Functions Documentation




### function apply 


```C++
template<class... TArgs>
static inline Hash merkle::Hasher::apply (
    const TArgs &... ins
) 
```



Static function to hash values in one call. Generates one call to the underlying hash function per input argument. 


        

------------------------------
The documentation for this class was generated from the following file `MerkleLib/include/merklelib/crypto.hpp`

