#pragma once
#include <QObject>
#include <httpxx-request/channel.hpp>

namespace httpxx_request {

namespace internal {
class QChannelPrivate;
}

class QChannel : public QObject, public Channel {
  Q_OBJECT
public:
  QChannel();
  virtual ~QChannel();

  virtual void request(Request &&req, IResponseDelegate *delegate);
  virtual void async(std::function<void(void *)> fn, void *data);

private:
  std::unique_ptr<internal::QChannelPrivate> d;
};

} // namespace httprequest