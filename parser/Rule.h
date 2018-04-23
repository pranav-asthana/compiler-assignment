#include <string>
#include <vector>

using namespace std;

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