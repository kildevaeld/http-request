cmake_minimum_required(VERSION 3.10)
project(http-request)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

option(HTTPX_REQ_QT_CHANNEL "build qt channel" off)
option(HTTPX_REQ_UV_CHANNEL "build libuv channel" off)
option(HTTPX_REQ_EXAMPLE "build examples" off)

## json
option(JSON_BuildTests "Build the unit tests when BUILD_TESTING is enabled." OFF)
include_directories(vendor/json/src)
add_subdirectory(vendor/json)

## Parser
#include_directories(vendor/httpxx-parser/include)
#add_subdirectory(vendor/httpxx-parser)
#include_directories(vendor/httpxx-types/include)
add_subdirectory(vendor/httpxx-types)
#message(STATUS ${httpxx_types_LIBRARIES})
## Httprequest
include_directories(${PROJECT_ROOT}/include)
add_subdirectory(src)


## Qt channel
if (HTTPX_REQ_QT_CHANNEL OR HTTPX_REQ_EXAMPLE)
    find_package(Qt5Network)
    add_subdirectory(channels/qt)
endif(HTTPX_REQ_QT_CHANNEL OR HTTPX_REQ_EXAMPLE)

## Uv channel
if (HTTPX_REQ_UV_CHANNEL OR HTTPX_REQ_EXAMPLE)
    add_subdirectory(vendor/uvhttp)
    include_directories(vendor/uvhttp/include)
    add_subdirectory(channels/uv)
endif(HTTPX_REQ_UV_CHANNEL OR HTTPX_REQ_EXAMPLE)

## Example
if (HTTPX_REQ_EXAMPLE)
    add_subdirectory(example)
endif(HTTPX_REQ_EXAMPLE)