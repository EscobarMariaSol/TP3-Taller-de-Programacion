#include "protocol.h"

HttpProtocol::HttpProtocol(const Resourcer& resourcer): resourcer(resourcer) {
}

HttpProtocol::~HttpProtocol() {
}

Response* HttpProtocol::handleRequestResponse(const std::string& content) {
    std::pair<std::string, std::string> line;
    line = this->parser.parseRequest(content);
    Checker checker(line);
    std::string response_value = "Content-Type: text/html\n\n";
    if (!checker.isAValidMethod()) return new NotAllowed();
    if (checker.isAPost()) {
        if (!checker.isAValidPostResource()) {
            return new Forbidden();
        }
        this->resourcer.addResource(
            line.second, parser.parseResourceValue(content));
    } else {
        if (!this->resourcer.containsResource(line.second)) {
            return new NotFound();
        }
        response_value += this->resourcer.getResourceValue(line.second);
    }
    return new Ok(response_value);
}

std::string HttpProtocol::getRequestFormat(const std::string& request) const {
    return request.substr(0,request.find_first_of('\n'));
}