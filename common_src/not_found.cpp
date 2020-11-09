#include "not_found.h"

NotFound::NotFound(): Response() {
}

NotFound::~NotFound() {
}

void NotFound::getResponse(std::stringbuf& str_serialize) {
    std::string resp = "HTTP/1.1 404 NOT FOUND\n\n";
    str_serialize.sputn(resp.c_str(), resp.size());
}
