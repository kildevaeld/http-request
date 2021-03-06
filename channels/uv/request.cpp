#include "request.hpp"

using httpxx_types::Method;

namespace httpxx_request {

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

  m_req.set_header("Host", m_req.url().host());

  m_response_cbs = {.on_connect = UVRequest::on_connect,
                    .on_headers = UVRequest::on_headers,
                    .on_finished = UVRequest::on_finished,
                    .on_data = UVRequest::on_data,
                    .on_error = UVRequest::on_error};
}
UVRequest::~UVRequest() {
  uv_http_request_free(&m_request);
  uv_http_free(m_client);
}

void UVRequest::start(std::function<void()> fn) {
  m_fn = std::move(fn);

  for (auto &h : m_req.header()) {
    uv_http_header_set(m_request.headers, h.first.c_str(), h.second.c_str());
  }

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

  req->m_delegate->on_data((const unsigned char *)data, size);

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

void UVRequest::on_error(http_client_t *client, const char *name,
                         const char *desc) {
  UVRequest *req = static_cast<UVRequest *>(uv_http_get_data(client));
  req->m_delegate->on_error(Error(name));
}

} // namespace httpxx_request