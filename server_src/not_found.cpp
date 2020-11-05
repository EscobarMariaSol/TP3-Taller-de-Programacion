#include "not_found.h"

NotFound::NotFound(): Response() {
}

NotFound::~NotFound() {
}

std::pair<std::string, std::string> NotFound::getResponse() {
    return std::pair<std::string, std::string>(
        "HTTP 404 NOT FOUND\n\n", "");
}
