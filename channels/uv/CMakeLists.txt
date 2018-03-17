
set(SOURCES uvhttpchannel.cpp request.cpp)

add_library(httpxx_uvhttpchannel ${SOURCES})
target_link_libraries(httpxx_uvhttpchannel uvhttp httpxx_request)