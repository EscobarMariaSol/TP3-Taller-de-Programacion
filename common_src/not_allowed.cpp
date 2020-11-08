#include "not_allowed.h"

NotAllowed::NotAllowed(std::string value): Response(), value(value) {
}

NotAllowed::~NotAllowed() {
}

std::pair<std::string, std::string> NotAllowed::getResponse() const {
    return std::pair<std::string, std::string>(
        "HTTP/1.1 405 METHOD NOT ALLOWED\n\n", "");
}

void NotAllowed::serialize(std::stringbuf& str_serialize) const {
    std::string resp = "HTTP/1.1 405 METHOD NOT ALLOWED\n\n";
    resp += this->value + " es un comando desconocido\n";
    str_serialize.sputn(resp.c_str(), resp.size());
}