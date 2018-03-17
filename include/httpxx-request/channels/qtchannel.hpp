#pragma once
#include <QObject>
#include <httpxx-request/channel.hpp>

namespace httpxx_request {

namespace internal {
class QtChannelPrivate;
}

class QtChannel : public QObject, public Channel {
  Q_OBJECT
public:
  QtChannel();
  virtual ~QtChannel();

  virtual void request(Request &&req, IResponseDelegate *delegate);
  virtual void async(std::function<void(void *)> fn, void *data);

private:
  std::unique_ptr<internal::QtChannelPrivate> d;
};

} // namespace httpxx_request