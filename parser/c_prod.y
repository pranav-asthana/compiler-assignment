%{
    #include <iostream>
    #include <stdio.h>
    #define YYDEBUG 1

%}
%token NUM ID MAIN DO WHILE IF ELSE FOR TYPE
%%

PROGRAM: MAIN '{' STMTS '}';
STMTS: STMTS STMT | STMT |;
STMT: DECL | ASSIGN | EXP | CONDITIONAL | LOOP | ';';
DECL: TYPE ID';';
ASSIGN: ID '=' EXP ';' | TYPE ID '=' EXP ';';
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
