#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <stdint.h>
#include <ctype.h>
#include <string.h>

#include "Parser.h"

using namespace std;


int main() 
{
    // Parser parser("TYPE ID ( e ) { ID EQ NUM ; }", "p3", "rules2");
    // Parser parser("TYPE ID ( TYPE ID ) { IF ( ID LTE NUM ) { RETURN NUM ; } ELSE { RETURN ID * ( ID ( ID - NUM ) ) ; } ; }", "p3", "rules2");

    Parser parser("TYPE ID ( TYPE ID ) { IF ( ID LTE NUM ) { RETURN NUM ; } ELSE { RETURN ID * ( ID ( ID - NUM ) ) ; } ; } TYPE ID ( e ) { TYPE ID ; ID EQ NUM ; WHILE ( ID LTE NUM ) { ID ( ID ) ; ID ( ID ( ID ) ) ; ID ( e ) ; ID EQ ID + NUM ; } ; }", "p3", "rules2");

    // ParseTable parseTable("tableP2");
    // cout << parseTable.actionTable[39][24].shift << " " << parseTable.actionTable[39][24].reduce;
    // cout << parseTable.actionSymbols[24];
    // for (int i = 0; i < parseTable.getActionSymbolCount(); i++) {
    //     cout << i << " " << parseTable.actionTable[39][i].shift << " " << parseTable.actionTable[39][i].reduce << endl;
    // }
    return 0;
}
// TYPE ID ( TYPE ID ) { IF ( ID LTE NUM ) RETURN NUM ; ELSE RETURN ID * ID ( ID - NUM ) ; } TYPE ID ( e ) { TYPE ID ; ID EQ NUM ; WHILE ( ID LTE NUM ) { ID ( ID ) ; ID ( ID ( ID ) ) ; ID ( e ) ; ID EQ ID + NUM ; } } 
