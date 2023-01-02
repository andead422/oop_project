#ifndef SECRET_H
#define SECRET_H

#include <string>

using std::string;


inline string getUser(){ return ""; } // sql username

inline string getPass(){ return ""; } // sql user pass

inline string getDB(){ return ""; } // database name

inline string getAPIKey(){ return ""; } // api key from tmdb database

inline const char* getPATH(){ return ""; } // absolute patth to main_model.py file 

#endif