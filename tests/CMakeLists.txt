

add_executable(tests )
target_sources(tests
        PRIVATE
        main.cpp
        tests.cpp
        )


target_compile_features(tests PRIVATE cxx_std_20 )
add_compile_options(-fconcepts-diagnostics-depth=20)

target_link_libraries(tests PRIVATE merklelib Catch2::Catch2 )

