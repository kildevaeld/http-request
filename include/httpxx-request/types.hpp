#pragma once
#include <exception>
#include <httpxx-types/header.hpp>
#include <httpxx-types/url.hpp>

#include <json.hpp>

namespace httpxx_request {

using httpxx_types::Header;
using httpxx_types::Method;
using httpxx_types::URL;

using HeaderCallback = std::function<void(int status, Header &&header)>;
using DataCallback = std::function<void(const unsigned char *data, int size)>;

class Error : public std::exception {

public:
  Error() {}
  Error(const char *msg) : m_what(msg) {}
  virtual const char *what() const throw() { return m_what.c_str(); }

private:
  std::string m_what;
};

template <typename T> class Response {

public:
  Response(Error &&err) : error(std::move(err)) {}
  Response(int s, Header &&h, Error &&err)
      : header(std::move(h)), status(s), error(std::move(err)) {}
  Response(int s, Header &&h, T &&c)
      : content(std::move(c)), header(std::move(h)), status(s), m_valid(true) {}
  Response() {}
  Response(Response &other)
      : content(other.content), header(other.header), status(other.status) {}
  Response(Response &&other)
      : content(std::move(other.content)), header(std::move(other.header)),
        status(other.status), error(std::move(other.error)) {}

  Response &operator=(const Response &other) {
    if (&other != this) {
      content = other.content;
      header = other.header;
      status = other.status;
      error = other.error;
      m_valid = other.m_valid;
    }
    return *this;
  }

  Response &operator=(Response &&other) {
    if (&other != this) {
      content = std::move(other.content);
      header = std::move(other.header);
      status = other.status;
      error = std::move(other.error);
      m_valid = other.m_valid;
    }

    return *this;
  }

  ~Response() {}

  bool valid() const { return m_valid; }

  operator bool() const { return valid(); }

  T content;
  Header header;
  int status;
  Error error;

private:
  bool m_valid = false;
};

template <typename T> using Callback = std::function<void(Response<T> &&resp)>;

} // namespace httpxx_request