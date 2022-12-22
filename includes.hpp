#ifndef includes
#define includes

#include <iostream>
// #include <vector>
// #include <string>
#include <map>
#include <random>

#include "database.hpp"

// using std::vector;
using std::map;
using std::pair;
// using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::rand;

template<typename T>
int findInVector(const vector<T>& vec, const T& element) {
    for(int ii = 0; ii < vec.size(); ++ii) {
        if(vec[ii] == element) {
            return ii;
        }
    }

    return -1;
}

#endif