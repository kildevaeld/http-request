#pragma once
#include <httpxx-request/channel.hpp>
#include <uv.h>

namespace httpxx_request {

namespace internal {
class UVHttpChannelPrivate;
}

class UVHttpChannel : public Channel {

public:
  UVHttpChannel(uv_loop_t *loop = uv_default_loop());
  virtual ~UVHttpChannel();

  // virtual void request(Request &&req, HeaderCallback hcb, DataCallback dcb);
  virtual void request(Request &&req, IResponseDelegate *delegate);

  virtual void async(std::function<void(void *)> fn, void *data);

  uv_loop_t *loop() const;

private:
  std::unique_ptr<internal::UVHttpChannelPrivate> d;
};

} // namespace httprequest