
set(SOURCES
    client.cpp
    request.cpp
    #reply.cpp
    #iresponse-delegate.cpp
)

add_library(httpxx_request ${SOURCES})
target_link_libraries(httpxx_request httpxx_types)
target_include_directories(httpxx_request 
    PUBLIC 
        #${PROJECT_ROOT}/include 
        #${PROJECT_ROOT}/vendor/json/src
        #${PROJECT_ROOT}/vendor/httpxx-types/include
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>  # <prefix>/include/mylib
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/vendor/json/src>
    #$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/vendor/htt/src>
)