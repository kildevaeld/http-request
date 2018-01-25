#pragma once
#include <QObject>
#include <httprequest/channel.hpp>

namespace httprequest {

namespace internal {
class UVChannelPrivate;
}

class UVChannel : public Channel {
 
public:
  UVChannel();
  virtual ~UVChannel();

  virtual void request(Request &&req, HeaderCallback hcb, DataCallback dcb);

  virtual void deleteObject(Object *object);

private:
  std::unique_ptr<internal::UVChannelPrivate> d;
};

} // namespace httprequest