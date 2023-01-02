#include "python_from_cpp.hpp"

//Шлях до папки де зберігається python-модуль
const char* path_to_python = getPATH();
//Назва модулю python
const char *python_module_name = "main_model";

PyObject *pName = NULL, *pModule = NULL;
PyObject *pDict = NULL, *pObjct = NULL, *pVal = NULL;
PyObject *sys = NULL;
PyObject *sys_path = NULL;
PyObject *folder_path = NULL;

//Завантаження інтерпретатора python и модуля .py в него.
PyObject *python_init() {
    // Ініціалізування інтерпретатора
    Py_Initialize();

    do {
        // Завантаження модуля sys
        sys = PyImport_ImportModule("sys");
        sys_path = PyObject_GetAttrString(sys, "path");
        // Шлях до нашого модуля python 
        folder_path = PyUnicode_FromString(path_to_python);
        PyList_Append(sys_path, folder_path);

        pName = PyUnicode_FromString(python_module_name);
        if (!pName) {
            break;
        }

        // Завантаження модуля main_model
        pModule = PyImport_Import(pName);
        if (!pModule) {
            break;
        }

        // Cписок об'єктів які зберігаються в main_model
        pDict = PyModule_GetDict(pModule);
        if (!pDict) {
            break;
        }

        return pDict;
    } while (0);

    PyErr_Print();
    return NULL;
}

/*
 * звільнення ресурсів інтерпретатора python
 */
void python_clear() {
    // Повернути ресурси системі
    Py_XDECREF(pDict);
    Py_XDECREF(pModule);
    Py_XDECREF(pName);

    Py_XDECREF(folder_path);
    Py_XDECREF(sys_path);
    Py_XDECREF(sys);
    
    // Вивантаження інтерпретатора Python
    Py_Finalize();
}

char *python_func_get_str(char *val) {
    char *ret = NULL;

    pObjct = PyDict_GetItemString(pDict, (const char *) "recommendation_system");
    if (!pObjct) {
        return ret;
    }

    do {
        if (!PyCallable_Check(pObjct)) {
            break;
        }

        pVal = PyObject_CallFunction(pObjct, (char *) "(s)", val);
        if (pVal != NULL) {
            PyObject* pResultRepr = PyObject_Repr(pVal);

            ret = strdup(PyBytes_AS_STRING(PyUnicode_AsEncodedString(pResultRepr, "utf-8", "ERROR")));

            Py_XDECREF(pResultRepr);
            Py_XDECREF(pVal);
        } else {
            PyErr_Print();
        }
    } while (0);

    return ret;
}

vector<int> split(const string &s, char delimiter) {     
    vector<int> tokens;     
    string token;     
    istringstream tokenStream(s);     
    while (getline(tokenStream, token, delimiter)) {      
        tokens.push_back(stoi(token));     
    }     
    return tokens;  
} 

vector<int> recomended_film(map<int, double> recommended){
    string s = "{\n";

    for(map<int, double>::iterator iter = recommended.begin(); iter != recommended.end(); ++iter)
        s = s + to_string(iter->first) + ": " + to_string(iter->second) + ",\n";
        s = s.substr(0, s.size() - 2);
    s += "\n}";

    char* cstr = new char[s.length()+1];
    strcpy(cstr, s.c_str());

    if (!python_init()) {
        puts("python_init error");

        vector<int> empty;
        return empty;
    }

    string ans = python_func_get_str(cstr);
    ans = ans.substr(1, ans.length() - 3);
    vector <int> int_ans = split(ans, ' ');
    python_clear();
    return int_ans;
}
