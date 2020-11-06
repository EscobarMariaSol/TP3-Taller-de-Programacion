#include "ok.h"

Ok::Ok(const std::string& value): Response(), value(value) {
}

Ok::~Ok() {
}

void Ok::setResponseValue(const std::string& value) {
    this->value = std::ref(value);
}

std::pair<std::string, std::string> Ok::getResponse() const {
    return std::pair<std::string, std::string>(
        "HTTP 200 OK\n", this->value);
}

void Ok::serialize(std::stringbuf& str_serialize) const {
    std::string resp = "HTTP 200 OK\n" + this->value;
    str_serialize.sputn(resp.c_str(), resp.size());
}
