#include "qchannel.hpp"
#include "reply.hpp"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>

namespace httprequest {

namespace internal {
class QChannelPrivate {

public:
  QNetworkAccessManager man;
};
} // namespace internal

QChannel::QChannel() : QObject(), d(new internal::QChannelPrivate) {
  // d->man.setStrictTransportSecurityEnabled(false);
}

QChannel::~QChannel() {}

void QChannel::request(Request &&req, HeaderCallback hcb, DataCallback dcb) {
  QUrl url(QString::fromStdString(req.url().str()));
  QNetworkRequest request(url);

  for (auto h : req.header())
    request.setRawHeader(QByteArray::fromStdString(h.first),
                         QByteArray::fromStdString(h.second));

  QSslConfiguration conf = request.sslConfiguration();
  conf.setPeerVerifyMode(QSslSocket::AutoVerifyPeer);
  request.setSslConfiguration(conf);

  QNetworkReply *reply = nullptr;
  switch (req.method()) {
  case Method::Get:
    reply = d->man.get(request);
    break;
  case Method::Post:
    reply = d->man.post(request, QByteArray::fromStdString(req.body()));
    break;
  case Method::Put:
    reply = d->man.put(request, QByteArray::fromStdString(req.body()));
    break;
  case Method::Delete:
    reply = d->man.deleteResource(request);
    break;
  default:
    return;
  }

  auto r = new Reply(reply, std::move(hcb), std::move(dcb));
  connect(r, &Reply::finished, r, &Reply::deleteLater);
}

void QChannel::deleteObject(Object *object) {
  QTimer::singleShot(0, [object]() { delete object; });
}
} // namespace httprequest