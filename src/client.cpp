#include <httprequest/client.hpp>
#include <iostream>

namespace httprequest {

Client::Client() {}

Client::Client(std::shared_ptr<Channel> channel)
    : m_channel(std::move(channel)) {}

void Client::json(Request req, Callback<nlohmann::json> fn) {
  auto reply = request(std::move(req));
  reply->on<FinishEvent>(
      [reply](auto &, const auto &) { /* reply->deleteLater();*/ });
  reply->on<HeaderEvent>([](auto &, const auto &) {});
  reply->on<DataEvent>([](auto &, const auto &) {});
}

void Client::request(Request req, Callback<std::string> fn) {
  auto resp = new Response<std::string>();
  m_channel->request(
      std::move(req),
      [resp](auto status, const auto &&header) {
        resp->header = header;
        resp->status = status;
      },

      [ resp, fn = std::move(fn), this ](const auto data, auto size) {
        if (data == NULL) {
          fn(*resp);
          m_channel->async<Response<std::string>>(
              [](auto resp) { delete resp; }, resp);
        } else {
          resp->content.append((const char *)data, size);
        }

      });
}

Reply *Client::request(Request req) {
  Reply *reply = new Reply(m_channel);
  m_channel->request(std::move(req),
                     [reply](auto status, const auto &&header) {
                       reply->publish(HeaderEvent(status, header));
                     },
                     [reply](const auto data, auto size) {
                       if (data == NULL) {
                         reply->publish(FinishEvent());
                       } else {
                         reply->publish(DataEvent((const char *)data, size));
                       }
                     });

  return reply;
}

} // namespace httprequest