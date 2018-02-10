#pragma once
#include <httpxx-parser/request.hpp>
#include <json.hpp>

namespace httprequest {

using Request = httpxx_parser::Request;
using Header = httpxx_parser::Header;
using Method = httpxx_parser::Method;
using json = nlohmann::json;

using HeaderCallback = std::function<void(int status, Header &&header)>;
using DataCallback = std::function<void(const unsigned char *data, int size)>;

template <typename T> class Response {

public:
  Response(int s, Header &&h, T &&c) : content(c), header(h), status(s) {}
  Response() {}
  Response(Response &other) {
    content = other.content;
    header = other.header;
    status = other.status;
  }
  ~Response() { printf("delete\n"); }

  T content;
  Header header;
  int status;
};

template <typename T>
using Callback = std::function<void(const Response<T> &resp)>;

} // namespace httprequest