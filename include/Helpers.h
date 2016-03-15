#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>

std::vector<float> &split(const std::string &s, char delim, std::vector<float> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(atoi(item.c_str()));
    }
    return elems;
}

std::vector<float> split(const std::string &s, char delim)
{
    std::vector<float> elems;
    split(s, delim, elems);
    return elems;
}

#endif // HELPERS_H_INCLUDED
