#include "Parser.h"
#include "ParseTable.h"

vector<string> Parser::split(const string &text, string sep)
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

void Parser::readRules(string rulesFile)
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
    while (it+1 != fileContents.end()) {
        char _nonTerm[512], _ruleString[512];
        auto nt_rule_split = split(*it, " -> ");
        nonTerm = nt_rule_split[0];
        ruleString = nt_rule_split[1];
        Production production;
        production.nonTerminalString = nonTerm;
        cout << nonTerm << " " << ruleString << endl;

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
}

Parser::Parser(string _input, string filename, string rulesFile)
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
        cout << s  << " " << a << endl;
        Action action = parseTable.actionTable[s][a];

        if (action.shift == -999) {
            if (!parseFailItr) {
                cout << "Parsing successful\n";
            } else {
                cout << "Parsed using a best-effort strategy to handle the parse failiure in iteration " << parseFailItr  << endl;
            }
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
            stateStack.push(parseTable.gotoTable[s][a]);
            cout << "Reducing: " << ruleList.at(action.reduce).nonTerm << " -> ";
            for (string s : ruleList.at(action.reduce).parsedRuleRHS) {
                cout << s << " ";
            }
            cout << endl;
        } else {
            cout << "Parsing fail @ " << s << " " << a << " " << parseTable.actionTable[s][a].shift << "/" << parseTable.actionTable[s][a].reduce  << endl;
            cout << "Trying to recover by popping stack " << endl;
            if (symbolStack.size() > 0 && stateStack.size() > 0) {
                symbolStack.pop();
                stateStack.pop();
            } else {
                cout << "Critical parse failure\n";
                return;
            }
            parseFailItr = itrCounter;
            // return;
        }
        cout << "Current input symbol: " << currentInput << endl;
        cout << "State stack: ";
        printStack(stateStack);
        cout << "Symbol stack: ";
        printStack(symbolStack);
    }
}

template <class T>
void Parser::printStack(stack<T> _stack)
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

Parser::Parser(string rulesFile)
{
    readRules(rulesFile);
}


