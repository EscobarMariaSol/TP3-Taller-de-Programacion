#include "protocol.h"
#include <iostream>

int main(int argc, char *argv[]){
    std::cout << "**************Pruebas Protocol***************************\n";
    bool first, second;
    std::string resp;
    Resourcer resourcer;
    HttpProtocol protocol(resourcer);
    
    std::cout << "\n**************Pruebas Protocol POST OK*****************\n";
    
    Response *response1;
    std::string petitorio1 = "POST /rec HTTP/1.1\nUser-Agent: Wget/1.20.3 (linux-gnu)\nAccept: */*\n\nHOLA!!";
    response1 = protocol.handleRequestResponse(petitorio1);
    first = (response1->getResponse().first == "HTTP 200 OK\n");
    second = (response1->getResponse().second == "Content-Type: text/html\n\n");
    resp = (first && second) ? "Ok\n" : "Falló\n";
    std::cout << "La respuesta coincide con lo esperado: "<< resp;
    std::cout<<response1->getResponse().first<< response1->getResponse().second<<"\n";
    delete response1;
    std::cout << "\n**************Pruebas Protocol GET OK******************\n";
    
    Response *response2;
    std::string petitorio2 = "GET /rec HTTP/1.1\nUser-Agent: Wget/1.20.3 (linux-gnu)\nAccept: */*\n\n";
    response2 = protocol.handleRequestResponse(petitorio2);
    first = (response2->getResponse().first == "HTTP 200 OK\n");
    second = (response2->getResponse().second == "Content-Type: text/html\n\nHOLA!!");
    resp = (first && second) ? "Ok\n" : "Falló\n";
    std::cout << "La respuesta coincide con lo esperado: "<< resp;
    std::cout<<response2->getResponse().first<< response2->getResponse().second<<"\n";
    delete response2;

    std::cout << "\n**************Pruebas Protocol GET NOT FOUND***********\n";
    
    Response *response3;
    std::string petitorio3 = "GET /ast HTTP/1.1\nUser-Agent: Wget/1.20.3 (linux-gnu)\nAccept: */*\n\n";
    response3 = protocol.handleRequestResponse(petitorio3);
    first = (response3->getResponse().first == "HTTP 404 NOT FOUND\n\n");
    second = (response3->getResponse().second == "");
    resp = (first && second) ? "Ok\n" : "Falló\n";
    std::cout << "La respuesta coincide con lo esperado: "<< resp;
    std::cout<<response3->getResponse().first<< response3->getResponse().second<<"\n";
    delete response3;

    std::cout << "\n**************Pruebas Protocol POST FORBIDDEN**********\n";
    
    Response *response4;
    std::string petitorio4 = "POST / HTTP/1.1\nUser-Agent: Wget/1.20.3 (linux-gnu)\nAccept: */*\n\nHOLA!!";
    response4 = protocol.handleRequestResponse(petitorio4);
    first = (response4->getResponse().first == "HTTP 403 FORBIDDEN\n\n");
    second = (response4->getResponse().second == "");
    resp = (first && second) ? "Ok\n" : "Falló\n";
    std::cout << "La respuesta coincide con lo esperado: "<< resp;
    std::cout<<response4->getResponse().first<< response4->getResponse().second<<"\n";
    delete response4;
    
    std::cout << "\n**************Pruebas Protocol METHOD NOT ALLOWED******\n";
    
    Response *response5;
    std::string petitorio5 = "PUT / HTTP/1.1\nUser-Agent: Wget/1.20.3 (linux-gnu)\nAccept: */*\n\nHOLA!!";
    response5 = protocol.handleRequestResponse(petitorio5);
    first = (response5->getResponse().first == "HTTP 405 METHOD NOT ALLOWED\n\n");
    second = (response5->getResponse().second == "");
    resp = (first && second) ? "Ok\n" : "Falló\n";
    std::cout << "La respuesta coincide con lo esperado: "<< resp;
    std::cout<<response5->getResponse().first<< response5->getResponse().second<<"\n";
    delete response5;
    
    
    return 0;
}