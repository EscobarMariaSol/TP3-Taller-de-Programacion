#ifndef RESPONSE_H
#define RESPONSE_H

#include <sstream>
#include <string>
#include <utility>

// Clase Abstracta correspondiente a la clase respuesta del 
// protocolo http.
class Response {
public:
    // Constructor
    Response();
    // Destructor
    virtual ~Response();
    // Método que devuelve la respuesta almacenada dentro de la clase
    // El método debe ser implementado obligatoriamente por las clases
    // que hereden de Response
    // Pre: recibe un buffer en el cual se almacenara la respuesta
    // Pos: la respuesta ha sido almacenada en el buffer
    virtual void operator()(std::stringbuf& str_serialize) = 0;
};

#endif // RESPONSE_H
