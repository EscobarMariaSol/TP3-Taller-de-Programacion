#include "parser.h"
#include <iostream>

void parser_request() {
    Parser parser;
    std::pair<std::string, std::string> response;
    bool first, second;
    std::string resp;

    std::cout << "**************Pruebas Parser Request*********************\n";

    std::string petitorio1 = "GET / HTTP/1.1";
    response = parser.parseRequest(petitorio1);
    first = (response.first == "GET");
    second = (response.second == "/");
    resp = (first && second) ? "Ok\n" : "Falló\n";
    std::cout << "\nEl petitorio 1 se parseó correctamente: " << resp;

    std::string petitorio2 = "GET /recurso1 HTTP/1.1";
    response = parser.parseRequest(petitorio2);
    first = (response.first == "GET");
    second = (response.second == "/recurso1");
    resp = (first && second) ? "Ok\n" : "Falló\n";
    std::cout << "\nEl petitorio 2 se parseó correctamente: " << resp;

    std::string petitorio3 = "POST / HTTP/1.1";
    response = parser.parseRequest(petitorio3);
    first = (response.first == "POST");
    second = (response.second == "/");
    resp = (first && second) ? "Ok\n" : "Falló\n";
    std::cout << "\nEl petitorio 3 se parseó correctamente: " << resp;

    std::string petitorio4 = "POST /recurso2 HTTP/1.1";
    response = parser.parseRequest(petitorio4);
    first = (response.first == "POST");
    second = (response.second == "/recurso2");
    resp = (first && second) ? "Ok\n" : "Falló\n";
    std::cout << "\nEl petitorio 4 se parseó correctamente: " << resp;
}

void parser_request_value() {
    Parser parser;
    std::string response;
    std::string resp;

    std::cout << "**************Pruebas Parser Request*********************\n";

    std::string petitorio1 = "GET / HTTP/1.1\nUser-Agent: Wget/1.20.3 (linux-gnu)\nAccept: */*\nAccept-Encoding: identity";
    response = parser.parseResourceValue(petitorio1);
    resp = (response.empty()) ? "Ok\n" : "Falló\n";
    std::cout << "\nEl petitorio 1 se parseó correctamente: " << resp;

    std::string petitorio2 = "GET /recurso1 HTTP/1.1\nUser-Agent: Wget/1.20.3 (linux-gnu)\n\nHola Mundo!";
    response = parser.parseResourceValue(petitorio2);
    resp = (response == "Hola Mundo!") ? "Ok\n" : "Falló\n";
    std::cout << "\nEl petitorio 2 se parseó correctamente: " << resp;
}

int main(int argc, char *argv[]){
    std::cout << "**************Pruebas Parser*****************************\n";
    parser_request();
    parser_request_value();

    return 0;
}