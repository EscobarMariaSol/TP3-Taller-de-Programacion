#include "thread_client.h"

#define BUFFER_TAM 64

/******************* Métodos Privados de ThreadClient ************************/

void ThreadClient::recvRequest(std::stringbuf& request) {
    int recv = 0;
    char buffer[BUFFER_TAM] = {0};
    do {
		if ((recv = this->peer.recv(buffer, BUFFER_TAM)) == -1);
		request.sputn(buffer, recv);
		memset(buffer, 0, BUFFER_TAM);	
	} while (recv > 0);
    this->peer.shutdown(SHUT_RD);
}

void ThreadClient::sendResponse(Response *response) {
    std::stringbuf str_request; 
    response->getResponse(str_request);
    this->peer.send(str_request.str().c_str(), str_request.str().size());
    this->peer.shutdown(SHUT_WR);
}

/******************* Métodos Públicos de ThreadClient ************************/

ThreadClient::ThreadClient(Socket&& peer, Resourcer& resourcer): 
    peer(std::move(peer)), 
    resourcer(resourcer), 
    running(true) {
}

ThreadClient::~ThreadClient() {
}

void ThreadClient::run() {
    std::stringbuf request;
    recvRequest(request);
    HttpProtocol protocol(std::ref(this->resourcer)); 
    Response *response = protocol.handleRequestResponse(request.str());
    try {
        std::cout << protocol.getRequestFormat(request.str());
        sendResponse(response);
        delete response;
        this->running = false;
    } catch (std::runtime_error& e) {
        if (response) delete response;
        throw std::runtime_error(e.what());
    }
}

void ThreadClient::stop() {
    this->running = false;
    this->peer.shutdown(SHUT_RDWR);
    this->peer.close();
}

bool ThreadClient::hasFinished() const {
    return (!this->running);
}
