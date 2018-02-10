#pragma once
#include <httprequest/types.hpp>

namespace httprequest {

template <typename T> class Serializer {

public:
  using Type = T;
  virtual bool can(const std::string &mime) const = 0;
  virtual bool decode(const std::string &, T &) const = 0;
};

class IResponseDelegate {

public:
  virtual ~IResponseDelegate() {}

  int status() const { return m_status; }
  Header &header() { return m_header; }

  virtual void on_header(int status, Header &&header) {
    m_header = std::move(header);
  }
  virtual void on_data(const unsigned char *data, size_t size) = 0;
  virtual void on_finished() = 0;

private:
  Header m_header;
  int m_status;
};

template <typename T> class ResponseDelegate : public IResponseDelegate {

public:
  ResponseDelegate(Callback<typename T::Type> fn) : m_fn(std::move(fn)) {}
  ResponseDelegate(ResponseDelegate<T> &other) = delete;

  ~ResponseDelegate() {}

  virtual void on_data(const unsigned char *data, size_t size) {
    m_buffer.append((const char *)data, size);
  }

  virtual void on_finished() {
    typename T::Type result;
    m_serializer.decode(m_buffer, result);
    auto h = header();
    m_fn(Response<typename T::Type>(status(), std::move(h), std::move(result)));
  }

private:
  T m_serializer;
  Callback<typename T::Type> m_fn;
  std::string m_buffer;
};

} // namespace httprequest