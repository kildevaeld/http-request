#pragma once
#include <QNetworkReply>
#include <httprequest/channel.hpp>

namespace httprequest {

class QtReply : public QObject {

  Q_OBJECT
public:
  QtReply(QNetworkReply *reply, HeaderCallback hcb, DataCallback dcb);
  ~QtReply() {}

signals:
  void finished();

private slots:
  void onReadyRead();
  void onFinished();

private:
  QNetworkReply *m_reply;
  HeaderCallback m_hcb;
  DataCallback m_dcb;
  bool m_first_read = true;
  // QByteArray m_bytes;
  // QBuffer m_buffer;
};

} // namespace httprequest