#include <httpxx-request/client.hpp>
#include <httpxx-request/serializers.hpp>
#include <iostream>

namespace httpxx_request {

Client::Client() {}

Client::Client(std::shared_ptr<Channel> channel)
    : m_channel(std::move(channel)) {}

void Client::request(Request req, IResponseDelegate *delegate) {
  m_channel->request(std::move(req), delegate);
}

void Client::request(Request req, Callback<std::string> fn) {
  request<serializers::Text>(std::move(req), std::move(fn));
}

} // namespace httprequest