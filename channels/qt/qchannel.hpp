#pragma once
#include <QObject>
#include <httprequest/channel.hpp>

namespace httprequest {

namespace internal {
class QChannelPrivate;
}

class QChannel : public QObject, public Channel {
  Q_OBJECT
public:
  QChannel();
  virtual ~QChannel();

  virtual void request(Request &&req, HeaderCallback hcb, DataCallback dcb);

  virtual void deleteObject(Object *object);

private:
  std::unique_ptr<internal::QChannelPrivate> d;
};

} // namespace httprequest