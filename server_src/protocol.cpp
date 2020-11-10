#include "protocol.h"

/**************** Métodos Privados de HttpProtocol ***************************/

Response* HttpProtocol::handlePostRequest(const Checker& checker, 
    const Parser& parser, const std::pair<std::string, std::string>& line) {
    std::string response_value = parser.parseResourceValue();
    if (!checker.isRootResource()) return new Forbidden();
    this->resourcer.addResource(
        line.second, response_value);
    return new Ok("\n" + response_value);
}

Response* HttpProtocol::handleGetRequest(const Checker& checker, 
    const std::pair<std::string, std::string>& line) {
    std::string response_value = "Content-Type: text/html\n\n";
    if (!this->resourcer.containsResource(line.second))
        return new NotFound();
    else 
        response_value += this->resourcer.getResourceValue(line.second);
    return new Ok(response_value);
}
    

/**************** Métodos públicos de HttpProtocol ***************************/

HttpProtocol::HttpProtocol(Resourcer& resourcer): resourcer(resourcer) {
}

HttpProtocol::~HttpProtocol() {
}

Response* HttpProtocol::handleRequestResponse(const std::string& content) {
    std::pair<std::string, std::string> line;
    Parser parser(content);
    line = parser.parseRequest();
    Checker checker(line);
    if (!checker.isAValidMethod()) return new NotAllowed(line.first);
    else if (checker.isAPost()) 
        return handlePostRequest(checker, parser, line);
    return handleGetRequest(checker, line);
}

std::stringbuf HttpProtocol::getRequestFormat(
    const std::string& request) const {
    std::stringbuf result;
    result.sputn(
        request.substr(0,request.find_first_of('\n') + 1).c_str(),
        request.find_first_of('\n') + 1);
    return result;
}
