#include "client.h"

#define BUFFER_TAM 64

/******************* Métodos Privados de Client ******************************/

void Client::sendRequest(const std::stringbuf& buffer) {
    this->socket.send(buffer.str().c_str(), buffer.str().size());
    this->socket.shutdown(SHUT_WR);
}

void Client::recvResponse(std::stringbuf& response) {
    int recv = 0;
    char buffer[BUFFER_TAM] = {0};
    do {
		recv = this->socket.recv(buffer, BUFFER_TAM);
		response.sputn(buffer, recv);
		memset(buffer, 0, BUFFER_TAM);	
	} while (recv > 0);
    this->socket.shutdown(SHUT_RD);
}

/******************* Métodos Públicos de Client ******************************/

Client::Client(const char* host, const char* port): 
    socket(host, port), handler() {
}

Client::~Client() {
}

void Client::run() {
    try {
        std::stringbuf buffer;
        handler.getInput(buffer);
        sendRequest(buffer);
        std::stringbuf response;
        recvResponse(response);
        handler.setOutput(response);
    } catch(const std::exception& e) {
        syslog(LOG_CRIT, "Error: %s", e.what());
    } catch (...) {
            syslog(LOG_CRIT, "Unknown Error\n");
    }
}
