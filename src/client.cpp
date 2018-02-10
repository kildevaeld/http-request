#include <httprequest/client.hpp>
#include <httprequest/serializers.hpp>
#include <iostream>

namespace httprequest {

Client::Client() {}

Client::Client(std::shared_ptr<Channel> channel)
    : m_channel(std::move(channel)) {}

void Client::request(Request req, IResponseDelegate *delegate) {
  m_channel->request(std::move(req), delegate);
}

void Client::request(Request req, Callback<std::string> fn) {
  request<TextSerializer>(std::move(req), std::move(fn));
}

} // namespace httprequest