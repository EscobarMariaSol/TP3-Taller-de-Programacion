#ifndef CHECKER_H
#define CHECKER_H

#include <string>
#include <utility>

class Checker {
private:
    std::pair<std::string, std::string> request;
    bool isAGet() const;

public:
    explicit Checker(const std::pair<std::string, std::string>& request);
    ~Checker();
    bool isAValidMethod() const;
    bool isAPost() const;
    bool isRootResource() const;
};

#endif // CHECKER_H
