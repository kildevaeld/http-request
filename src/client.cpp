#include <httpxx-request/client.hpp>
#include <httpxx-request/serializers.hpp>
#include <iostream>

namespace httpxx_request {

//Client::Client() {}

Client::Client(Channel *channel)
    : m_channel(channel) {}
  
Client::~Client() {}

void Client::request(Request req, IResponseDelegate *delegate) {
  m_channel->request(std::move(req), delegate);
}

void Client::request(Request req, Callback<std::string> fn) {
  request<serializers::Text>(std::move(req), std::move(fn));
}

} // namespace httprequest