#include <stdio.h>
#include <iostream>
using namespace std;
class GenericParseNode {
public:
    enum type {
        PROGRAM, STMTS, STMT, DECL, ASSIGN, EXP, BOOL_E, AE, 
        T,  F,  LE, RE, CONDITIONAL, LOOP, WHILE_LOOP, DO_WHILE_LOOP
    } node_type;

    void printNode(){}

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
