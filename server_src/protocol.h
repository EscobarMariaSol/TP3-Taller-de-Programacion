#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <string>
#include <fstream>
#include "resourcer.h"
#include "../common_src/response.h"
#include "checker.h"
#include "parser.h"
#include "../common_src/ok.h"
#include "../common_src/not_allowed.h"
#include "../common_src/not_found.h"
#include "../common_src/forbidden.h"

// Clase correspondiente al Protocolo que despacha petitorios Http
// Cuenta con los siguientes atributos:
// resorcer, correspondiente al repositorio compartido ene el cual se 
// guardan los recursos creados/accedidos por los clientes
// parser, correspondiente al parser que se encarga de extraer
// la solicitud que se encuentra dentro del petitorio
class HttpProtocol{
private:
    Resourcer resourcer;
    Parser parser;
    Response* handlePostRequest(Checker& checker, const std::string& content, 
        std::pair<std::string, std::string> line);
    Response* handleGetRequest(Checker& checker, 
        std::pair<std::string, std::string> line);

public:
    // Constructor
    HttpProtocol(const Resourcer& resourcer);
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
    std::string getRequestFormat(const std::string& request) const;
};

#endif // REQUEST_HANDLER_H
