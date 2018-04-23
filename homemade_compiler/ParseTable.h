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

    // Splits a string based on the delimiter

    vector<string> split(const string &text, string sep);

public:
    vector<vector<Action>> actionTable;
    vector<vector<int>> gotoTable;

    vector<string> nonTerminals;
    vector<string> actionSymbols;

    // Finds the index of a given symbol defined in the first row of the Action table in the provided parse table

    int getActionSymbolIndex(string symbol);
    int getNonTerminalIndex(string nonTerminal);

    int getNonTerminalCount();
    int getActionSymbolCount();

    // Reads the parse table from a file, parses it and stores it in our own separate tables for Actions and Goto transitions

    void readParseTableFromFile(string filename);
    ParseTable(string filename);
}; 
 
#endif