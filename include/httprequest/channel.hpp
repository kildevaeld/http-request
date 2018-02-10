#pragma once
#include <functional>
#include <httprequest/iresponse-delegate.hpp>
#include <httprequest/types.hpp>
#include <httpxx-parser/parser.hpp>
#include <httpxx-parser/request.hpp>
#include <json.hpp>

namespace httprequest {

class Object {
public:
  virtual ~Object() {}
};

class Channel {

public:
  virtual ~Channel() {}

  virtual void request(Request &&req, IResponseDelegate *delegate) = 0;
  template <typename T> void deleteLater(T *ptr) {
    async<T>([ptr](T *ptr) { delete ptr; }, ptr);
  }

  template <typename T> void async(std::function<void(T *ptr)> fn, T *data) {
    async([ fn = std::move(fn), data ](void *data) {
      T *c = static_cast<T *>(data);
      fn(c);
    },
          data);
  }

  virtual void async(std::function<void(void *)> fn, void *data) = 0;
};

} // namespace httprequest