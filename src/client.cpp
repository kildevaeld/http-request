#include <httprequest/client.hpp>
#include <httprequest/serializers.hpp>
#include <iostream>

namespace httprequest {

Client::Client() {}

Client::Client(std::shared_ptr<Channel> channel)
    : m_channel(std::move(channel)) {}

void Client::json(Request req, Callback<nlohmann::json> fn) {
  request(
      std::move(req), [fn = std::move(fn)](const Response<std::string> &resp) {
        Response<nlohmann::json> r;
        r.status = resp.status;
        r.header = std::move(resp.header);
        try {
          r.content = nlohmann::json::parse(resp.content);
        } catch (const nlohmann::json::exception &e) {
        }
        fn(r);
      });
}

void Client::request(Request req, Callback<std::string> fn) {
  // auto resp = std::make_shared<Response<std::string>>();

  m_channel->request(std::move(req),
                     new ResponseDelegate<TextSerializer>(std::move(fn)));
  /*m_channel->request(
      std::move(req),
      [resp](auto status, const auto &&header) {
        resp->header = header;
        resp->status = status;
      },

      [ resp, fn = std::move(fn), this ](const auto data, auto size) {
        if (data == NULL) {
          fn(*resp.get());
        } else {
          resp->content.append((const char *)data, size);
        }
      });*/
}

Reply *Client::request(Request req) {
  /*Reply *reply = new Reply(m_channel);
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
                     });*/

  return nullptr;
}

} // namespace httprequest