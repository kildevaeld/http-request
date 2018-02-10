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
  Response(int s, Header &&h, T &&c)
      : content(std::move(c)), header(std::move(h)), status(s) {}
  Response() {}
  Response(Response &other)
      : content(other.content), header(other.header), status(other.status) {}
  Response(Response &&other)
      : content(std::move(other.content)), header(std::move(other.header)),
        status(other.status) {}

  Response &operator=(const Response &other) {
    if (&other != this) {
      content = other.content;
      header = other.header;
      status = other.status;
    }
    return *this;
  }

  Response &operator=(Response &&other) {
    if (&other != this) {
      content = std::move(other.content);
      header = std::move(other.header);
      status = other.status;
    }

    return *this;
  }

  ~Response() {}

  T content;
  Header header;
  int status;
};

template <typename T> using Callback = std::function<void(Response<T> &&resp)>;

} // namespace httprequest