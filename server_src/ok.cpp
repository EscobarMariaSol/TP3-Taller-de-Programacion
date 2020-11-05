#include "ok.h"

Ok::Ok(const std::string& value): Response(), value(value) {
}

Ok::~Ok() {
}

void Ok::setResponseValue(const std::string& value) {
    this->value = std::ref(value);
}

std::pair<std::string, std::string> Ok::getResponse() {
    return std::pair<std::string, std::string>(
        "HTTP 200 OK\n", this->value);
}
