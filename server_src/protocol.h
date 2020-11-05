#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <string>
#include <fstream>
#include "resourcer.h"
#include "response.h"
#include "checker.h"
#include "parser.h"
#include "ok.h"
#include "not_allowed.h"
#include "not_found.h"
#include "forbidden.h"

class HttpProtocol{
private:
    Resourcer resourcer;
    Parser parser;

public:
    HttpProtocol(const Resourcer& resourcer);
    ~HttpProtocol();
    Response* handleRequestResponse(const std::string& content);
};

#endif // REQUEST_HANDLER_H
