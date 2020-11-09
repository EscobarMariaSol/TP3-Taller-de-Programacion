#include "parser.h"

/******************* Métodos Privados de Parser ******************************/

std::string Parser::getResourceName() const {
    size_t start = this->content.find_first_of('/');
    if (start == std::string::npos) return "";
    size_t end = this->content.substr(start).find_first_of(' ');
    return this->content.substr(start, end);
}

std::string Parser::getMethodName() const {
    size_t end = this->content.find_first_of(' ');
    if (end == std::string::npos) return "";
    return this->content.substr(0, end);
}

/******************* Métodos Públicos de Parser ******************************/

Parser::Parser(const std::string& content): content(content) {
}

Parser::~Parser() {
}

std::pair<std::string, std::string> Parser::parseRequest() const {
    return std::pair<std::string, std::string>(
        getMethodName(), getResourceName());
}

std::string Parser::parseResourceValue() const {
    std::string blank_line = "\n\n";
    size_t start = this->content.find(blank_line);
    if (start == this->content.npos) return "";
    return this->content.substr(start + blank_line.size());
}
