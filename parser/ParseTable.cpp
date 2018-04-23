#include "ParseTable.h"

vector<string> ParseTable::split(const string &text, string sep)
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

int ParseTable::getActionSymbolIndex(string symbol)
{
    auto it = find(actionSymbols.begin(), actionSymbols.end(), symbol);
    return (it - actionSymbols.begin());
}

int ParseTable::getNonTerminalIndex(string nonTerminal)
{
    auto it = find(nonTerminals.begin(), nonTerminals.end(), nonTerminal);
    return (it - nonTerminals.begin());
}

int ParseTable::getNonTerminalCount()
{
    return nonTerminals.size();
}

int ParseTable::getActionSymbolCount()
{
    return actionSymbols.size();
}

void ParseTable::readParseTableFromFile(string filename)
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

    if (input.is_open()) {
        while (getline(input, line)) {
            vector<string> splitLine = split(line, "\t");
            vector<Action> actionList;
            int i = 1;
            for (i = 1; i <= getActionSymbolCount(); i++) {
                Action action;
                char actionType;
                int state0;
                int state1;
                if (isalpha(splitLine[i][0])) {
                    if (splitLine.at(i).find_first_of("/") == string::npos) {
                        sscanf(splitLine.at(i).c_str(), "%c%d", &actionType, &state0);
                        if (actionType == 's') {
                            action.shift = state0;
                        } else if (actionType == 'r') {
                            action.reduce = state0;
                        } else if (actionType == 'a') {
                            action.shift = -999;
                        }
                    } else {
                        cout << "Conflict in parsing.\n";
                        // exit(0);
                        sscanf(splitLine.at(i).c_str(), "s%d / r%d", &state0, &state1);
                        action.shift = state0;
                        // action.reduce = state1;
                    }
                }
                actionList.push_back(action);
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

ParseTable::ParseTable(string filename)
{
    readParseTableFromFile(filename);
}
