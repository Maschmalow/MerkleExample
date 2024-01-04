


add_subdirectory(cryptopp)
#target_compile_options(cryptopp-object PRIVATE -march=native)

set(BOOST_INCLUDE_LIBRARIES program_options)
add_subdirectory(boost EXCLUDE_FROM_ALL)



add_subdirectory(Catch2)