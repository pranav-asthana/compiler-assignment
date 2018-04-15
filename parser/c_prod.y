%{
    #include <iostream>
    #include <stdio.h>
    #define YYDEBUG 1

%}
%token NUM ID MAIN DO WHILE IF ELSE FOR TYPE
%%

PROGRAM: MAIN '{' STMTS '}' {
    $$ = new GenericParseNode(GenericParseNode::Type::PROGRAM, $3);
};
STMTS: STMTS STMT {
    $$ = new GenericParseNode(GenericParseNode::Type::STMTS, $2, $3);
} | STMT {
    $$ = new GenericParseNode(GenericParseNode::Type::STMT, $2);
}| {
    // seriously think about this
    $$ = new GenericParseNode(GenericParseNode::Type::NULLTYPE, $2)
};
STMT: DECL {
    $$ = new GenericParseNode(GenericParseNode::Type::DECL, $2)
} | ASSIGN {
    $$ = new GenericParseNode(GenericParseNode::Type::ASSIGN, $2)
}| EXP {
    $$ = new GenericParseNode(GenericParseNode::Type::EXP, $2)
}| CONDITIONAL {
    $$ = new GenericParseNode(GenericParseNode::Type::CONDITIONAL, $2)
}| LOOP {
    $$ = new GenericParseNode(GenericParseNode::Type::LOOP, $2)
}| ';';
DECL: TYPE ID';' {
    $$ = new GenericParseNode(GenericParseNode::Type::TERMINAL, $2, $3)
};
ASSIGN: ID '=' EXP ';' {
    $$ = new GenericParseNode
}| TYPE ID '=' EXP ';';
EXP: AE | BOOL_E;
BOOL_E: LE | RE;
AE: AE '+' T | AE '-' T | T;
T: T '*' F | T '/' F | F;
F: '(' AE ')' | NUM | ID;
LE: AE '&' AE | AE '|' AE;
RE: AE'>'AE | AE'<'AE | AE'>''='AE | AE'<''='AE | AE'=''='AE | AE'!''='AE;
CONDITIONAL: IF'('BOOL_E')''{'STMTS'}' | IF'('BOOL_E')''{'STMTS'}'ELSE'{'STMTS'}';
LOOP: WHILE_LOOP | DO_WHILE_LOOP;
WHILE_LOOP: WHILE'('BOOL_E')''{'STMTS'}';
DO_WHILE_LOOP: DO'{'STMTS'}'WHILE'('BOOL_E')'';';

%%
int yyerror(char *s)
{
    printf("Invalid string\n");
}

int main()
{

    extern FILE * yyin;
    yyin = fopen("input.c", "r");
yydebug=1
    if (yyparse() == 0) {
        printf("Valid string\n");
    }
    return 0;
}
