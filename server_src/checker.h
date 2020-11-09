#ifndef CHECKER_H
#define CHECKER_H

#include <string>
#include <utility>

// Clase que chequea la request de un petitorio
// Cuenta con un único atributo correspondiente al par 
// (request, recurso) que utilizará el protocolo http
class Checker {
private:
    std::pair<std::string, std::string> request;
    // Méto booleano para chequear si la request corresponde a un GET
    // Pos: devuelve true en caso de ser un GET o false en caso contrario
    bool isAGet() const;

public:
    // Constructor
    explicit Checker(const std::pair<std::string, std::string>& request);
    // Destructor
    ~Checker();
    // Método para chequear si el método recibido en la request es válido
    // Pos: devuelve true en caso de ser un GET o POST, sino 
    // false en caso contrario
    bool isAValidMethod() const;
    // Método para chequear si el método recibido en la request es un POST
    // Pos: devuelve true en caso de ser un POST, sino false en caso contrario
    bool isAPost() const;
    // Método para chequear si el recurso recibido en la request corresponde al
    // recurso root del servidor
    // Pos: devuelve true en caso de ser el recurso root, sino 
    // false en caso contrario
    bool isRootResource() const;
};

#endif // CHECKER_H
