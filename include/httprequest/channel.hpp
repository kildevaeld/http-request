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

  virtual void deleteObject(Object *object) = 0;
};

} // namespace httprequest