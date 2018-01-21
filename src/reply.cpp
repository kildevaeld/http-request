#include <httprequest/reply.hpp>

namespace httprequest {

Reply::Reply(std::shared_ptr<Channel> channel)
    : m_channel(std::move(channel)) {}

void Reply::deleteLater() { m_channel->deleteLater(this); }

} // namespace httprequest