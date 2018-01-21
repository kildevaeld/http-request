#pragma once
#include <httprequest/channel.hpp>
#include <httprequest/reply.hpp>
#include <httprequest/response.hpp>

#include <memory>

namespace httprequest {

template <typename T>
using Callback = std::function<void(const Response<T> &resp)>;

class Client {

public:
  Client();
  Client(std::shared_ptr<Channel>);

  template <typename T> void json(const Request &req, Callback<T> fn) {}

  void json(Request req, Callback<nlohmann::json> fn);

  Reply *request(Request req);

private:
  std::shared_ptr<Channel> m_channel;
};

} // namespace httprequest