cmake_minimum_required(VERSION 3.10)
project(http-request)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

option(EHTTP_QT_CHANNEL "build qt channel" off)
option(EHTTP_UV_CHANNEL "build libuv channel" off)
option(EHTTP_EXAMPLE "build examples" off)

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
if (EHTTP_QT_CHANNEL OR EHTTP_EXAMPLE)
    find_package(Qt5Network)
    add_subdirectory(channels/qt)
endif(EHTTP_QT_CHANNEL OR EHTTP_EXAMPLE)

## Uv channel
if (EHTTP_UV_CHANNEL OR EHTTP_EXAMPLE)
    add_subdirectory(vendor/uvhttp)
    include_directories(vendor/uvhttp/include)
    add_subdirectory(channels/uv)
endif(EHTTP_UV_CHANNEL OR EHTTP_EXAMPLE)

## Example
if (EHTTP_EXAMPLE)
    add_subdirectory(example)
endif(EHTTP_EXAMPLE)