#ifndef PYTHON_FROM_CPP_H
#define PYTHON_FROM_CPP_H

#include "../includes.hpp"

extern const char* path_to_python;
extern const char *python_module_name;

extern PyObject *pName, *pModule;
extern PyObject *pDict, *pObjct, *pVal;
extern PyObject *sys;
extern PyObject *sys_path;
extern PyObject *folder_path;

PyObject *python_init();
void python_clear();
char *python_func_get_str(char*);
vector<int> split(const string&, char);
vector<int> recomended_film(map<int, double>);

#endif
