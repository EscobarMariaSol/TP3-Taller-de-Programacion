#ifndef IO_HANDLER_H
#define IO_HANDLER_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <functional>

class IOHandler {
private:
    std::fstream file;
    
public:
    IOHandler(const std::string path);
    ~IOHandler();
    void getInput(std::stringbuf& buffer);
    void setOutput(const std::stringbuf& msg);
};

#endif // IO_HANDLER