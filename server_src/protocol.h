#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <string>
#include <fstream>
#include <utility>
#include "resourcer.h"
#include "checker.h"
#include "parser.h"
#include "response.h"
#include "ok.h"
#include "not_allowed.h"
#include "not_found.h"
#include "forbidden.h"

// Clase correspondiente al Protocolo que despacha petitorios Http
// Cuenta con los siguientes atributos:
// resorcer, correspondiente al repositorio compartido ene el cual se 
// guardan los recursos creados/accedidos por los clientes
class HttpProtocol{
private:
    Resourcer& resourcer;
    Response* handlePostRequest(const Checker& checker, const Parser& parser,
        const std::pair<std::string, std::string>& line);
    Response* handleGetRequest(const Checker& checker, 
        const std::pair<std::string, std::string>& line);

public:
    // Constructor
    explicit HttpProtocol(Resourcer& resourcer);
    // Destructor
    ~HttpProtocol();
    // Método que recibe el contenido de un petitorio, lo procesa, 
    // ejecuta la petición y duvuelve la respuesta
    // pre: recibe un string correspondiente a un petitorio
    // pos: devuelve una respuesta al petitorio
    Response* handleRequestResponse(const std::string& content);
    // Método que devuelve cual fue el formato de la petición extraida
    // del petitorio
    // pre: recibe el petitorio almacenado en un string
    // Pos: devuelve la petición que se halla dentro del mismo
    std::stringbuf getRequestFormat(const std::string& request) const;
};

#endif // REQUEST_HANDLER_H
