

# Interface derived\_hashable



[**ClassList**](annotated.md) **>** [**derived\_hashable**](interfacederived__hashable.md)



_Concept modelling types supporting hashing though addToHash()._ [More...](#detailed-description)

* `#include <crypto.hpp>`

































































# Detailed Description


We do not use the [**implementsAddToHash**](interfaceimplements_add_to_hash.md) directly because we would risk having external classes inadvertently implementing addToHash in unexpected ways. Other implementations are possible with different trade-offs, eg, CRTP, type tag, virtual class, etc. 


    

------------------------------
The documentation for this class was generated from the following file `MerkleLib/include/merklelib/crypto.hpp`
