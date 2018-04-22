#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include <stdio.h>

#include "token.hpp"

using namespace std;

string whitespace = " \n\t";
string digits = "0123456789";
string letter_ = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
string reserved[] = {"", "main", "return", "if", "else", "while"};
string types[] = {"", "int", "float"};
string special[] = {"", ".", ",", "(", ")", "{", "}", "\"", "\'", ";"};
string operators[] = {"", "+", "-", "*", "/", "%"};
string relOps[] = {"GTE", "GT", "LTE", "LT", "EQEQ", "EQ", "NEQ"};

vector<Token> tokens;
vector<string> lexemes;

void addToken(string tkName, string lexeme) {
    ptrdiff_t pos = find(lexemes.begin(), lexemes.end(), lexeme) - lexemes.begin();
    if (pos == lexemes.size()) {
        tokens.push_back(Token(tkName, lexeme, tokens.size()));
        lexemes.push_back(lexeme);
    }
    else {
        tokens.push_back(Token(tkName, lexeme, pos));
    }
}

int belongs(char a, string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (a == str[i])
        {
            return 1;
        }
    }
    return 0;
}

int isState(int s, int states[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (s == states[i])
        {
            return i+1;
        }
    }
    return 0;
}

int belongs2(char * needle, string haystack[])
{
    string needle_str = string(needle);
    int i = 1;
    while (haystack[i].length() > 0)
    {
        if (needle_str.compare(haystack[i]) == 0)
            return i;
        i++;
    }
    return 0;
}

int move(int state, char input)
{

    int transition_table[][23] = {
        {3, 1, -1, 3, 5, 5, -1, -1, 10, -1, -1, 13, -1, -1, 16, -1, -1, -1, -1, -1, 20, -1, -1}, // digits
        {1, 1, -1, 7, -1, 6, -1, -1, 10, -1, -1, 13, -1, -1, 16, -1, -1, -1, -1, -1, 20, -1, -1}, // letter_
        {-1, 2, -1, 4, -1, 6, -1, -1, 10, -1, -1, 13, -1, -1, 16, -1, -1, -1, -1, -1, 20, -1, -1}, // \.
        {8, 2, -1, 7, -1, 6, -1, -1, 10, -1, -1, 13, -1, -1, 16, -1, -1, -1, -1, -1, 20, -1, -1}, // >
        {11, 2, -1, 7, -1, 6, -1, -1, 10, -1, -1, 13, -1, -1, 16, -1, -1, -1, -1, -1, 20, -1, -1}, // <
        {14, 2, -1, 7, -1, 6, -1, -1, 9, -1, -1, 12, -1, -1, 15, -1, -1, 18, -1, -1, 20, -1, -1}, // =
        {17, 2, -1, 7, -1, 6, -1, -1, 10, -1, -1, 13, -1, -1, 16, -1, -1, -1, -1, -1, 20, -1, -1}, // !
        {0, 2, 0, 7, 0, 6, 0, 0, 10, 0, 0, 13, 0, 0, 16, 0, 0, 0, 0, 0, 20, 0, 0}, // whitespace
        {0, 2, 0, 7, 0, 6, 0, 0, 10, 0, 0, 13, 0, 0, 16, 0, 0, 0, 0, 0, 20, 0, 0},  // other
        {19, 2, -1, 7, -1, 6, -1, -1, 10, -1, -1, 13, -1, -1, 16, -1, -1, -1, -1, -1, 20, 22, -1}, // /
        {-1, 2, -1, 7, -1, 6, -1, -1, 10, -1, -1, 13, -1, -1, 16, -1, -1, -1, -1, 20, 21, 21, -1}, // *
    };

    if (belongs(input, digits))
        state = transition_table[0][state];
    else if (belongs(input, letter_))
        state = transition_table[1][state];
    else if (belongs(input, whitespace))
        state = transition_table[7][state];
    else
    {
        switch (input)
        {
            case '.':
            {
                state = transition_table[2][state];
                break;
            }
            case '>':
            {
                state = transition_table[3][state];
                break;
            }
            case '<':
            {
                state = transition_table[4][state];
                break;
            }
            case '=':
            {
                state = transition_table[5][state];
                break;
            }
            case '!':
            {
                state = transition_table[6][state];
                break;
            }
            case '/':
            {
                state = transition_table[9][state];
                break;
            }
            case '*':
            {
                state = transition_table[10][state];
                break;
            }
            default:
            {
                state = transition_table[8][state];
                break;
            }
        }
    }
    return state;
}

