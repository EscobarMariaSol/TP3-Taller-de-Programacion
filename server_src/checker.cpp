#include "checker.h"

/******************* Métodos Privados de Checker *****************************/

bool Checker::isAGet() const {
    return (this->request.first == "GET");
}

/******************* Métodos Públicos de Checker *****************************/

Checker::Checker(std::pair<std::string, std::string>& request): 
    request(request) {
}

Checker::~Checker() {
}

bool Checker::isAPost() const {
    return (this->request.first == "POST");
}

bool Checker::isAValidMethod() const {
    return (isAGet() || isAPost());
}

bool Checker::isAValidPostResource() const {
    return (this->request.second != "/");
}
