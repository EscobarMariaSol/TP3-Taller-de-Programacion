#ifndef OK_H
#define OK_H

#include "response.h"
#include <functional>
#include <utility>
#include <string>
#include <sstream>

// Clase correspondiente a la respuesta Ok del protocolo http
// Cuenta con un único atributo correspondiente al valor de la
// respuesta, que puede ser el valor de un recurso almacenado luego
// de realizar un POST o el valor de un recurso obtenido con un GET
class Ok: public Response {
private: 
    std::string value;

public:
    // Constructor
    explicit Ok(const std::string& value);
    // Destructor
    ~Ok();
    // Método heredado de la calse Response
    void operator()(std::stringbuf& str_serialize) override;
};

#endif // OK_H
