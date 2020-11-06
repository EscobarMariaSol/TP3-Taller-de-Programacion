#include "not_allowed.h"

NotAllowed::NotAllowed(): Response() {
}

NotAllowed::~NotAllowed() {
}

std::pair<std::string, std::string> NotAllowed::getResponse() const {
    return std::pair<std::string, std::string>(
        "HTTP 405 METHOD NOT ALLOWED\n\n", "");
}

void NotAllowed::serialize(std::stringbuf& str_serialize) const {
    std::string resp = "HTTP 405 METHOD NOT ALLOWED\n\n";
    str_serialize.sputn(resp.c_str(), resp.size());
}