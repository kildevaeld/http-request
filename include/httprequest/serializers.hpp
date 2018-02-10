#pragma once
#include <cstring>
#include <httprequest/iresponse-delegate.hpp>
#include <json.hpp>

namespace httprequest {

namespace serializers {

class Text : public Serializer<std::string> {

public:
  virtual bool can(const std::string &mime) const {
    return std::strncmp(mime.c_str(), "text", 4) == 0;
  }

  virtual bool decode(const std::string &in, std::string &out) const {
    out = in;
    return true;
  }
};

class Json : public Serializer<nlohmann::json> {

public:
  virtual bool can(const std::string &mime) const {
    return std::strncmp(mime.c_str(), "application/json", 16) == 0;
  }

  virtual bool decode(const std::string &in, nlohmann::json &out) const {
    try {
      out = nlohmann::json::parse(in);
    } catch (...) {
      return false;
    }
    return true;
  }
};

} // namespace serializers

} // namespace httprequest