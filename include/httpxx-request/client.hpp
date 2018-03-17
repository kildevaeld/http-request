#pragma once
#include <httpxx-request/channel.hpp>
#include <httpxx-request/types.hpp>
#include <memory>

namespace httpxx_request {

class Client {

public:
  //Client();
  Client(Channel *);
  ~Client();
  Client(const Client &) = delete;
  Client &operator=(const Client &) = delete;

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

  template<typename T, typename ...Args>
  static std::shared_ptr<Client> create(Args &&... a) {
    T *channel = new T(std::forward<T>(a)...);
    return std::make_shared<Client>(channel);
  }


private:
  
  std::unique_ptr<Channel> m_channel;
};

} // namespace httpxx_request
