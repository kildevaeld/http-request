#include <QCoreApplication>
#include <httprequest/channels/qchannel.hpp>
#include <httprequest/client.hpp>
#include <httprequest/serializers.hpp>
#include <iostream>
using namespace httprequest;

int main(int argc, char **argv) {

  QCoreApplication app(argc, argv);

  auto channel = std::make_shared<httprequest::QChannel>();

  Client client(channel);

  client.request(Request(Method::Get, "http://localhost:4000/"),
                 [](const auto &k) { std::cout << k.content << std::endl; });

  client.request<serializers::Json>(
      Request(Method::Get, "http://localhost:4000/json"),
      [](const auto &k) { std::cout << k.content.dump() << std::endl; });

  return app.exec();
}