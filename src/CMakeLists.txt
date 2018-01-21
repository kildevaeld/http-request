
set(SOURCES
    client.cpp
    reply.cpp
)

add_library(httprequest ${SOURCES})
target_link_libraries(httprequest sigc++)
target_include_directories(httprequest PUBLIC ${PROJECT_ROOT}/include)