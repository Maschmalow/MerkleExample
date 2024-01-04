# Example project, Merkle Tree implementation

## Build

The project is build with CMake, external dependencies are kept as git submodules.
To clone this repo with the submodule, run `git clone --recurse-submodules git@github.com:Maschmalow/StakeCube.git`.
If the repository is already cloned, run `git submodule update --init --recursive` to pull the submodules.

CMake usage, at root directory:  
`cmake -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" .`  
Replace `Unix Makefiles` according to your build system. Then run `cmake --build <build_dir> --target <target>`

The targets can be `tests` or`MerkleLib`.

The documentation can be built locally with MkDocs. To do so, install Mkdocs, its plugin Mkdoxy 
(and doxygen as well if you don't already have it), and run `mkdocs serve` to build the site and serve it locally.


## Documentation

See [MerkleExample.github.io](https://MerkleExample.github.io) for the online documentation. Alternatively, you can directly browse
the markdown documentation ins [docs/index.md](docs/index.md).

 - [docs](docs) contains the documentation.
 - [external](external) all external dependencies, ie, boost, Catch2 and cryptopp.
 - [MerkleLib](MerkleLib) is the source of this library.
 - [tests](tests) contains the sources for the MerkleLib tests.


## Possible improvements
 * Integrate mkdocs in the build system.
 * Provide a docker build image.
 * Switch to a better build system, eg, bazel.
 * Extend the test suite, update to Catch v3.
 * CI/CD integration. 