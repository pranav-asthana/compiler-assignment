#ifndef PARSETABLE_H
#define PARSETABLE_H

#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <stdint.h>
#include <ctype.h>
#include <string.h>

#include "Action.h"

using namespace std;


class ParseTable
{
    int states; 
    vector<string> split(const string &text, string sep);

public:
    vector<vector<Action>> actionTable;
    vector<vector<int>> gotoTable;

    vector<string> nonTerminals;
    vector<string> actionSymbols;

    int getActionSymbolIndex(string symbol);
    int getNonTerminalIndex(string nonTerminal);
    int getNonTerminalCount();
    int getActionSymbolCount();    
    void readParseTableFromFile(string filename);
    ParseTable(string filename);
}; 
 
#endif