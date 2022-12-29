#ifndef INCLUDES_H
#define INCLUDES_H

#include <iostream>
// #include <vector>
// #include <string>
#include <map>
#include <random>

#include "db/database.hpp"

extern DBConnect database;

// using std::vector;
using std::map;
using std::pair;
// using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::rand;
using std::max;

template<typename T>
int findInVector(const vector<T>&, const T&);

template<typename T>
void addToSet(vector<T>&, const T&);

string& to_string(string& str) { return str;}

template<typename T>
string to_string(const vector<T>&, const string&);


#endif