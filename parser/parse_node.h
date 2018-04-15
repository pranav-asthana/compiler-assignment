#include <stdio.h>

typedef struct parse_node parse_node;


struct parse_node {
    enum type {
        PROGRAM, STMTS, STMT, DECL, ASSIGN, EXP, BOOL_E, AE, 
        T,  F,  LE, RE, CONDITIONAL, LOOP, WHILE_LOOP, DO_WHILE_LOOP
    } node_type;
    
}