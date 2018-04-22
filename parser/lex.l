%{
	#include "y.tab.h"
	// redefine yylval to give a string
	char* _input;
	char* _tinput;
%}

alpha [a-zA-Z_]
digit [0-9]

%%
"and" return AND;
"or" return OR;
"not" return NOT;
"main()" return MAIN;
"{" return LCB;
"}" return RCB;
";" return SEMICOLON;
"=" return EQ;
"+" return ADD;
"-" return SUB;
"*" return MUL;
"/" return DIV;
{digit}+ return NUM;
"(" return LSB;
")" return RSB;
"int"|"float"|"boolean" {
	_tinput = malloc(1000);
	for (int i = 0; yytext[i] != ' ' && yytext[i] != '\0'; i++) {
		_tinput[i] = yytext[i];
	}
 return TYPE;}
{alpha}{alpha}*{digit}* {_input = yytext; return id;}
\n
%%
