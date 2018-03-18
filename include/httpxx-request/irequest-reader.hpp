#pragma once
#include <cstdlib>

namespace httpx_request {

class IRequestReader {

public:
  virtual int read(char *data, size_t length) = 0;
};

} // namespace httpx_request