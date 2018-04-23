# CS F363 Compiler Assignment - Lexer, Parser, and TAC Generator

## Team Members

* Arnav Dhamija
* Pranav Asthana
* Sahil Sangwan

## Introduction

This project aims to implement the first three components of what make every compiler. The Lexer generates tokens and lexemes which are delivered to the Parser for checking whether the given input is valid given the specification of the language defined in the `grammar` file. These two parts have been written in C++11.

The grammar implemented is a slightly modified version of C which is LALR compliant.

The parser uses LALR tables for checking the input. The tables were taken from [http://jsmachines.sourceforge.net/machines/lalr1.html](http://jsmachines.sourceforge.net/machines/lalr1.html).

TAC generation is done using Yacc and Lex.

## Installation

Simply run the following commands in the working directory:

```
sudo apt install cmake
mkdir build
cd build
cmake ..
make -j4
./phase1
```

## Grammar

```
PROGRAM -> FUNCS
FUNCS -> FUNCS FUNC
FUNCS -> FUNC
FUNC -> TYPE ID ( PARAMETERS ) { STMTS }
PARAMETERS -> e
PARAMETERS -> PARAM_LIST
PARAM_LIST -> PARAM_LIST , TYPE ID
PARAM_LIST -> TYPE ID
STMTS -> STMTS STMT ;
STMTS -> STMT ;
STMT -> DECL
STMT -> ASSIGN
STMT -> EXP
STMT -> CONDITIONAL
STMT -> LOOP
STMT -> RETURN EXP
FUNC_CALL -> ID ( CALL_PARAMS )
CALL_PARAMS -> CALL_LIST
CALL_LIST -> CALL_LIST , EXP
CALL_LIST -> EXP
DECL -> TYPE ID
ASSIGN -> ID EQ EXP
ASSIGN -> TYPE ID EQ EXP
EXP -> AE
EXP -> BOOL_E
EXP -> e
BOOL_E -> LE
BOOL_E -> RE
AE -> AE + T
AE -> AE - T
AE -> T
AE -> FUNC_CALL
T -> T * F
T -> T / F
T -> F
F -> ( AE )
F -> NUM
F -> ID
LE -> AE & AE
LE -> AE | AE
RE -> AE GT AE
RE -> AE LT AE
RE -> AE GTE AE
RE -> AE LTE AE
RE -> AE CMP AE
RE -> AE NEQ AE
CONDITIONAL -> IF ( BOOL_E ) { STMTS }
CONDITIONAL -> IF ( BOOL_E ) { STMTS } ELSE { STMTS }
LOOP -> WHILE_LOOP
LOOP -> DO_WHILE_LOOP
WHILE_LOOP -> WHILE ( BOOL_E ) { STMTS }
DO_WHILE_LOOP -> DO { STMTS } WHILE ( BOOL_E ) ;
```