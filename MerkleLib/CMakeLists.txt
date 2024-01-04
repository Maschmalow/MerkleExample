


add_library(merklelib STATIC)
target_sources(merklelib
        PUBLIC
        include/merklelib/merkle.hpp
        include/merklelib/crypto.hpp
        )


target_compile_options(merklelib PUBLIC -fconcepts-diagnostics-depth=20)
target_include_directories(merklelib PRIVATE include SYSTEM INTERFACE include)

target_link_libraries(merklelib PUBLIC cryptopp )
target_compile_features(merklelib PRIVATE cxx_std_20)
target_compile_options(merklelib PRIVATE -Wall -Wextra -Wconversion)
