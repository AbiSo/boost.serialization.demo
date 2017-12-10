cmake_minimum_required(VERSION 3.9)

project(demo VERSION 1.0 DESCRIPTION "Boost.Serialization Demo" LANGUAGES CXX)

set(CMAKE_CXX EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.65 REQUIRED serialization program_options system)
file(GLOB src boost.serialization.demo/*.cpp)

add_executable(demo ${src})

target_link_libraries(demo
  Boost::serialization
  Boost::program_options
  Boost::system
)
