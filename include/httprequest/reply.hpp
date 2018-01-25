#pragma once
#include <httprequest/channel.hpp>
#include <httpxx-parser/emitter.hpp>

namespace httprequest {

class FinishEvent {};

struct DataEvent {
  DataEvent(const char *d, int s) : data(d), size(s) {}

  const char *data;
  int size;
};

class ErrorEvent {};

struct HeaderEvent {
  HeaderEvent(int s, Header h) : status(s), header(std::move(h)) {}

  int status;
  Header header;
};

class Reply : public httpxx_parser::Emitter<Reply>, public Object {
public:
public:
  Reply(std::shared_ptr<Channel> channel);
  virtual ~Reply();

   void deleteLater();

private:
  friend class Client;
  std::shared_ptr<Channel> m_channel;
};

} // namespace httprequest