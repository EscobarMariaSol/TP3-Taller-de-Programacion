#include "resourcer.h"

/******************* Métodos Públicos de Resourcer ***************************/

Resourcer::Resourcer(): resources() {
}

Resourcer::~Resourcer() {
}

Resourcer::Resourcer(const Resourcer& other) {
    this->resources = std::ref(other.resources);
}

Resourcer& Resourcer::operator=(const Resourcer& other) {
    this->resources = std::ref(other.resources);
    return *this;
}

void Resourcer::addResource(const std::string& resource_name, 
    const std::string& resource_value) {
    std::lock_guard<std::mutex> lock(this->mutex);
    if (this->resources.insert(
            std::pair<std::string, std::string>(
                resource_name, resource_value)).second == false) {
                    throw std::runtime_error("The resource cannot be saved.");
    }
}

std::string Resourcer::getResourceValue(const std::string& resource_name) {
    std::lock_guard<std::mutex> lock(this->mutex);
    std::map<std::string, std::string>::const_iterator it;
    it = this->resources.find(resource_name);
    if (it == this->resources.end()) return "";
    return it->second;
}

bool Resourcer::containsResource(const std::string& resource_name) {
    std::lock_guard<std::mutex> lock(this->mutex);
    std::map<std::string, std::string>::const_iterator it;
    it = this->resources.find(resource_name);
    return (it != this->resources.end());
}
