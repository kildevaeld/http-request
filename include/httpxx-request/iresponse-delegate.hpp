#pragma once
#include <httpxx-request/types.hpp>

#include <iostream>

namespace httpxx_request {

template <typename T> class Serializer {

public:
  using Type = T;
  virtual bool can(const std::string &mime) const = 0;
  virtual void decode(const std::string &, T &) const = 0;
};

class IResponseDelegate {

public:
  virtual ~IResponseDelegate() {}

  int status() const { return m_status; }
  Header &header() { return m_header; }

  virtual void on_header(int status, Header &&header) {
    m_status = status;
    m_header = std::move(header);
  }
  virtual void on_data(const unsigned char *data, size_t size) = 0;
  virtual void on_finished() = 0;
  virtual void on_error(Error &&error) = 0;

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
    auto h = header();

    try {
      m_serializer.decode(m_buffer, result);
    } catch (const SerializeException &e) {
      m_fn(Response<typename T::Type>(status(), std::move(h), Error(e.what())));
      return;
    } catch (...) {

      m_fn(Response<typename T::Type>(status(), std::move(h),
                                      Error("serializer error")));
      return;
    }

    m_fn(Response<typename T::Type>(status(), std::move(h), std::move(result)));
  }

  virtual void on_error(Error &&error) {
    m_fn(Response<typename T::Type>(std::move(error)));
  }

private:
  T m_serializer;
  Callback<typename T::Type> m_fn;
  std::string m_buffer;
};

#include <ostream>

template <typename T> class StreamResponseDelegate : public IResponseDelegate {

public:
  StreamResponseDelegate(T &&stream, Callback<T> fn)
      : m_stream(std::move(stream)), m_fn(std::move(fn)) {}

  ~StreamResponseDelegate() {}

  virtual void on_data(const unsigned char *data, size_t size) {
    m_stream.write((const char *)data, size);
  }

  virtual void on_finished() {

    m_stream.flush();

    auto h = header();
    m_fn(Response<T>(status(), std::move(h), std::move(m_stream)));
  }

  virtual void on_error(Error &&error) {
    m_fn(Response<T>(std::move(error)));
    m_stream.close();
  }

private:
  T m_stream;
  Callback<T> m_fn;
};

} // namespace httpxx_request