#include <httprequest/reply.hpp>

namespace httprequest {

Reply::Reply(std::shared_ptr<Channel> channel)
    : m_channel(std::move(channel)) {}

Reply::~Reply() {}

void Reply::deleteLater() {

  m_channel->async<Reply>([this](auto reply) { delete reply; }, this);
}

} // namespace httprequest