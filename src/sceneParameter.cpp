#include "sceneParameter.h"

void Parameter::set(std::string key, int val){
    _map[key] = val;
}

int Parameter::get(std::string key) const
{
    auto it = _map.find(key);
    if(_map.end() == it){
        return -1; //error
    }else{
        return it->second;
    }
}

