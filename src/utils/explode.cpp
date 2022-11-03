//
// Created by natha on 01/11/2022.
//


#include <vector>
#include <string>
#include <sstream>
#include "explode.h"

std::vector<std::string> explode(std::string const & s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); )
    {
        result.push_back(std::move(token));
    }

    return result;
}