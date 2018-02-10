

#add_executable(qreq qmain.cpp)
#target_link_libraries(qreq httprequest qchannel)

add_executable(uvreq uvmain.cpp)
target_link_libraries(uvreq httprequest uvchannel uvhttp)