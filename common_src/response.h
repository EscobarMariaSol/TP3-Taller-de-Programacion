#ifndef RESPONSE_H
#define RESPONSE_H

#include <sstream>
#include <string>
#include <utility>

// Clase Abstracta correspondiente a la clase respuesta del 
// protocolo http.
class Response {
public:
    Response();
    virtual ~Response();
    virtual std::pair<std::string, std::string> getResponse() const = 0;
    virtual void serialize(std::stringbuf& str_serialize) const = 0;
};

#endif // RESPONSE_H
