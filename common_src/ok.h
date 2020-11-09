#ifndef OK_H
#define OK_H

#include "response.h"
#include <functional>
#include <utility>
#include <string>
#include <sstream>

// Clase correspondiente a la respuesta Ok
class Ok: public Response {
private: 
    std::string value;

public:
    explicit Ok(const std::string& value);
    ~Ok();
    void getResponse(std::stringbuf& str_serialize) override;
};

#endif // OK_H
