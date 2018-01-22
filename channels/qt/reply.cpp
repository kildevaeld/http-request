#include "reply.hpp"

namespace httprequest {

Reply::Reply(QNetworkReply *reply, HeaderCallback hcb, DataCallback dcb)
    : QObject(), m_reply(reply), m_hcb(std::move(hcb)), m_dcb(std::move(dcb)) {

  connect(m_reply, &QNetworkReply::finished, this, &Reply::onFinished);
  connect(m_reply, &QIODevice::readyRead, this, &Reply::onReadyRead);

  // m_buffer.setBuffer(&m_bytes);
  // m_buffer.open(QBuffer::ReadWrite);
}

void Reply::onReadyRead() {
  if (m_first_read) {
    Header h;
    for (auto a : m_reply->rawHeaderPairs()) {
      qDebug() << a.first << a.second;
      h[a.first.toStdString()] = a.second.toStdString();
    }
    auto statusCode =
        m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    m_first_read = false;

    m_hcb(statusCode.toInt(), std::move(h));
  }

  auto buffer = m_reply->readAll();

  m_dcb((const unsigned char *)buffer.data(), buffer.size());
}
void Reply::onFinished() {

  m_dcb(NULL, 0);

  if (m_reply->error()) {
  } else {
  }
  emit this->finished();
}

} // namespace httprequest