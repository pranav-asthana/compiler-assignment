#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
using namespace std;

struct Action {
    int shift;
    int reduce;
    int reduce2;
public:
    Action()
    {
        shift = -1;
        reduce = -1;
        reduce2 = -1;
    }
};

class ParseTable
{

    int states; 
    vector<string> split(const string &text, string sep)
    {
        vector<string> tokens;
        size_t start = 0, end = 0;
        while ((end = text.find(sep, start)) != string::npos) {
            tokens.push_back(text.substr(start, end - start));
            start = end + sep.length();
        }
        tokens.push_back(text.substr(start));
        return tokens;
    }

public:
    vector<vector<Action>> actionTable;
    vector<vector<int>> gotoTable;

    vector<string> nonTerminals;
    vector<string> actionSymbols;

    int getActionSymbolIndex(string symbol)
    {
        auto it = find(actionSymbols.begin(), actionSymbols.end(), symbol);
        return (it - actionSymbols.begin());
    }

    int getNonTerminalIndex(string nonTerminal)
    {
        auto it = find(nonTerminals.begin(), nonTerminals.end(), nonTerminal);
        return (it - nonTerminals.begin());
    }

    int getNonTerminalCount()
    {
        return nonTerminals.size();
    }

    int getActionSymbolCount()
    {
        return actionSymbols.size();
    }
    
    void readParseTableFromFile(string filename)
    {
        string line;
        ifstream input(filename);
        if (input.is_open()) {
            getline(input, line);
        }
        vector<string> res = split(line, "\t");

        int i;
        for (i = 0; i < res.size() && res[i] != "$"; i++) {
            actionSymbols.push_back(res.at(i));
        }
        actionSymbols.push_back(res[i++]);

        for (; i < res.size(); i++) {
            nonTerminals.push_back(res.at(i));
        }

        // cout << "action time\n";
        // for (string x : actionSymbols) {
        //     cout << x << " ";
        // }
        // cout << "\ngoto time\n";
        // for (string x : nonTerminals) {
        //     cout << x << " ";
        // }

        if (input.is_open()) {
            // cout << "start!\n";
            while (getline(input, line)) {
                vector<string> splitLine = split(line, "\t");
                // for (string x : splitLine) {
                //     cout << x << " ";
                // }
                vector<Action> actionList;
                int i = 1;
                for (i = 1; i < getActionSymbolCount(); i++) {
                    Action action;
                    char actionType;
                    int state0;
                    int state1;
                    if (isalpha(splitLine[i][0])) {
                        if (splitLine.at(i).find_first_of("/") == string::npos) {
                            sscanf(splitLine.at(i).c_str(), "%c%d", &actionType, &state0);
                            if (actionType == 's') {
                                action.shift = state0;
                                // cout << "shift " << state0 << endl;
                            } else if (actionType == 'r') {
                                action.reduce = state0;
                                // cout << "reduce " << state0 << endl;
                            } else if (actionType == 'a') {
                                action.shift = -999;
                            }
                        } else {
                            cout << "Conflict in parsing.\n";
                            sscanf(splitLine.at(i).c_str(), "s%d / r%d", &state0, &state1);
                            action.shift = state0;
                            action.reduce = state1;
                            exit(0);
                        }
                        // cout << "s " << action.shift << " r " << action.reduce << "\n";
                        actionList.push_back(action);
                    }
                }
                actionTable.push_back(actionList);

                vector<int> states;
                for (int j = 0; j < getNonTerminalCount(); j++) {
                    int state;
                    string tmp = splitLine.at(i+j);
                    if (isdigit(tmp[0])) {
                        sscanf(tmp.c_str(), "%d", &state);
                    } else {
                        state = -1;
                    }
                    states.push_back(state);
                }
                gotoTable.push_back(states);
            }
        }
        input.close();
    }

    ParseTable(string filename)
    {
        readParseTableFromFile(filename);
        for (auto it = gotoTable.begin(); it != gotoTable.end(); it++) {
            for (auto it0 = it->begin(); it0 != it->end(); it0++) {
                cout << *it0 << " ";
            }
            cout << endl;
        }
    }
};

struct Production {
    string nonTerminalString;
    vector<vector<string>> rules;
};

class Parser {
    stack<int> stateStack;
    stack<string> symbolStack;
    vector<string> input;
    vector<Production> productions;
    vector<string> split(const string &text, string sep)
    {
        vector<string> tokens;
        size_t start = 0, end = 0;
        while ((end = text.find(sep, start)) != string::npos) {
            tokens.push_back(text.substr(start, end - start));
            start = end + sep.length();
        }
        tokens.push_back(text.substr(start));
        return tokens;
    }
public:
    void readRules(string rulesFile)
    {
        string line;

        vector<string> fileContents;
        ifstream input(rulesFile);
        if (input.is_open()) {
            getline(input, line);
            fileContents.push_back(line);
        }
        auto it = fileContents.begin();
        string nonTerm, ruleString;
        vector<string> parsedRule;
        while (it != fileContents.end()) {
            char _nonTerm[512], _ruleString[512];
            sscanf(it->c_str(), "%s -> %s", _nonTerm, _ruleString);
            nonTerm = _nonTerm;
            ruleString = _ruleString;
            Production production;
            production.nonTerminalString = nonTerm;
            parsedRule = split(ruleString, " ");
            production.rules.push_back(parsedRule);
            while (strncmp(it->c_str(), nonTerm.c_str(), nonTerm.length()) == 0) {
                sscanf(it->c_str(), "%s -> %s", _nonTerm, _ruleString);
                parsedRule = split(ruleString, " ");
                production.rules.push_back(parsedRule);
                it++;
            }
            productions.push_back(production);
            it++;
        }
    }

    Parser(vector<string> _input, string filename)
    {
        input = _input;
        ParseTable parseTable(filename);
        stateStack.push(0);
        int inputPtr = 0;
        int s, a;
        while (true) {
            string currentInput = input.at(inputPtr);
            s = stateStack.top();
            a = parseTable.getActionSymbolIndex(currentInput);
            Action action = parseTable.actionTable[s][a];
            if (action.shift == -999) {
                cout << "Parsing completed";
                return;
            }
            if (action.shift != -1) {
                stateStack.push(action.shift);
                inputPtr++;
            } else if (action.reduce != -1) {
                // pop symbols off symbol stack
                string nt;

                s = stateStack.top();
                a = parseTable.getNonTerminalIndex(nt);
                stateStack.push(parseTable.gotoTable[s][a]);
                // cout production
            } else {
                cout << "Oh dear";
                return;
            }
        }
    }


};


int main() 
{
    ParseTable parseTable("tableP");
    return 0;
}