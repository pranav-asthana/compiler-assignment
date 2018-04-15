%{
    #include <iostream>
    #include <stdio.h>
    #define YYDEBUG 1
    typedef GenericParseNode::Type Type
%}
%token NUM ID MAIN DO WHILE IF ELSE FOR TYPE
%%

PROGRAM: MAIN '{' STMTS '}' {
    $$ = new GenericParseNode(Type::PROGRAM, $3);
};
STMTS: STMTS STMT {
    $$ = new GenericParseNode(Type::STMTS, new GenericParseNode(Type::STMTS, $2), new GenericParseNode(Type::STMT, $3));
} | STMT {
    $$ = new GenericParseNode(Type::STMTS, new GenericParseNode(Type::STMT, $2)); 
}| {
    // seriously think about this
    $$ = new GenericParseNode(Type::STMTS, $2)
};
STMT: DECL {
    $$ = new GenericParseNode(Type::STMT, new GenericParseNode(Type::DECL, $2));
} | ASSIGN {
    $$ = new GenericParseNode(Type::STMT, new GenericParseNode(Type::ASSIGN, $2));
}| EXP {
    $$ = new GenericParseNode(Type::STMT, new GenericParseNode(Type::EXP, $2));
}| CONDITIONAL {
    $$ = new GenericParseNode(Type::STMT, new GenericParseNode(Type::CONDITIONAL, $2));
}| LOOP {
    $$ = new GenericParseNode(Type::STMT, new GenericParseNode(Type::LOOP, $2));
}| ';';
DECL: TYPE ID';' {
    $$ = new GenericParseNode(Type::DECL, new GenericParseNode(Type::TYPE, $2), new GenericParseNode(Type::ID, $2));
};
ASSIGN: ID '=' EXP ';' {
    $$ = new GenericParseNode(Type::ASSIGN, new GenericParseNode(Type::ID, $2))
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