char * FA(char * file_name)
{
    // FILE * fp = fopen(file_name, "r");
    ifstream file (file_name);

    int line_number = 1;
    char yytext[100];
    int yylen;

    int int_states[] = {7};
    int float_states[] = {6};
    int id_states[] = {2};
    int rel_op_states[] = {9, 10, 12, 13, 15, 16, 18};
    int comment_states[] = {22};

    char c = file.get();
    while(c > 0)
    {
        char state = 0;
        yylen = 0;
        while(c > 0)
        {
            yytext[yylen] = '\0';
            yytext[yylen+1] = '\0';

            // printf("State:%d c='%c' yytext(%d)=%s\n", state, c, yylen, yytext);
            state = move(state, c);
            // printf("State:%d c='%c' yytext(%d)=%s\n----\n", state, c, yylen, yytext);

            if (isState(state, comment_states, 1))
            {
                yytext[yylen++] = c;
                printf("Comment %s at line %d\n", yytext, line_number);
                addToken("COMMENT", yytext);
                c = file.get();
                break;
            }

            int tkNum;
            // Check for operators
            if (tkNum = belongs2(yytext, operators) && state == 0)
            {
                yytext[yylen] = '\0';
                printf("Operator[%d] %s at line %d\n", tkNum, yytext, line_number);
                addToken("OPERATOR", yytext);
                c = file.get();
                break;
            }
            // Check for special symbols
            // printf("belongs2(%s, special) = %d\n", yytext, belongs2(yytext, special));
            if (tkNum = belongs2(yytext, special))// && state == 0)
            {
                yytext[yylen] = '\0';
                printf("Symbol[%d] %s at line %d\n", tkNum, yytext, line_number);
                addToken("SYMBOL", yytext);
                // c = file.get();
                break;
            }
            // Check for data types
            if (tkNum = belongs2(yytext, types))
            {
                printf("Type[%d] %s at line %d\n", tkNum, yytext, line_number);
                addToken("TYPE", yytext);
                break;
            }
            // Check for reserved words
            if (tkNum = belongs2(yytext, reserved))
            {
                printf("Reseved word[%d] %s at line %d\n", tkNum, yytext, line_number);
                addToken("KEYWORD", yytext);
                break;
            }


            int op_id;
            if (op_id = isState(state, rel_op_states, 7))
            {
                string op = relOps[op_id-1];
                // addToken("RELOP", yytext); // Will be like "<="
                addToken("RELOP", op); // Will be like "LTE"
                cout << "Relational operator[] " << op <<" at line "<< line_number << endl;
                if (op.length() > 2)
                    c = file.get();
                break;
            }
            if (isState(state, int_states, 1))
            {
                printf("Int %s at line %d\n", yytext, line_number);
                // addToken("INT", yytext);
                addToken("NUM", yytext);
                break;
            }
            else if (isState(state, float_states, 1))
            {
                printf("Float %s at line %d\n", yytext, line_number);
                // addToken("FLOAT", yytext);
                addToken("NUM", yytext);
                break;
            }
            else if(isState(state, id_states, 1))
            {
                printf("ID %s at line %d\n", yytext, line_number);
                addToken("ID", yytext);
                break;
            }
            else if (state == -1 && yylen > 0) // invalid
            {
                printf("Unidentified token: '%s'(%d) at line %d\n", yytext, yylen, line_number);
                printf("Lexical error\n");
                return 0;
            }
            else if (state == -1 && yylen == 0)
            {
              state = 0;
            }

            if (belongs(c, whitespace) == 0 || state >= 19)
                yytext[yylen++] = c;
            c = file.get();

            if (c == '\n')
                line_number++;
        }
        if (belongs(c, whitespace))
        {
            c = file.get();
            continue;
        }
    }
    file.close();

    cout << "Num of tokens = " << tokens.size() << endl;
    for (int i = 0; i < tokens.size(); i++) {
        cout << tokens.at(i).tkName << " ";
        cout << tokens.at(i).lexeme << " ";
        cout << tokens.at(i).tkNum << endl;
    }
}

int main()
{
    // id = [a-zA-Z_][a-zA-Z_0-9]*
    // float = int.int
    // whitespace = [ \n\t]
    // special = . // Anything else

    // char * result = FA("mini.c");
    char * result = FA("input.c");

    return 0;
}
