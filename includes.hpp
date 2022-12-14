#ifndef INCLUDES_H
#define INCLUDES_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <python3.10/Python.h>
#include <cctype>
#include <sstream>

#include "db/database.hpp"
#include "secrets/secret.hpp"

extern DBConnect* database;

using std::vector;
using std::map;
using std::pair;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::rand;
using std::max;
using std::to_string;
using std::toupper;
using std::istringstream;

//шукає елемент у векторі
template<typename T>
int findInVector(const vector<T>& vec, const T& element) {
    for(int ii = 0; ii < vec.size(); ++ii) {
        if(vec[ii] == element) {
            return ii;
        }
    }

    return -1;
}

//перевіряє наявність елемента у векторі перед додаванням (вектор відіграє роль множини(set) )
template<typename T>
void addToSet(vector<T>& vec, const T& element) {
    if(findInVector(vec, element) == -1) {
        vec.push_back(element);
    }
}

//база рекурсії
inline string& to_string(string& str) { return str;}

//перетворює вектор у string розділяючи елементи delim-ом, приймає вектор типу для якого визначена функція to_string(type)
template<typename T>
string to_string(const vector<T>& vec, const string& delim = ", ") {
    string output;

    for (T i: vec) {
      output += to_string(i) + delim;
    }
    
    if (output.size() != 0) {
        output.erase(output.size() - delim.size(), delim.size());
    }

    return output;
}


#endif