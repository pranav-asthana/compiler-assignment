// #include <iostream>
// #include <fstream>
// #include <stdio.h>

using namespace std;

class Token {
public:
    string tkName;
    string lexeme;
    int tkNum;
    Token(string tkName, string lexeme) {
        this->tkName = tkName;
        this->lexeme = lexeme;
    }
    Token(string tkName, string lexeme, int tkNum) {
        this->tkName = tkName;
        this->lexeme = lexeme;
        this->tkNum = tkNum;
    }
};

/*
FUNCTION: TYPE ID (PARAMS) { STMTS }
PARAMS: PARAM_LIST | NULL
PARAM_LIST: TYPE ID | PARAM_LIST, TYPE ID
*/