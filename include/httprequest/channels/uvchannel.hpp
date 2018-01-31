#pragma once
#include <httprequest/channel.hpp>
#include <uv.h>

namespace httprequest {

namespace internal {
class UVChannelPrivate;
}

class UVChannel : public Channel {

public:
  UVChannel(uv_loop_t *loop = uv_default_loop());
  virtual ~UVChannel();

  virtual void request(Request &&req, HeaderCallback hcb, DataCallback dcb);

  uv_loop_t *loop() const;

  virtual void async(std::function<void(void *)> fn, void *data);

  // void deleteObject2(void *object);

private:
  std::unique_ptr<internal::UVChannelPrivate> d;
};

} // namespace httprequest