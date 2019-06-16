%{
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "parser.hpp"

extern int yylex();
void yyerror(YYLTYPE* loc, const char* err);
std::string translate_boolean_str(std::string boolean_str);
/*std::string* translate_boolean_str(std::string* boolean_str);*/


/*
 * Here, target_program is a string that will hold the target program being
 * generated, and symbols is a simple symbol table.
 */
/* std::string* target_program; */
/* std::set<std::string> symbols; */

/* Root node for AST */
Node* root = new Node;

%}

/* Enable location tracking. */
%locations

/* Add Node structure. */
%code requires{
  #include <vector>
  struct Node{
    std::string name;
    std::string value;
    std::vector<Node*> nodes;
  };
}

/*
 * All program constructs will be represented as Nodes, specifically as
 * their corresponding C/C++ translation.
 */
%define api.value.type { /*std::string*/ Node* }

/*
 * Because the lexer can generate more than one token at a time (i.e. DEDENT
 * tokens), we'll use a push parser.
 */
%define api.pure full
%define api.push-pull push

/*
 * These are all of the terminals in our grammar, i.e. the syntactic
 * categories that can be recognized by the lexer.
 */
%token IDENTIFIER
%token FLOAT INTEGER BOOLEAN
%token INDENT DEDENT NEWLINE
%token AND BREAK DEF ELIF ELSE FOR IF NOT OR RETURN WHILE
%token ASSIGN PLUS MINUS TIMES DIVIDEDBY
%token EQ NEQ GT GTE LT LTE
%token LPAREN RPAREN COMMA COLON

/*
 * Here, we're defining the precedence of the operators.  The ones that appear
 * later have higher precedence.  All of the operators are left-associative
 * except the "not" operator, which is right-associative.
 */
%left OR
%left AND
%left PLUS MINUS
%left TIMES DIVIDEDBY
%left EQ NEQ GT GTE LT LTE
%right NOT

/* This is our goal/start symbol. */
%start program

%%

/*
 * Each of the CFG rules below recognizes a particular program construct in
 * Python and creates a new string containing the corresponding C/C++
 * translation.  Since we're allocating strings as we go, we also free them
 * as we no longer need them.  Specifically, each string is freed after it is
 * combined into a larger string.
 */
program
  : statements { /*target_program = $1;*/
                  root->name = "program";
               }
  ;

statements
  : statement { root->nodes.push_back($1); }
  | statements statement { /*$$ = new std::string(*$1 + *$2); delete $1; delete $2;*/
                            root->nodes.push_back($2);
                         }
  ;

statement
  : assign_statement { $$ = $1; }
  | if_statement { $$ = $1; }
  | while_statement { $$ = $1; }
  | break_statement { $$ = $1; }
  ;

primary_expression
  : IDENTIFIER { $$ = $1; }
  | FLOAT { $$ = $1; }
  | INTEGER { $$ = $1; }
  | BOOLEAN { /*$$ = translate_boolean_str($1); delete $1;*/
              Node* node = new Node;
              node->name = $1->name;
              node->value = translate_boolean_str($1->value); 
              $$ = node;
            }
  | LPAREN expression RPAREN { /*$$ = new std::string("(" + *$2 + ")"); delete $2;*/
                                $$ = $2;
                             }
  ;

negated_expression
  : NOT primary_expression { /*$$ = new std::string("!" + *$2); delete $2;*/
                              Node* node = new Node;
                              node->name = "not";
                              node->nodes.push_back($2);
                              $$ = node;
                           }
  ;

expression
  : primary_expression { $$ = $1; }
  | negated_expression { $$ = $1; }
  | expression PLUS expression { /*$$ = new std::string(*$1 + " + " + *$3); delete $1; delete $3;*/
                                  Node* node = new Node;
                                  node->name = "plus";
                                  node->nodes.push_back($1);
                                  node->nodes.push_back($3);
                                  $$ = node;
                               }
  | expression MINUS expression { /*$$ = new std::string(*$1 + " - " + *$3); delete $1; delete $3;*/
                                  Node* node = new Node;
                                  node->name = "minus";
                                  node->nodes.push_back($1);
                                  node->nodes.push_back($3);
                                  $$ = node;
                                }
  | expression TIMES expression { /*$$ = new std::string(*$1 + " * " + *$3); delete $1; delete $3;*/
                                  Node* node = new Node;
                                  node->name = "times";
                                  node->nodes.push_back($1);
                                  node->nodes.push_back($3);
                                  $$ = node;
                                }
  | expression DIVIDEDBY expression { /*$$ = new std::string(*$1 + " / " + *$3); delete $1; delete $3;*/
                                      Node* node = new Node;
                                      node->name = "dividedby";
                                      node->nodes.push_back($1);
                                      node->nodes.push_back($3);
                                      $$ = node;
                                    }
  | expression EQ expression { /*$$ = new std::string(*$1 + " == " + *$3); delete $1; delete $3;*/
                                Node* node = new Node;
                                node->name = "eq";
                                node->nodes.push_back($1);
                                node->nodes.push_back($3);
                                $$ = node;
                             }
  | expression NEQ expression { /*$$ = new std::string(*$1 + " != " + *$3); delete $1; delete $3;*/
                                Node* node = new Node;
                                node->name = "neq";
                                node->nodes.push_back($1);
                                node->nodes.push_back($3);
                                $$ = node;
                              }
  | expression GT expression { /*$$ = new std::string(*$1 + " > " + *$3); delete $1; delete $3;*/
                                Node* node = new Node;
                                node->name = "gt";
                                node->nodes.push_back($1);
                                node->nodes.push_back($3);
                                $$ = node;
                             }
  | expression GTE expression { /*$$ = new std::string(*$1 + " >= " + *$3); delete $1; delete $3;*/
                                Node* node = new Node;
                                node->name = "gte";
                                node->nodes.push_back($1);
                                node->nodes.push_back($3);
                                $$ = node;
                              }
  | expression LT expression { /*$$ = new std::string(*$1 + " < " + *$3); delete $1; delete $3;*/
                                Node* node = new Node;
                                node->name = "lt";
                                node->nodes.push_back($1);
                                node->nodes.push_back($3);
                                $$ = node;
                             }
  | expression LTE expression { /*$$ = new std::string(*$1 + " <= " + *$3); delete $1; delete $3;*/
                                Node* node = new Node;
                                node->name = "lte";
                                node->nodes.push_back($1);
                                node->nodes.push_back($3);
                                $$ = node;
                              }
  ;

