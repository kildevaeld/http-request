#include <httprequest/iresponse-delegate.hpp>

namespace httprequest {

IResponseDelegate::~IResponseDelegate(){};

int IResponseDelegate::status() const { return m_status; }
const Header IResponseDelegate::header() const { return m_header; }

void IResponseDelegate::on_header(int status, Header &&header) {}

} // namespace httprequest