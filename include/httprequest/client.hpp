#pragma once
#include <httprequest/channel.hpp>
#include <httprequest/reply.hpp>
#include <httprequest/types.hpp>

#include <memory>

namespace httprequest {

class Client {

public:
  Client();
  Client(std::shared_ptr<Channel>);

  template <typename T> void json(const Request &req, Callback<T> fn) {}

  void json(Request req, Callback<nlohmann::json> fn);

  void request(Request req, Callback<std::string> fn);
  Reply *request(Request req);

private:
  std::shared_ptr<Channel> m_channel;
};

} // namespace httprequest