assign_statement
  : IDENTIFIER ASSIGN expression NEWLINE { /*symbols.insert(*$1); $$ = new std::string(*$1 + " = " + *$3 + ";\n"); delete $1; delete $3;*/
                                            Node* node = new Node;
                                            node->name = "assign";
                                            node->nodes.push_back($1);
                                            node->nodes.push_back($3);
                                            $$ = node;
                                         }
  ;

block
  : INDENT statements DEDENT { /*$$ = new std::string("{\n" + *$2 + "}"); delete $2;*/
                                Node* node = new Node;
                                node->name = "block";
                                node->nodes.push_back($2);
                                $$ = node;
                             }
  ;

condition
  : expression { $$ = $1; }
  | condition AND condition { /*$$ = new std::string(*$1 + " && " + *$3); delete $1; delete $3;*/
                              Node* node = new Node;
                              node->name = "and";
                              node->nodes.push_back($1);
                              node->nodes.push_back($3);
                              $$ = node;
                            }
  | condition OR condition { /*$$ = new std::string(*$1 + " || " + *$3); delete $1; delete $3;*/
                              Node* node = new Node;
                              node->name = "or";
                              node->nodes.push_back($1);
                              node->nodes.push_back($3);
                              $$ = node;
                           }
  ;

if_statement
  : IF condition COLON NEWLINE block elif_blocks else_block { /*$$ = new std::string("if (" + *$2 + ") " + *$5 + *$6 + *$7 + "\n"); delete $2; delete $5; delete $6; delete $7;*/
                                                              Node* node = new Node;
                                                              node->name = "if";
                                                              node->nodes.push_back($2);
                                                              node->nodes.push_back($5);
                                                              node->nodes.push_back($6);
                                                              node->nodes.push_back($7);
                                                              $$ = node;
                                                            }
  ;

elif_blocks
  : %empty { /*$$ = new std::string("");*/
              Node* node = NULL;
              $$ = node;
           }
  | elif_blocks ELIF condition COLON NEWLINE block { /*$$ = new std::string(*$1 + " else if (" + *$3 + ") " + *$6); delete $1; delete $3; delete $6;*/
                                                      Node* node = new Node;
                                                      node->name = "else if";
                                                      node->nodes.push_back($1);
                                                      node->nodes.push_back($3);
                                                      node->nodes.push_back($6);
                                                      $$ = node;
                                                   }
  ;

else_block
  : %empty { /*$$ = new std::string("");*/
              Node* node = NULL;
              $$ = node;
           }
  | ELSE COLON NEWLINE block { /*$$ = new std::string(" else " + *$4); delete $4;*/
                                Node* node = new Node;
                                node->name = "else";
                                node->nodes.push_back($4);
                                $$ = node;
                             }


while_statement
  : WHILE condition COLON NEWLINE block { /*$$ = new std::string("while (" + *$2 + ") " + *$5 + "\n"); delete $2; delete $5;*/
                                          Node* node = new Node;
                                          node->name = "while";
                                          node->nodes.push_back($2);
                                          node->nodes.push_back($5);
                                          $$ = node;
                                        }
  ;

break_statement
  : BREAK NEWLINE { /*$$ = new std::string("break;\n");*/
                    Node* node = new Node;
                    node->name = "break";
                    $$ = node;
                  }
  ;

%%

void yyerror(YYLTYPE* loc, const char* err) {
  std::cerr << "Error (line " << loc->first_line << "): " << err << std::endl;
}

/*
 * This function translates a Python boolean value into the corresponding
 * C++ boolean value.
 */
/*std::string* translate_boolean_str(std::string* boolean_str) {
  if (boolean_str == "True") {
    return new std::string("true");
  } else {
    return new std::string("false");
  }
}*/

std::string translate_boolean_str(std::string boolean_str) {
  if (boolean_str == "True") {
    return "true";
  } else {
    return "false";
  }
}
