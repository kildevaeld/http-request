

add_executable(qreq qmain.cpp)
target_link_libraries(qreq httpxx_req qchannel)

add_executable(uvreq uvmain.cpp)
target_link_libraries(uvreq httpxx_req uvchannel uvhttp)