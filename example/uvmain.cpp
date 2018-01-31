#include <httprequest/channels/uvchannel.hpp>
#include <httprequest/client.hpp>
#include <iostream>

using namespace httprequest;

int main() {

  auto channel = std::make_shared<httprequest::UVChannel>(uv_default_loop());

  Client client(channel);

  auto reply = client.request(Request(Method::Get, "http://google.com"));

  reply->once<HeaderEvent>([](const auto &e, auto &) {
    for (auto h : e.header) {
      std::cout << h.first << ": " << h.second << std::endl;
    }

    std::cout << "Header" << std::endl;
  });

  reply->on<DataEvent>(
      [](const auto &, auto &) { std::cout << "Data" << std::endl; });

  reply->once<FinishEvent>([reply, channel](const auto &, auto &) {
    reply->deleteLater();
    std::cout << "finished" << std::endl;

  });

  return uv_run(uv_default_loop(), UV_RUN_DEFAULT);
}