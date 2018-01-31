#pragma once
#include <httprequest/channel.hpp>
#include <uvhttp/client.h>

namespace httprequest {

class UVRequest : public Object {

public:
  UVRequest(uv_loop_t *loop, Request &&req, HeaderCallback hcb,
            DataCallback dcb);
  virtual ~UVRequest();

  void start(std::function<void()> fn);

private:
  static void on_connect(http_client_t *client, int status);
  static bool on_data(http_client_t *client, const char *data, size_t size);
  static bool on_headers(http_client_t *client, int status,
                         uv_http_header_t *header);
  static void on_finished(http_client_t *client);

  uv_loop_t *m_loop;
  Request m_req;
  HeaderCallback m_hcb;
  DataCallback m_dcb;
  http_client_t *m_client;
  http_request_t m_request;
  http_request_callbacks m_response_cbs;
  std::function<void()> m_fn;
};

} // namespace httprequest