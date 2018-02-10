
set(SOURCES uvchannel.cpp request.cpp)

add_library(uvchannel ${SOURCES})
target_link_libraries(uvchannel uvhttp)