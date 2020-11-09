#ifndef IO_HANDLER_H
#define IO_HANDLER_H

#include <fstream>
#include <sstream>
#include <utility>
#include <string>
#include <iostream>
#include <functional>

// Clase encargada de interactuar con la entrada y salida estándar de datos
// Cuenta con un único atributo correspondiente al file desde el cual se 
// leeran los datos, si no cuenta con el mismo se utilizaran la entrada 
// estándar, para el caso de la salida, siempre se utilizará la salida 
// estándar
class IOHandler {
private:
    std::fstream file;
    
public:
    // Constructor sin file
    IOHandler();
    // Constructor con file
    explicit IOHandler(const std::string& path);
    // Destructor
    ~IOHandler();
    // Método para obtener el contenido de un archivo o de la entrada estándar
    // Pre: recibe un buffer en el cual almacenar el contenido
    // Pos: el contenido ha sido almacenado, en caso de que ocurra algún error
    // se lanzará una excepción informando del mismo
    void getInput(std::stringbuf& buffer);
    // Método que muestra un mensaje por salida estándar
    // Pre: recibe un mensaje por parámetro
    // Pos: el mensaje ha sido mostrado por la salida estándar
    void setOutput(const std::stringbuf& msg);
    // Método que obtiene un caracter por entrada estándar
    // Pre: recibe una referencia a la variable donde se almacenará el caracter
    // Pos: se ha leído un caracter por entrada estándar y se ha almacenado 
    // dentro de la variable especificada
    void getChar(char& c);
};

#endif // IO_HANDLER
