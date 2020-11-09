#ifndef IO_HANDLER_H
#define IO_HANDLER_H

#include <fstream>
#include <sstream>
#include <utility>
#include <string>
#include <iostream>
#include <functional>

// clase encargada de interactuar con la entrada y salida estándar de datos
class IOHandler {
private:
    std::fstream file;
    
public:
    IOHandler();
    explicit IOHandler(const std::string& path);
    ~IOHandler();
    void getInput(std::stringbuf& buffer);
    void setOutput(const std::stringbuf& msg);
    void getChar(char& c);
};

#endif // IO_HANDLER
