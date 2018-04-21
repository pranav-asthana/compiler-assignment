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

        if (input.is_open()) {
            while (getline(input, line)) {
                vector<string> splitLine = split(line, "\t");
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

    ParseTable(string filename)
    {
        readParseTableFromFile(filename);
        // for (auto it = gotoTable.begin(); it != gotoTable.end(); it++) {
        //     for (auto it0 = it->begin(); it0 != it->end(); it0++) {
        //         cout << *it0 << " ";
        //     }
        //     cout << endl;
        // }
        // for (auto it = actionTable.begin(); it != actionTable.end(); it++) {
        //     for (auto it0 = it->begin(); it0 != it->end(); it0++) {
        //         cout << it0->shift << "/" << it0->reduce << " ";
        //     }
        //     cout << endl;
        // }
    }
};

struct Production {
    string nonTerminalString;
    vector<vector<string>> rules;
};

class Rule {
public:
    string nonTerm;
    vector<string> parsedRuleRHS;
    Rule(string _nonTerm, vector<string> _rhs)
    {
        nonTerm = _nonTerm;
        parsedRuleRHS = _rhs;
    }
};

class Parser {
    stack<int> stateStack;
    stack<string> symbolStack;
    vector<string> input;
    vector<Production> productions;
    vector<Rule> ruleList;
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
            while (getline(input, line)) {
                fileContents.push_back(line);
            }
        }

        auto it = fileContents.begin();
        string nonTerm, ruleString;
        vector<string> parsedRule;
        while (it != fileContents.end()) {
            char _nonTerm[512], _ruleString[512];
            auto nt_rule_split = split(*it, " -> ");
            nonTerm = nt_rule_split[0];
            ruleString = nt_rule_split[1];
            Production production;
            production.nonTerminalString = nonTerm;

            parsedRule = split(ruleString, " ");
            production.rules.push_back(parsedRule);
            ruleList.push_back(Rule(nonTerm, parsedRule));
            it++;
            while (it->compare(0, nonTerm.length(), nonTerm) == 0) {
                nt_rule_split = split(*it, " -> ");
                ruleString = nt_rule_split[1];
                parsedRule = split(ruleString, " ");
                production.rules.push_back(parsedRule);
                ruleList.push_back(Rule(nonTerm, parsedRule));
                it++;
            }
            productions.push_back(production);
        }

        // int i = 0;
        // for (Rule r : ruleList) {
        //     cout << i++<< " " << r.nonTerm << " -> ";
        //     for (string x : r.parsedRuleRHS) {
        //         cout << x << " ";
        //     }
        //     cout << endl;
        // }
    }

    Parser(string _input, string filename, string rulesFile)
    {
        input = split(_input, " ");
        input.push_back("$");
        ParseTable parseTable(filename);
        readRules(rulesFile);
        stateStack.push(0);
        int inputPtr = 0;
        int s, a;
        int itrCounter = 0;
        while (true) {
            cout << "\nIteration: " << itrCounter++ << endl;
            string currentInput = input.at(inputPtr);
            s = stateStack.top();
            a = parseTable.getActionSymbolIndex(currentInput);
            Action action = parseTable.actionTable[s][a];

            if (action.shift == 0) {
                cout << "Parsing successful\n";
                return;
            }
            if (action.shift != -1) {
                cout << "Shifting: " << action.shift << " " << endl;

                stateStack.push(action.shift);
                symbolStack.push(currentInput);
                inputPtr++;
            } else if (action.reduce != -1) {
                Rule rule = ruleList.at(action.reduce);
                int pop_size = rule.parsedRuleRHS.size();
                string nt = ruleList.at(action.reduce).nonTerm;
                while (pop_size > 0) {
                    symbolStack.pop();
                    stateStack.pop();
                    pop_size--;
                }

                s = stateStack.top();
                a = parseTable.getNonTerminalIndex(nt);
                symbolStack.push(nt);
                stateStack.push(parseTable.gotoTable[s][a+1]);
                cout << "Reducing: " << ruleList.at(action.reduce).nonTerm << " -> ";
                for (string s : ruleList.at(action.reduce).parsedRuleRHS) {
                    cout << s << " ";
                }
                cout << endl;
            } else {
                cout << "Parsing fail @ " << s << " " << a << " " << parseTable.actionTable[s][a].shift << "/" << parseTable.actionTable[s][a].reduce  << endl;
                return;
            }
            cout << "Current input symbol: " << currentInput << endl;
            cout << "State stack: ";
            printStack(stateStack);
            cout << "Symbol stack: ";
            printStack(symbolStack);
        }
    }
    
    template <class T>
    void printStack(stack<T> _stack)
    {
        stack<T> invertedStack;
        while(!_stack.empty())
        {
            invertedStack.push(_stack.top());
            _stack.pop();
        }
        while(!invertedStack.empty())
        {
            cout << invertedStack.top() << " ";
            invertedStack.pop();
        }
        cout << endl;
    }

    Parser(string rulesFile)
    {
        readRules(rulesFile);
    }
};


int main() 
{
    Parser parser("MAIN { ID = NUM * ID ; }", "t2", "rules");
    return 0;
}