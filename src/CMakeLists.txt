
set(SOURCES
    client.cpp
    request.cpp
    #reply.cpp
    #iresponse-delegate.cpp
)

add_library(httpxx_req ${SOURCES})
target_link_libraries(httpxx_req httpxx_types)
target_include_directories(httpxx_req PUBLIC ${PROJECT_ROOT}/include)