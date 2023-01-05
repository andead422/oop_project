#ifndef TEMPLATE_H
#define TEMPLATE_H

// template for secret.hpp file, which should be located in this directory

#include <string>

using std::string;


inline string getUser() { return ""; } // sql username

inline string getPass() { return ""; } // sql user pass

inline string getDB() { return ""; } // database name

inline string getAPIKey() { return ""; } // api key from tmdb database

inline const char* getPATH() { return ""; } // absolute path to main_model.py file 

#endif