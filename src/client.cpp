#include <httprequest/client.hpp>

namespace httprequest {

Client::Client() {}

Client::Client(std::shared_ptr<Channel> channel)
    : m_channel(std::move(channel)) {}

void Client::json(Request req, Callback<nlohmann::json> fn) {
  auto reply = request(std::move(req));
  reply->on<FinishEvent>(
      [reply](auto &, const auto &) { reply->deleteLater(); });
  reply->on<HeaderEvent>([](auto &, const auto &) {});
  reply->on<DataEvent>([](auto &, const auto &) {});
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