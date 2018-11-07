# boost.serialization.demo

Experimenting with Boost.Serialization.
- split save/load
- polymorphic hierarchy
- tracking level
  - custom primitive types
- export

The output of the project is the program `demo` which has some options (see `demo --help`) to write/read binary or xml archives.

# Building

Note: Requires C++17 to build. 

## Linux

- Use [cmake](#building-with-cmake) to build the project.

## MacOS

- The project makes use of Boost as provided by [Homebrew](https://brew.sh)
- Use either [cmake](#building-with-cmake) or included the Xcode project to build.

## Building with CMake
````sh
> cd boost.serialization.demo
> mkdir Build
> cd Build
> cmake ..
> make -j
> ./demo -h # get some help
````
