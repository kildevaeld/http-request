#include <fstream> // std::ofstream
#include <httpxx-request/channels/uvchannel.hpp>
#include <httpxx-request/client.hpp>
#include <httpxx-request/iresponse-delegate.hpp>
#include <httpxx-request/serializers.hpp>
#include <iostream>

using namespace httpxx_request;

int main() {

  auto channel = std::make_shared<UVChannel>(uv_default_loop());

  Client client(channel);

  /*auto reply = client.request(Request(Method::Get, "http://google.com"));

  reply->once<HeaderEvent>([](const auto &e, auto &) {
    for (auto h : e.header) {
      std::cout << h.first << ": " << h.second << std::endl;
    }

    std::cout << "Header" << std::endl;
  });

  reply->on<DataEvent>(
      [](const auto &, auto &) { std::cout << "Data" << std::endl; });

  reply->once<FinishEvent>([reply, channel](const auto &, auto &) {
    // reply->deleteLater();
    std::cout << "finished" << std::endl;

  });*/

  /*client.request(Request(Method::Get, "http://google.com"),
                 [](const auto &resp) {
                   for (const auto &kv : resp.header) {
                     std::cout << kv.first << " " << kv.second << "\n";
                   }
                   std::cout << "Coud" << resp.content << std::endl;
                 });*/

  client.request(Request(Method::Get, "http://localhost:4000/"),
                 [](const auto &k) { std::cout << k.content << std::endl; });

  client.request<serializers::Json>(
      Request(Method::Get, "http://localhost:4000/json"),
      [](const auto &k) { std::cout << k.content.dump() << std::endl; });

  std::ofstream outfile("test.txt");

  auto stream = new StreamResponseDelegate<std::ofstream>(
      std::move(outfile), [](auto &&resp) {
        std::cout << "done" << std::endl;
        resp.content.close();
      });

  client.request(Request(Method::Get, "http://localhost:4000/json"), stream);

  return uv_run(uv_default_loop(), UV_RUN_DEFAULT);
}