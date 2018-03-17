#include <QCoreApplication>
#include <httpxx-request/channels/qchannel.hpp>
#include <httpxx-request/client.hpp>
#include <httpxx-request/serializers.hpp>
#include <iostream>

using namespace httpxx_request;
using namespace httpxx_types;

int main(int argc, char **argv) {

  QCoreApplication app(argc, argv);

  auto client = Client::create<QChannel>();

 /* client->request(Request(Method::Get, "http://localhost:4000/"),
                 [](const auto &k) { std::cout << k.content << std::endl; });

  client->request<serializers::Json>(
      Request(Method::Get, "http://localhost:4000/json"),
      [](const auto &k) { std::cout << k.content.dump() << std::endl; });*/
      Request req(Method::Post, "http://localhost:5000/auth/login");
  req.set_body("{\"email\":\"test@gmail.com\",\"password\":\"password\"}");
  client->request(std::move(req),
                 [](const auto &k) {
                   if (!k.valid()) {
                     std::cout << "error: " << k.error.what() << std::endl;
                   }
                   std::cout << k.content << std::endl;
                 });


  return app.exec();
}