#include "checker.h"

/******************* Métodos Privados de Checker *****************************/

bool Checker::isAGet() const {
    return (this->request.first == "GET");
}

/******************* Métodos Públicos de Checker *****************************/

Checker::Checker(const std::pair<std::string, std::string>& request): 
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

bool Checker::isRootResource() const {
    return (this->request.second != "/");
}
