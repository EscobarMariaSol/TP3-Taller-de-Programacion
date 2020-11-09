#ifndef NOT_ALLOWED_H
#define NOT_ALLOWED_H

#include "response.h"
#include <utility>
#include <string>
#include <sstream>

// Clase correspondiente a la respuesta Not Allowed
class NotAllowed: public Response {
private:
    std::string value;
    
public:
    explicit NotAllowed(const std::string& value);
    ~NotAllowed();
    std::pair<std::string, std::string> getResponse() const override;
    void serialize(std::stringbuf& str_serialize) const override;
};

#endif // NOT_ALLOWED_H
