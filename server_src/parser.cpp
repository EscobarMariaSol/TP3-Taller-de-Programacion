#include "parser.h"

/******************* Métodos Privados de Parser ******************************/

std::string Parser::getResourceName(const std::string& content) const {
    size_t start = content.find_first_of('/');
    size_t end = content.substr(start).find_first_of(' ');
    return content.substr(start, end);
}

std::string Parser::getMethodName(const std::string& content) const {
    size_t end = content.find_first_of(' ');
    return content.substr(0, end);
}

/******************* Métodos Públicos de Parser ******************************/

Parser::Parser() {
}

Parser::~Parser() {
}

std::pair<std::string, std::string> Parser::parseRequest(
    const std::string& content) const {
    return std::pair<std::string, std::string>(
        getMethodName(content), getResourceName(content));
}

std::string Parser::parseResourceValue(const std::string& content) const {
    std::string blank_line = "\n\n";
    size_t start = content.find(blank_line);
    if (start == content.npos) return "";
    return content.substr(start + blank_line.size());
}
