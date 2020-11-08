#include "protocol.h"

/**************** Métodos Privados de HttpProtocol ***************************/

Response* HttpProtocol::handlePostRequest(Checker& checker, const std::string& content, 
    std::pair<std::string, std::string> line) {
    std::string response_value = this->parser.parseResourceValue(content);
    if (!checker.isRootResource()) return new Forbidden();
    this->resourcer.addResource(
        line.second, response_value);
    return new Ok("\n" + response_value);
}

Response* HttpProtocol::handleGetRequest(Checker& checker, 
    std::pair<std::string, std::string> line) {
    std::string response_value = "Content-Type: text/html\n\n";
    if (!this->resourcer.containsResource(line.second))
        return new NotFound();
    else 
        response_value += this->resourcer.getResourceValue(line.second);
    return new Ok(response_value);
}
    

/**************** Métodos públicos de HttpProtocol ***************************/

HttpProtocol::HttpProtocol(const Resourcer& resourcer): resourcer(resourcer) {
}

HttpProtocol::~HttpProtocol() {
}

Response* HttpProtocol::handleRequestResponse(const std::string& content) {
    std::pair<std::string, std::string> line;
    line = this->parser.parseRequest(content);
    Checker checker(line);
    if (!checker.isAValidMethod()) return new NotAllowed(line.first);
    else if (checker.isAPost()) 
        return handlePostRequest(checker, content, line);
    return handleGetRequest(checker, line);
}

std::string HttpProtocol::getRequestFormat(const std::string& request) const {
    return request.substr(0,request.find_first_of('\n') + 1);
}