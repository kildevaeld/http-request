#include "request.hpp"
#include <httprequest/channels/uvchannel.hpp>

namespace httprequest {

namespace internal {
class UVChannelPrivate {

public:
  UVChannelPrivate(uv_loop_t *l) : loop(l) {}

  uv_loop_t *loop = nullptr;
};
} // namespace internal

UVChannel::UVChannel(uv_loop_t *loop)
    : d(new internal::UVChannelPrivate(loop)) {}

UVChannel::~UVChannel() {}

void UVChannel::request(Request &&req, IResponseDelegate *delegate) {
  auto request = new UVRequest(d->loop, std::move(req), delegate);
  request->start([request, this]() {
    this->async([request](auto) { delete request; }, NULL);
  });
}

/*void UVChannel::request(Request &&req, HeaderCallback hcb, DataCallback dcb)
{

  auto request =
      new UVRequest(d->loop, std::move(req), std::move(hcb), std::move(dcb));
  request->start([request, this]() {
    this->async([request](auto) { delete request; }, NULL);
  });
}*/

uv_loop_t *UVChannel::loop() const { return d->loop; }

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

void UVChannel::async(std::function<void(void *)> fn, void *data) {
  uv_async_t *async = new uv_async_t;

  auto b = new bag();
  b->fn = std::move(fn);
  b->data = data;

  async->data = b;
  uv_async_init(d->loop, async, async_cb);
  uv_async_send(async);
}

/*void UVChannel::deleteObject2(void *object) {
  uv_async_t *async = new uv_async_t;
  async->data = object;
  uv_async_init(d->loop, async, async_cb);
  uv_async_send(async);
}*/

} // namespace httprequest