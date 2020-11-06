#include "io_handler.h"

int main(int argc, char *argv[]){
    std::cout << "**************Pruebas IOHandler**************************\n";
    std::cout << "\n************Pruebas IOHandler Input File***************\n";
    IOHandler handler("prueba_1.txt");
    std::stringbuf buffer;
    handler.getInput(buffer);
    std::cout<<buffer.str();

    std::cout << "\n************Pruebas IOHandler sin Input File***********\n";
    IOHandler handler1("");
    std::stringbuf buffer1;
    handler1.getInput(buffer1);
    std::cout<<buffer1.str();

    std::cout << "**************Pruebas IOHandler**************************\n";
    std::cout << "\n************Pruebas IOHandler Input/output File********\n";
    IOHandler handler2("prueba_1.txt");
    std::stringbuf buffer2;
    handler2.getInput(buffer2);
    handler2.setOutput(buffer2);
    std::cout<<"\n";
    return 0;
}