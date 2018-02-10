#pragma once
#include <httpxx-request/channel.hpp>
#include <uv.h>

namespace httpxx_request {

namespace internal {
class UVChannelPrivate;
}

class UVChannel : public Channel {

public:
  UVChannel(uv_loop_t *loop = uv_default_loop());
  virtual ~UVChannel();

  // virtual void request(Request &&req, HeaderCallback hcb, DataCallback dcb);
  virtual void request(Request &&req, IResponseDelegate *delegate);

  virtual void async(std::function<void(void *)> fn, void *data);

  uv_loop_t *loop() const;

private:
  std::unique_ptr<internal::UVChannelPrivate> d;
};

} // namespace httprequest