#ifndef OK_H
#define OK_H

#include "response.h"

class Ok: public Response {
private: 
    std::string value;

public:
    Ok(const std::string& value);
    ~Ok();
    void setResponseValue(const std::string& value);
    std::pair<std::string, std::string> getResponse() const override;
    void serialize(std::stringbuf& str_serialize) const override;
};

#endif // OK_H
