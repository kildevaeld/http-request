cmake_minimum_required(VERSION 3.10)
project(http-request)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

## json
option(JSON_BuildTests "Build the unit tests when BUILD_TESTING is enabled." OFF)
include_directories(vendor/json/src)
add_subdirectory(vendor/json)

## Parser
include_directories(vendor/httpxx-parser/include)
add_subdirectory(vendor/httpxx-parser)

## Httprequest
include_directories(${PROJECT_ROOT}/include)
add_subdirectory(src)

## Qt channel
find_package(Qt5Network)
add_subdirectory(channels/qt)


## Example
add_subdirectory(example)