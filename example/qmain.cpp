#include <QCoreApplication>
#include <httprequest/channels/qchannel.hpp>
#include <httprequest/client.hpp>
#include <iostream>

using namespace httprequest;

int main(int argc, char **argv) {

  QCoreApplication app(argc, argv);

  auto channel = std::make_shared<httprequest::QChannel>();

  Client client(channel);

  auto reply = client.request(Request(Method::Get, "http://google.com"));

  reply->once<HeaderEvent>(
      [](const auto &, auto &) { std::cout << "Header" << std::endl; });

  reply->on<DataEvent>(
      [](const auto &, auto &) { std::cout << "Data" << std::endl; });

  reply->once<FinishEvent>([reply, &app](const auto &, auto &) {
    reply->deleteLater();
    std::cout << "finished" << std::endl;
    app.exit();
  });

  return app.exec();
}