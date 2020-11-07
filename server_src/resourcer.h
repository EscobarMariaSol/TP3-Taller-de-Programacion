#ifndef RESOURCER_H
#define RESOURCER_H

#include <map>
#include <functional>
#include <iostream>
#include <mutex>

// Clase que almacena los recursos 
// Cuenta con los siguientes parámetros
// resources: este parámetro es un map donde se alamacenan los resursos
class Resourcer {
private:
    std::map<std::string, std::string> resources;
    std::mutex mutex;
    
public:
    Resourcer();
    ~Resourcer();
    Resourcer(const Resourcer& other);
    Resourcer& operator=(const Resourcer& other);
    void addResource(const std::string& resource_name, 
        const std::string& resource_value);
    std::string getResourceValue(const std::string resource_name);
    bool containsResource(const std::string resource_name);
};

#endif // RESOURCER_H
