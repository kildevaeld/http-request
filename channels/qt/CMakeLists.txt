
qt5_wrap_cpp(MOCS ${PROJECT_SOURCE_DIR}/include/httpxx-request/channels/qtchannel.hpp reply.hpp)

set(SOURCES
    qtchannel.cpp
    reply.cpp
    ${MOCS}
)

add_library(httpxx_qtchannel ${SOURCES})

target_link_libraries(httpxx_qtchannel Qt5::Network httpxx_request)