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

    GenericParseNode(type _nodeType, string termString)
    {
        terminalString = termString;
    }

    GenericParseNode(type _nodeType, GenericParseNode* _node)
    {
        children = 1;
        nodeType = _nodeType;
        node[0] = _node;
    }

    GenericParseNode(type _nodeType, GenericParseNode* _node0, GenericParseNode* node1)
    {
        children = 2;
        nodeType = _nodeType;
        node[0] = _node0;
        node[1] = _node1;
    }

    GenericParseNode(type _nodeType, GenericParseNode* _node0, GenericParseNode* node1, GenericParseNode* node2)
    {
        children = 3;
        nodeType = _nodeType;
        node[0] = _node0;
        node[1] = _node1;
        node[2] = _node2;
    }

    void printNode()
    {
        switch(nodeType) {
        case PROGRAM:
            cout << "main " << node0.printNode();
            break;
        case STMT:
            cout <<
        case EXPR:
        case BOOL_E:
        case AE:
        case T:
        case F:
        case LE:
        case LOOP:
        }
    }

    type getType()
    {
        return node_type;
    }
};

class DeclarativeNode : public GenericParseNode {
    string type;
    string id;
public:
    DeclarativeNode(string _type, string _id)
    {
        node_type = DECL;
        type = _type;
        id = _id;
    }

    void printNode()
    {
        cout << type << " " << id;
    }
};

class ExpressionNode : public GenericParseNode {
};

class ArithmeticExpressionNode : public ExpressionNode {
    ArithmeticExpressionNode* aen;
    char symbol;
    Term term;
public:
    ArithmeticExpressionNode(ArithmeticExpressionNode* _aen, char _symbol, Term _term) {
        aen = _aen;
        symbol = _symbol;
        term = _term;
    }
}

class Term {
    Term* term;

}

class AssignmentNode : public StatementNode {
    string id;
    string type;
    ExpressionNode exprNode;
public:
    DeclarativeNode(string _id, ExpressionNode _exprNode)
    {
        node_type = DECL;
        id = _id;
        exprNode = _exprNode;
    }


    DeclarativeNode(string _type, string _id, ExpressionNode _exprNode)
    {
        node_type = DECL;
        type = _type;
        id = _id;
        exprNode = _exprNode;
    }

    void printNode()
    {
        cout << type << " " << id << " = " << exprNode.printNode();
    }
};
