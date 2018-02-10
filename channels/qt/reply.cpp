#include "reply.hpp"

namespace httprequest {

QtReply::QtReply(QNetworkReply *reply, IResponseDelegate *delegate)
    : QObject(), m_delegate(delegate), m_reply(reply) {

  connect(m_reply, &QNetworkReply::finished, this, &QtReply::onFinished);
  connect(m_reply, &QIODevice::readyRead, this, &QtReply::onReadyRead);
}

void QtReply::onReadyRead() {
  if (m_first_read) {
    Header h;
    for (auto a : m_reply->rawHeaderPairs()) {
      h[a.first.toStdString()] = a.second.toStdString();
    }
    auto statusCode =
        m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    m_first_read = false;

    m_delegate->on_header(statusCode.toInt(), std::move(h));
    // m_hcb(statusCode.toInt(), std::move(h));
  }

  auto buffer = m_reply->readAll();
  m_delegate->on_data((const unsigned char *)buffer.data(), buffer.size());
  // m_dcb((const unsigned char *)buffer.data(), buffer.size());
}
void QtReply::onFinished() {

  // m_dcb(NULL, 0);
  m_delegate->on_finished();
  if (m_reply->error()) {
  } else {
  }
  emit this->finished();
}

} // namespace httprequest