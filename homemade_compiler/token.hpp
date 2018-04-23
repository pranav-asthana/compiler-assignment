#ifndef TOKEN_H
#define TOKEN_H

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

#endif