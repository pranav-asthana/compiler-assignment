#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <stdint.h>
#include <ctype.h>
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
                            } else {
                                action.reduce = state0;
                                // cout << "reduce " << state0 << endl;
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

class Parser {
    stack<int> stateStack;
    stack<string> symbolStack;
    vector<string> input;
public:
    Parser(vector<string> _input, string filename)
    {
        input = _input;
        ParseTable parseTable(filename);
        stateStack.push(0);
        int inputPtr = 0;

        while (true) {
            string currentInput = input.at(inputPtr);
            int s = stateStack.top();
            int a = ParseTable.getActionSymbolIndex(currentInput);
            if (ParseTable.actionTable[s][a].) {

            }
        }
    }


};


int main() 
{
    ParseTable parseTable("tableP");
    return 0;
}