# boost.serialization.demo

Experimenting with Boost.Serialization.
- split save/load
- polymorphic hierarchy
- tracking level
  - custom primitive types
- export

The output of the project is the program `demo` which has some option `demo --help` to write/read binary or xml archives.

# Building

Note: Requires C++17 to build. 

## MacOS

- The project makes use of Boost as provided by [Homebrew](https://brew.sh)
- Use either CMake or the Xcode project to build.

### CMake
````sh
> cd boost.serialization.demo
> mkdir Build
> cd Build
> cmake ..
> make -j
````
