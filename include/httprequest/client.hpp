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

  template <typename T>
  void request(Request req, Callback<typename T::Type> fn) {
    ResponseDelegate<T> *resp = new ResponseDelegate<T>(std::move(fn));
    request(std::move(req), resp);
  }

  void request(Request req, IResponseDelegate *delegate);
  void request(Request req, Callback<std::string> fn);

  /*template <typename T, typename... Args>
  void request(Request req, Args &&... args) {
    T *resp = new T(std::forward<Args>(args)...);
    request(std::move(req), resp);
  }*/

private:
  std::shared_ptr<Channel> m_channel;
};

} // namespace httprequest