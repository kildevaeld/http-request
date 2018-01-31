#pragma once
#include <functional>
#include <httpxx-parser/parser.hpp>
#include <httpxx-parser/request.hpp>
#include <json.hpp>

namespace httprequest {

using Request = httpxx_parser::Request;
using Header = httpxx_parser::Header;
using Method = httpxx_parser::Method;
using json = nlohmann::json;

using HeaderCallback = std::function<void(int status, Header &&header)>;
using DataCallback = std::function<void(const unsigned char *data, int size)>;

class Object {
public:
  virtual ~Object() {}
};

class Channel {

public:
  virtual ~Channel() {}

  virtual void request(Request &&req, HeaderCallback hcb, DataCallback dcb) = 0;

  template <typename T> void async(std::function<void(T *ptr)> fn, T *data) {
    async([ fn = std::move(fn), data ](void *data) {
      T *c = static_cast<T *>(data);
      fn(c);
    });
  }

  virtual void async(std::function<void(void *)> fn, void *data) = 0;
};

} // namespace httprequest