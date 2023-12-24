


add_library(merklelib STATIC)
target_sources(merklelib
        PRIVATE
        src/merkle.cpp
        PUBLIC
        include/merklelib/merkle.hpp
        )


target_include_directories(merklelib PRIVATE include SYSTEM INTERFACE include)

target_link_libraries(merklelib PUBLIC cryptopp-static )
target_compile_features(merklelib PRIVATE cxx_std_20)
target_compile_options(merklelib PRIVATE -Wall -Wextra -Wconversion)
