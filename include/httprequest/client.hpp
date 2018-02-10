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

  template <typename T>
  void request(Request req, Callback<typename T::Type> fn) {
    ResponseDelegate<T> *resp = new ResponseDelegate<T>(std::move(fn));
    request(std::move(req), resp);
  }

  void request(Request req, IResponseDelegate *delegate);
  void request(Request req, Callback<std::string> fn);

private:
  std::shared_ptr<Channel> m_channel;
};

} // namespace httprequest