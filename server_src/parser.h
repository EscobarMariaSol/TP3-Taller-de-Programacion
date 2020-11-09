#ifndef PARSER_H
#define PARSER_H

#include <exception>
#include <utility>
#include <string>
#include "resourcer.h"
#include "checker.h"

// Clase encarganda de parsear un petitorio, extrayendo la request
// y el value, si esta contiene uno
// Cuenta con un único atributo correspondiente al contenido del
// petitorio que se debe parsear
class Parser {
private:
    const std::string& content;
    // Método que devuelve el nombre del recurso utilizado en el petitorio
    // Pre: el contenido del parser cuenta con el nombre de un recursos
    // Pos: el nombre del recurso ha sido devuelto, si el recurso no se 
    // encuentra, devuelve un string vacío
    std::string getResourceName() const;
    // Método que devuelve el método utilizado en el petitorio
    // Pre: el contenido del parser cuenta con el nombre de un método
    // Pos: el nombre del método ha sido devuelto, si el método no se 
    // encuentra, devuelve un string vacío
    std::string getMethodName() const;

public:
    // Constructor
    explicit Parser(const std::string& content);
    // Destructor
    ~Parser();
    // Método que parsea el contenido del petitorio y devuelve
    // unícamente el método y el recurso a utilizar
    // Pre: el contenido del petitorio cuenta con un método y un recurso
    // Pos: el método y el recurso han sido devueltos como par(método, recurso)
    std::pair<std::string, std::string> parseRequest() const;
    // Método que extrae el valor del recurso desde el contenido del petitorio
    // Pre: el contenido del petitorio contiene un valor para el recurso
    // Pos: el valor del recurso ha sido devuelto, o en su defecto un string
    // vacío, si el petitorio no contiene un valor para el recurso.
    std::string parseResourceValue() const;
};

#endif // PARSER_H
