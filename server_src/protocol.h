#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <string>
#include <fstream>
#include "resourcer.h"
#include "../common_src/response.h"
#include "checker.h"
#include "parser.h"
#include "../common_src/ok.h"
#include "../common_src/not_allowed.h"
#include "../common_src/not_found.h"
#include "../common_src/forbidden.h"

class HttpProtocol{
private:
    Resourcer resourcer;
    Parser parser;

public:
    HttpProtocol(const Resourcer& resourcer);
    ~HttpProtocol();
    Response* handleRequestResponse(const std::string& content);
    std::string getRequestFormat(const std::string& request) const;
};

#endif // REQUEST_HANDLER_H
