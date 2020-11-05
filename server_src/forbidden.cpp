#include "forbidden.h"

Forbidden::Forbidden(): Response() {
}

Forbidden::~Forbidden() {
}

std::pair<std::string, std::string> Forbidden::getResponse() {
    return std::pair<std::string, std::string>(
        "HTTP 403 FORBIDDEN\n\n", "");
}