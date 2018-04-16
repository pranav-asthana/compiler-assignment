#include <fstream>
#include <iostream>
#include <vector>
#include <stdint.h>
using namespace std;

class ParseTable
{
    struct Action {
        uint8_t shift;
        uint8_t reduce;
    };

    uint8_t states;
    vector<vector<Action>> actionTable;
    vector<vector<uint8_t>> gotoTable;

    vector<string> nonTerminals;
    vector<string> actionSymbols;
 
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

        cout << "action time\n";
        for (string x : actionSymbols) {
            cout << x << " ";
        }
        cout << "\ngoto time\n";
        for (string x : nonTerminals) {
            cout << x << " ";
        }

        if (input.is_open()) {
            while (getline(input, line)) {
                vector<string> splitLine = split(line, "\t");
                vector<Action> actionList;
                int i = 1;
                for (; i < getActionSymbolCount(); i++) {
                    Action action;
                    char actionType;
                    int state0;
                    int state1;
                    if (splitLine.at(i).find_first_of("/") == string::npos) {
                        sscanf(splitLine.at(i).c_str(), "%c%d", &actionType, &state0);
                        if (actionType == 's') {
                            action.shift = state0;
                            action.reduce = -1;
                        } else {
                            action.shift = -1;
                            action.reduce = state0;
                        }
                    } else {
                        sscanf(splitLine.at(i).c_str(), "s%d / r%d", &state0, &state1);
                        action.shift = state0;
                        action.reduce = state1;
                    }
                    cout << splitLine[i] << " s " << action.shift << " r " << action.reduce << "\n";
                    actionList.push_back(action);
                }
                actionTable.push_back(actionList);

                vector<uint8_t> states;
                for (int j = 0; j < getNonTerminalCount(); j++) {
                    int state;
                    string tmp = splitLine.at(i+j);
                    if (tmp == "") {
                        state = -1;
                    } else {
                        sscanf(tmp.c_str(), "%d", &state);
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
    }
};

int main() 
{
    ParseTable parseTable("tableP");
    return 0;
}