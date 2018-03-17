

add_executable(qreq qmain.cpp)
target_link_libraries(qreq httpxx_request httpxx_qtchannel)

add_executable(uvreq uvmain.cpp)
target_link_libraries(uvreq httpxx_request httpxx_uvhttpchannel uvhttp)