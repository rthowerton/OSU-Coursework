%{
#include <iostream>
#include <set>
#include <vector>
#include <string>

#include "parser.hpp"

bool _error = false;
std::set<std::string> identifiers;
std::vector<std::string> statements;

extern int yylex();

void yyerror(YYLTYPE* loc, const char* err) {
  std::cerr << "Error (line " << loc->first_line << "): " << err << std::endl;
}

%}

%locations
%define parse.error verbose

%define api.pure full
%define api.push-pull push

%union {
  std::string* str;
}

%token <str> IDENTIFIER
%token <str> BOOLEAN INTEGER FLOAT
%token <str> AND BREAK DEF ELIF ELSE FOR IF NEWLINE NOT OR RETURN WHILE
%token <str> ASSIGN PLUS MINUS TIMES DIVIDEDBY EQ NEQ GT GTE LT LTE
%token <str> COMMA COLON LPAREN RPAREN
%token <str> INDENT DEDENT

%type <str> program expression conditional
%type <str> statement

%left PLUS MINUS
%left TIMES DIVIDEDBY
%right NOT

%start program

%%

program
    : program statement { statements.push_back(*$2); delete $2; }
    | statement { statements.push_back(*$1); delete $1; }
    ;

statement
    : IDENTIFIER ASSIGN expression NEWLINE { identifiers.insert(*$1); $$ = new std::string(*$1 + " = " + *$3 + ";"); delete $1, $3; }
    | IF expression COLON NEWLINE INDENT statement { $$ = new std::string("if(" + *$2 + "){\n" + *$6 + "\n}"); delete $2, $6; }
    | IF expression COLON NEWLINE INDENT statement conditional { $$ = new std::string("if(" + *$2 + "){\n" + *$6 + "\n}" + *$7); delete $2, $6, $7; }
    | WHILE expression COLON NEWLINE INDENT statement { $$ = new std::string("while(" + *$2 + "){\n" + *$6 + "\n}"); delete $2, $6; }
    | BREAK NEWLINE { $$ = new std::string("break;\n"); }
    | NEWLINE { $$ = new std::string("\n"); }
    | DEDENT
    ;

conditional
    : DEDENT ELIF expression COLON NEWLINE INDENT statement conditional { $$ = new std::string("else if(" + *$3 + "){\n" + *$7 + ";\n}" + *$8); delete $3, $7, $8; }
    | DEDENT ELSE COLON NEWLINE INDENT statement { $$ = new std::string("else{\n" + *$5 + ";\n}"); delete $5; }
    | NEWLINE DEDENT { $$ = new std::string("\n"); }
    | DEDENT
    ;

expression
    : LPAREN expression RPAREN { $$ = new std::string("(" + *$2 + ")"); delete $2; }
    | expression PLUS expression { $$ = new std::string (*$1 + " + " + *$3); delete $1, $3; }
    | expression MINUS expression { $$ = new std::string(*$1 + " - " + *$3); delete $1, $3; }
    | expression TIMES expression { $$ = new std::string(*$1 + " * " + *$3); delete $1, $3; }
    | expression DIVIDEDBY expression { $$ = new std::string(*$1 + " / " + *$3); delete $1, $3; }
    | expression EQ expression { $$ = new std::string(*$1 + " == " + *$3); delete $1, $3; }
    | expression NEQ expression { $$ = new std::string(*$1 + " != " + *$3); delete $1, $3; }
    | expression GT expression { $$ = new std::string(*$1 + " > " + *$3); delete $1, $3; }
    | expression GTE expression { $$ = new std::string(*$1 + " >= " + *$3); delete $1, $3; }
    | expression LT expression { $$ = new std::string(*$1 + " < " + *$3); delete $1, $3; }
    | expression LTE expression { $$ = new std::string(*$1 + " <= " + *$3); delete $1, $3; }
    | expression AND expression { $$ = new std::string(*$1 + " && " + *$3); delete $1, $3; }
    | expression OR expression { $$ = new std::string(*$1 + " || " + *$3); delete $1, $3; }
    | NOT expression { $$ = new std::string("!" + *$2); delete $2; }
    | INTEGER { $$ = $1; }
    | FLOAT { $$ = $1; }
    | BOOLEAN { $$ = $1; }
    | IDENTIFIER { $$ = $1; }
    ;

%%