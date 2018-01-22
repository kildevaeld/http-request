#include "../channels/qt/qchannel.hpp"
#include <QCoreApplication>
#include <httprequest/client.hpp>
#include <iostream>

using namespace httprequest;

int main(int argc, char **argv) {

  QCoreApplication app(argc, argv);

  auto channel = std::make_shared<httprequest::QChannel>();

  Client client(channel);

  auto reply = client.request(Request(Method::Get, "http://google.com"));

  // reply->on<HeaderEvent>([](const auto &, auto &) {});

  return app.exec();
}