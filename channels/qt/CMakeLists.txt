
qt5_wrap_cpp(MOCS ${PROJECT_SOURCE_DIR}/include/httpxx-request/channels/qchannel.hpp reply.hpp)

set(SOURCES
    qchannel.cpp
    reply.cpp
    ${MOCS}
)

add_library(qchannel ${SOURCES})

target_link_libraries(qchannel Qt5::Network httpxx_request)