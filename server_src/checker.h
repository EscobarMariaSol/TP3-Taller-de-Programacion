#ifndef CHECKER_H
#define CHECKER_H

#include <string>

class Checker {
private:
    std::pair<std::string, std::string> request;
    bool isAGet() const;

public:
    explicit Checker(std::pair<std::string, std::string>& request);
    ~Checker();
    bool isAValidMethod() const;
    bool isAPost() const;
    bool isAValidPostResource() const;
};

#endif // CHECKER_H
