#pragma once
#include <string>
#include <concepts>


class Pricer {
public:
    std::string getName() const {
        return name;
    }
    explicit Pricer(std::string name) : name(std::move(name)) {}
private:
    std::string name;
};
