#ifndef PARSER_H
#define PARSER_H

#include <exception>
#include "resourcer.h"
#include "response.h"
#include "checker.h"

class Parser {
private:
   std::string getResourceName(const std::string& content) const;
   std::string getMethodName(const std::string& content) const;

public:
    Parser();
    ~Parser();
    std::pair<std::string, std::string> parseRequest(
        const std::string& content) const;
    std::string parseResourceValue(const std::string& content) const;
};

#endif // PARSER_H
