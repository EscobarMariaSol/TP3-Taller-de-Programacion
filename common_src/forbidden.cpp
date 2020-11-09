#include "forbidden.h"

Forbidden::Forbidden(): Response() {
}

Forbidden::~Forbidden() {
}

void Forbidden::getResponse(std::stringbuf& str_serialize) {
    std::string resp= "HTTP/1.1 403 FORBIDDEN\n\n";
    str_serialize.sputn(resp.c_str(), resp.size());
}
