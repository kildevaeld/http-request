#pragma once
#include <httpxx-request/types.hpp>
#include <httpxx-types/url.hpp>
#include <string>

namespace httpxx_request {

namespace internal {
class RequestPrivate;
}

class Request {

public:
  Request(httpxx_types::Method method = httpxx_types::Get,
          const httpxx_types::URL &url = httpxx_types::URL());
  Request(Request &&other);

  Request(const Request &) = delete;
  Request &operator=(const Request &) = delete;

  virtual ~Request();

  Request &set_url(const httpxx_types::URL &url);
  Request &set_url(httpxx_types::URL &&url);
  httpxx_types::URL url() const;

  Request &set_method(httpxx_types::Method method);
  httpxx_types::Method method() const;

  Request &set_header(const httpxx_types::Header &header);
  Request &set_header(httpxx_types::Header &&header);
  Request &set_header(const std::string &field, const char *value);
  Request &set_header(const std::string &field, const std::string &value);

  /*template <typename Integer,
            typename = std::enable_if_t<std::is_integral<Integer>::value>>
  Request &set_header(const std::string &field, Integer i) {
    std::string v = std::to_string(i);
    return set_header(field, v);
  }*/

  template <typename Integer,
            typename = std::enable_if<std::is_integral<Integer>::value>>
  Request &set_header(const std::string &field, Integer i) {
    std::string v = std::to_string(i);
    return set_header(field, v);
  }

  httpxx_types::Header header() const;

  Request &set_body(const std::string &body);
  Request &set_body(std::string &&body);
  Request &set_body(const char *data, size_t size);

  std::string &body() const;

  bool valid() const;
  operator bool() const;

  std::string str() const;

  friend std::ostream &operator<<(std::ostream &, const Request &);

private:
  std::unique_ptr<internal::RequestPrivate> d;
};

} // namespace httpxx_request