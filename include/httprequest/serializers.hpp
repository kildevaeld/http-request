#pragma once
#include <cstring>
#include <httprequest/iresponse-delegate.hpp>
namespace httprequest {

class TextSerializer : public Serializer<std::string> {

public:
  virtual bool can(const std::string &mime) const {
    return std::strncmp(mime.c_str(), "text", 4) == 0;
  }

  virtual bool decode(const std::string &in, std::string &out) const {
    out = in;
    return true;
  }
};

} // namespace httprequest