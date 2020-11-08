#include "forbidden.h"

Forbidden::Forbidden(): Response() {
}

Forbidden::~Forbidden() {
}

std::pair<std::string, std::string> Forbidden::getResponse() const {
    return std::pair<std::string, std::string>(
        "HTTP/1.1 403 FORBIDDEN\n\n", "");
}

void Forbidden::serialize(std::stringbuf& str_serialize) const {
    std::string resp= "HTTP/1.1 403 FORBIDDEN\n\n";
    str_serialize.sputn(resp.c_str(), resp.size());
}