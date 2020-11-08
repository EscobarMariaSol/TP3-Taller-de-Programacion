#include "not_found.h"

NotFound::NotFound(): Response() {
}

NotFound::~NotFound() {
}

std::pair<std::string, std::string> NotFound::getResponse() const {
    return std::pair<std::string, std::string>(
       "HTTP/1.1 404 NOT FOUND\n\n", "");
}

void NotFound::serialize(std::stringbuf& str_serialize) const {
    std::string resp = "HTTP/1.1 404 NOT FOUND\n\n";
    str_serialize.sputn(resp.c_str(), resp.size());
}