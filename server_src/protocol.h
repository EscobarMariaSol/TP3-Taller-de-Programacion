#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <string>
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
    Response* handleRequestResponse(const std::string& content);

public:
    HttpProtocol(Resourcer& resourcer);
    ~HttpProtocol();
};

#endif // REQUEST_HANDLER_H
