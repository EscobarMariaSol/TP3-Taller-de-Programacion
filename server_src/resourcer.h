#ifndef RESOURCER_H
#define RESOURCER_H

#include <map>
#include <functional>
#include <iostream>
#include <mutex>
#include <string>
#include <utility>

// Clase correspondiente al repositorio donde se almacenan los recursos 
// Cuenta con los siguientes atributos
// resources: este atributo es un map donde se alamacenan los resursos
// mutex: correspondiente al mutex que se utilizará para evitar que
// un thread interrumpa a otro mientra realiza operaciones sobre el repositorio
class Resourcer {
private:
    std::map<std::string, std::string> resources;
    std::mutex mutex;
    
public:
    // Constructor
    Resourcer();
    // Destructor
    ~Resourcer();
    // constructor por referencia
    Resourcer(const Resourcer& other);
    // Asignación por referencia
    Resourcer& operator=(const Resourcer& other);
    // Método que agrega un recurso al repositorio
    // Pre: recibe el nombre del recurso y su contenido, ambos strings
    // Pos: el recurso ha sido guardado, en caso de un error se lanzará
    // una excepción, informando del mismo
    void addResource(const std::string& resource_name, 
        const std::string& resource_value);
    // Método que obtiene el valor de un recurso
    // pre: recibe el nombre del recurso en un string
    // Pos: si el recurso se encuentra en el repositorio devuelve su 
    // contenido, sino devuelve un string vacío
    std::string getResourceValueIfExist(const std::string& resource_name);
};

#endif // RESOURCER_H
