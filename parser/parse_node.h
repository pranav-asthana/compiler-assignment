#include <stdio.h>
#include <iostream>
using namespace std;
class GenericParseNode {
public:
    enum Type {
        PROGRAM, STMTS, STMT, DECL, ASSIGN, EXP, BOOL_E, AE, 
        T,  F,  LE, RE, CONDITIONAL, LOOP, WHILE_LOOP, DO_WHILE_LOOP, NULLTYPE, TERMINAL
    } nodeType;

    string terminalString;

public:
    int children;
    GenericParseNode* nodes[3];

    GenericParseNode(Type _nodeType, string termString)
    {
        terminalString = termString;
    }

    GenericParseNode(Type _nodeType, GenericParseNode* _node)
    {
        children = 1;
        nodeType = _nodeType;
        nodes[0] = _node;
    }

    GenericParseNode(Type _nodeType, GenericParseNode* _node0, GenericParseNode* _node1)
    {
        children = 2;
        nodeType = _nodeType;
        nodes[0] = _node0;
        nodes[1] = _node1;
    }

    GenericParseNode(Type _nodeType, GenericParseNode* _node0, GenericParseNode* _node1, GenericParseNode* _node2)
    {
        children = 3;
        nodeType = _nodeType;
        nodes[0] = _node0;
        nodes[1] = _node1;
        nodes[2] = _node2;
    }

    void printNode()
    {
        switch(nodeType) {
        // case PROGRAM:
        //     // cout << "main "; 
        //     // nodes[0]->printNode();
        //     // break;
        // case STMT:
        //     // cout <<
        // case EXP:
        // case BOOL_E:
        // case AE:
        // case T:
        // case F:
        // case LE:
        // case LOOP:
        }
    }

    Type getType()
    {
        return nodeType;
    }
};

