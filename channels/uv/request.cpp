#include "request.hpp"

namespace httprequest {

static inline uv_http_method_t get_method(Method method) {
  switch (method) {
  case Method::Get:
    return HTTP_GET;
  case Method::Post:
    return HTTP_POST;
  case Method::Delete:
    return HTTP_DELETE;
  case Method::Put:
    return HTTP_PUT;
  case Method::Patch:
    return HTTP_PATCH;
  case Method::Option:
    return HTTP_OPTIONS;
  case Method::Head:
    return HTTP_HEAD;
  }
}

UVRequest::UVRequest(uv_loop_t *loop, Request &&req,
                     IResponseDelegate *delegate)
    : m_loop(loop), m_req(std::move(req)), m_delegate(delegate) {

  uv_http_request_init(&m_request, get_method(m_req.method()),
                       m_req.url().str().c_str());
  m_client = uv_http_create(loop, &m_request);
  uv_http_set_data(m_client, this);

  m_response_cbs = {.on_connect = UVRequest::on_connect,
                    .on_headers = UVRequest::on_headers,
                    .on_finished = UVRequest::on_finished,
                    .on_data = UVRequest::on_data};
}
UVRequest::~UVRequest() {
  if (m_request.headers)
    uv_http_header_free(m_request.headers);
  uv_http_free(m_client);
}

void UVRequest::start(std::function<void()> fn) {
  m_fn = std::move(fn);
  uv_http_request(m_client, &m_response_cbs);
}

void UVRequest::on_connect(http_client_t *client, int status) {

  UVRequest *req = static_cast<UVRequest *>(uv_http_get_data(client));
  uv_buf_t buf;
  buf.base = req->m_req.body().data();
  buf.len = req->m_req.body().size();

  uv_http_request_write(req->m_client, &buf, NULL);
  uv_http_request_end(client);
}

bool UVRequest::on_data(http_client_t *client, const char *data, size_t size) {
  UVRequest *req = static_cast<UVRequest *>(uv_http_get_data(client));

  req->m_delegate->on_data(data, size);
  // req->m_dcb((const unsigned char *)data, size);

  return true;
}
bool UVRequest::on_headers(http_client_t *client, int status,
                           uv_http_header_t *header) {
  UVRequest *req = static_cast<UVRequest *>(uv_http_get_data(client));

  Header h;
  uv_http_header_foreach(item, header) { h[item->field] = item->value; }

  req->m_delegate->on_header(status, std::move(h));

  return true;
}

void UVRequest::on_finished(http_client_t *client) {
  UVRequest *req = static_cast<UVRequest *>(uv_http_get_data(client));
  req->m_delegate->on_finished();
  req->m_fn();
}

} // namespace httprequest