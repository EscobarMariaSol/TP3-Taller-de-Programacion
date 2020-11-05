#include "not_allowed.h"

NotAllowed::NotAllowed(): Response() {
}

NotAllowed::~NotAllowed() {
}

std::pair<std::string, std::string> NotAllowed::getResponse() {
    return std::pair<std::string, std::string>(
        "HTTP 405 METHOD NOT ALLOWED\n\n", "");
}
