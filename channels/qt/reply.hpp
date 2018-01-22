#pragma once
#include <QNetworkReply>
#include <httprequest/channel.hpp>

namespace httprequest {

class Reply : public QObject {

  Q_OBJECT
public:
  Reply(QNetworkReply *reply, HeaderCallback hcb, DataCallback dcb);
  ~Reply() {}

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