#include "reply.hpp"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <httpxx-request/channels/qchannel.hpp>

using httpxx_types::Method;

namespace httpxx_request {

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

void QChannel::request(Request &&req, IResponseDelegate *delegate) {
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
  case Method::Patch:
    reply = d->man.sendCustomRequest(request, "PATCH",
                                     QByteArray::fromStdString(req.body()));

    break;
  case Method::Delete:
    reply = d->man.deleteResource(request);
    break;
  default:
    return;
  }

  auto r = new QtReply(reply, delegate);
  connect(r, &QtReply::finished, r, &QtReply::deleteLater);
}

void QChannel::async(std::function<void(void *)> fn, void *data) {
  QTimer::singleShot(0, [ data, fn = std::move(fn) ]() { fn(data); });
}
} // namespace httpxx_request