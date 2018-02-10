#pragma once
#include <functional>
#include <httpxx-request/iresponse-delegate.hpp>
#include <httpxx-request/types.hpp>
#include <httpxx-types/request.hpp>
#include <json.hpp>

namespace httpxx_request {

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