#pragma once
#include <httprequest/channel.hpp>

namespace httprequest {

template <typename T> class Response {

public:
    Response() {}
    ~Response() {}   

    T content;
    Header header;
    int status;
};

} // namespace httprequest