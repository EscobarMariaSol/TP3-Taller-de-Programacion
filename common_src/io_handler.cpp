#include "io_handler.h"

IOHandler::IOHandler(){
}

IOHandler::IOHandler(const std::string path) {
    if (!path.empty()) {
        this->file.open(path, std::fstream::in);
        if (this->file.fail())
            throw std::runtime_error("File cannot be open.");
    }
}

IOHandler::~IOHandler() {
    if (this->file.is_open())
        this->file.close();
}

void IOHandler::getInput(std::stringbuf& buffer) {
    if (this->file.is_open() && !this->file.eof()) {
        this->file.get(buffer, EOF);
        if (this->file.fail())
            throw std::runtime_error("Input cannot be get.");
    } else {
        std::cin.get(buffer, EOF);
    }
}

void IOHandler::setOutput(const std::stringbuf& msg) {
    std::cout << msg.str();
}

void IOHandler::getChar(char& c) {
    std::cin.read(&c, 1);
}