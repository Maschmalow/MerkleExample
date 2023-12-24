

add_executable(merkleCLI)
target_sources(merkleCLI
        PRIVATE
        src/main.cpp
        PUBLIC
        include/MerkleCLI/main.hpp
        )

target_include_directories(merkleCLI PRIVATE include SYSTEM INTERFACE include)
target_compile_features(merkleCLI PRIVATE cxx_std_20)
target_compile_options(merkleCLI PRIVATE -Wall -Wextra -Wconversion -g3 -ggdb3)
target_link_libraries(merkleCLI PUBLIC merklelib  Boost::program_options)