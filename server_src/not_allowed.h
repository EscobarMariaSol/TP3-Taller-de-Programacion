#ifndef NOT_ALLOWED_H
#define NOT_ALLOWED_H

#include "response.h"
#include <utility>
#include <string>
#include <sstream>

// Clase correspondiente a la respuesta Not Allowed del protocolo http
// Cuenta con un único atributo correspondiente al valor de la respuesta,
// este constará del método que se intentó utilizar y la leyenda de la no
// disponibilidad de este método
class NotAllowed: public Response {
private:
    std::string value;
    
public:
    // Constructor
    explicit NotAllowed(const std::string& value);
    // Destructor
    ~NotAllowed();
    // Método heredado de la clase Response
    void getResponse(std::stringbuf& str_serialize) override;
};

#endif // NOT_ALLOWED_H
