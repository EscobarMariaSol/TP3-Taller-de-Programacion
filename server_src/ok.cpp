#include "ok.h"

/************************ Métodos públicos de la clase OK ********************/

Ok::Ok(const std::string& value): Response(), value(value) {
}

Ok::~Ok() {
}

void Ok::operator()(std::stringbuf& str_serialize) {
    std::string resp = "HTTP/1.1 200 OK\n" + this->value;
    str_serialize.sputn(resp.c_str(), resp.size());
}
