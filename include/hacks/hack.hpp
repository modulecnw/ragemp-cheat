#pragma once
#include <string>

class Hack {
public:
    virtual std::string getCategory() = 0;
    virtual std::string getName() = 0;
};