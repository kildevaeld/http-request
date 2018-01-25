
set(SOURCES uvchannel.cpp)

add_library(httprequest_libuv ${SOURCES})
target_link_libraries(httprequest uv)