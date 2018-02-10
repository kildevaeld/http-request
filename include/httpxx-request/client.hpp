#pragma once
#include <httpxx-request/channel.hpp>
#include <httpxx-request/types.hpp>
#include <memory>

namespace httpxx_request {

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

  template <typename T>
  void get(const URL &url, Callback<typename T::Type> fn) {
    request(Request(Method::Get, url), fn);
  }

private:
  std::shared_ptr<Channel> m_channel;
};

} // namespace httpxx_request
