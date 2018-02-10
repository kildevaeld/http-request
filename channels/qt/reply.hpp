#pragma once
#include <QNetworkReply>
#include <httpxx-request/channel.hpp>

namespace httpxx_request {

class QtReply : public QObject {

  Q_OBJECT
public:
  QtReply(QNetworkReply *reply, IResponseDelegate *delegate);
  ~QtReply() {}

signals:
  void finished();

private slots:
  void onReadyRead();
  void onFinished();

private:
  QNetworkReply *m_reply;
  IResponseDelegate *m_delegate;

  bool m_first_read = true;
  // QByteArray m_bytes;
  // QBuffer m_buffer;
};

} // namespace httprequest