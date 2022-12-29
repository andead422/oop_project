#include "includes.hpp"

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
    
    output.erase(0, output.size() - delim.size());

    return output;
}