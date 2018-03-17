

add_executable(qreq qmain.cpp)
target_link_libraries(qreq httpxx_request qchannel)

add_executable(uvreq uvmain.cpp)
target_link_libraries(uvreq httpxx_request uvchannel uvhttp)