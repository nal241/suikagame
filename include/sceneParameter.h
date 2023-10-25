
#pragma once
#include <unordered_map>

class Parameter{
public:
    void set(std::string key, int val); 
    int get(std::string key) const;
private:
    std::unordered_map<std::string, int> _map;
};