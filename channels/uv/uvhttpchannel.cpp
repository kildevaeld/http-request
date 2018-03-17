#include "request.hpp"
#include <httpxx-request/channels/uvhttpchannel.hpp>

namespace httpxx_request {

namespace internal {
class UVHttpChannelPrivate {

public:
  UVHttpChannelPrivate(uv_loop_t *l) : loop(l) {}

  uv_loop_t *loop = nullptr;
};
} // namespace internal

UVHttpChannel::UVHttpChannel(uv_loop_t *loop)
    : d(new internal::UVHttpChannelPrivate(loop)) {}

UVHttpChannel::~UVHttpChannel() {}

void UVHttpChannel::request(Request &&req, IResponseDelegate *delegate) {
  auto request = new UVRequest(d->loop, std::move(req), delegate);
  request->start([request, this]() {
    this->async([request](auto) { delete request; }, NULL);
  });
}

uv_loop_t *UVHttpChannel::loop() const { return d->loop; }

struct bag {
  std::function<void(void *)> fn;
  void *data;
};

static void async_cb(uv_async_t *async) {
  uv_close((uv_handle_t *)async, NULL);

  auto b = static_cast<bag *>(async->data);

  b->fn(b->data);

  delete b;
  delete async;
}

void UVHttpChannel::async(std::function<void(void *)> fn, void *data) {
  uv_async_t *async = new uv_async_t;

  auto b = new bag();
  b->fn = std::move(fn);
  b->data = data;

  async->data = b;
  uv_async_init(d->loop, async, async_cb);
  uv_async_send(async);
}

} // namespace httpxx_request