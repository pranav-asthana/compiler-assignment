#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <stdint.h>
#include <ctype.h>
#include <string.h>

#include "Action.h"
#include "Rule.h"

using namespace std;

class Parser {
    struct Production {
        string nonTerminalString;
        vector<vector<string>> rules;
    };

    stack<int> stateStack;
    stack<string> symbolStack;
    vector<string> input;
    vector<Production> productions;
    vector<Rule> ruleList;
    int parseFailItr = 0;
    vector<string> split(const string &text, string sep);
    template <class T>
    void printStack(stack<T> _stack);

public:
    void readRules(string rulesFile);
    Parser(string _input, string filename, string rulesFile);
    Parser(string rulesFile);
};
 
#endif