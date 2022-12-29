#ifndef INCLUDES_H
#define INCLUDES_H

#include <iostream>
// #include <vector>
// #include <string>
#include <map>
#include <random>

#include "db/database.hpp"

extern DBConnect database;

using std::vector;
using std::map;
using std::pair;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::rand;
using std::max;

// template<typename T>
// extern int findInVector(const vector<T>&, const T&);

// template<typename T>
// extern void addToSet(vector<T>&, const T&);

inline string& to_string(string& str) { return str;}

// template<typename T>
// extern string to_string(const vector<T>&, const string&);


template<typename T>
int findInVector(const vector<T>& vec, const T& element) {
    for(int ii = 0; ii < vec.size(); ++ii) {
        if(vec[ii] == element) {
            return ii;
        }
    }

    return -1;
}

template<typename T>
void addToSet(vector<T>& vec, const T& element) {
    if(findInVector(vec, element) != -1) {
        vec.push_back(element);
    }
}

template<typename T>
string to_string(const vector<T>& vec, const string& delim = ", ") {
    string output;

    for (T i: vec) {
      output += to_string(i) + delim;
    }
    
    output.erase(output.size() - delim.size(), delim.size());

    return output;
}


#endif