#include <httprequest/channels/uvchannel.hpp>
#include "reply.hpp"


namespace httprequest {

namespace internal {
class UVChannelPrivate {

public:
  
};
} // namespace internal

UVChannel::UVChannel() : QObject(), d(new internal::UVChannelPrivate) {
  
}

UVChannel::~UVChannel() {}

void UVChannel::request(Request &&req, HeaderCallback hcb, DataCallback dcb) {
  
}

void UVChannel::deleteObject(Object *object) {
  
}
} // namespace httprequest