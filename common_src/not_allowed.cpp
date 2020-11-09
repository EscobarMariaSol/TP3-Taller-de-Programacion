#include "not_allowed.h"

NotAllowed::NotAllowed(const std::string& value): Response(), value(value) {
}

NotAllowed::~NotAllowed() {
}

void NotAllowed::getResponse(std::stringbuf& str_serialize) {
    std::string resp = "HTTP/1.1 405 METHOD NOT ALLOWED\n\n";
    resp += this->value + " es un comando desconocido\n";
    str_serialize.sputn(resp.c_str(), resp.size());
}
