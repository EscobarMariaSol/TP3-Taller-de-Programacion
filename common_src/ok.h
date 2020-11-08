#ifndef OK_H
#define OK_H

#include "response.h"
#include <functional>

class Ok: public Response {
private: 
    std::string value;

public:
    explicit Ok(const std::string& value);
    ~Ok();
    std::pair<std::string, std::string> getResponse() const override;
    void serialize(std::stringbuf& str_serialize) const override;
};

#endif // OK_H
