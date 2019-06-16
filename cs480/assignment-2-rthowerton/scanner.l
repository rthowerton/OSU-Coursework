%{
#include <iostream>
#include <stack>
#include <cstdlib>

#include "parser.hpp"

YYSTYPE yylval;
YYLTYPE yylloc;
yypstate* pstate = yypstate_new();

std::stack<int> _indent_stack;

#define PUSH_TOKEN(category) do {                      \
    int s = yypush_parse(pstate, category, &yylval, &yylloc);   \
    if (s != YYPUSH_MORE) {                         \
      yypstate_delete(pstate);                      \
      return s;                                     \
    }                                               \
  } while(0)

#define YY_USER_ACTION \
  yylloc.first_line = yylloc.last_line = yylineno;

%}

%option noyywrap
%option yylineno

%%

%{
  /*
   * These lines go at the top of the lexing function.  We only want to
   * initialize the indentation level stack once by pushing a 0 onto it (the
   * indentation stack should never be empty, except immediately after it is
   * created).
   */
  if (_indent_stack.empty()) {
    _indent_stack.push(0);
  }
%}

^[ \t]*\r?\n   { /* Skip blank lines */ }

^[ \t]*#.*\r?\n    { /* Skip whole-line comments. */ }

#.*$          { /* Skip comments on the same line as a statement. */ }

^[ \t]+       { 
                /*
                 * Handle indentation as described in Python docs linked above.
                 * Note that this pattern treats leading spaces and leading tabs
                 * equivalently, which could cause some unexpected behavior if
                 * they're combined in a single line.  For the purposes of this
                 * project, that's OK.
                 */
                if (_indent_stack.top() < yyleng) {
                  /*
                   * If the current indentation level is greater than the
                   * previous indentation level (stored at the top of the stack),
                   * then emit an INDENT and push the new indentation level onto
                   * the stack.
                   */
                  /* std::cout << "INDENT" << std::endl; */
                  yylval.str = new std::string(yytext, yyleng);
                  PUSH_TOKEN(INDENT);
                  _indent_stack.push(yyleng);
                } else {
                  /*
                   * If the current indentation level is less than or equal to
                   * the previous indentation level, pop indentation levels off
                   * the stack until the top is equal to the current indentation
                   * level.  Emit a DEDENT for each element popped from the stack.
                   */
                  while (!_indent_stack.empty() && _indent_stack.top() != yyleng) {
                    _indent_stack.pop();
                    /* std::cout << "DEDENT" << std::endl; */
                    yylval.str = new std::string(yytext, yyleng);
                    PUSH_TOKEN(DEDENT);
                  }

                  /*
                   * If we popped everythin g off the stack, that means the
                   * current indentation level didn't match any on the stack,
                   * which is an indentation error.
                   */
                  if (_indent_stack.empty()) {
                    std::cerr << "Error: Incorrect indentation on line " << yylineno << std::endl;
                    return 1;
                  }
                }
              }

^[^ \t\r\n]+ {
                /*
                 * If we find a line that's not indented, pop all indentation
                 * levels off the stack, and emit a DEDENT for each one.  Then,
                 * call REJECT, so the next rule matching this token is also
                 * applied.
                 */
                while (_indent_stack.top() != 0) {
                  _indent_stack.pop();
                  /* std::cout << "DEDENT" << std::endl; */
                  yylval.str = new std::string(yytext, yyleng);
                  PUSH_TOKEN(DEDENT);
                }
                REJECT;
              }

\r?\n         { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(NEWLINE); }

[ \t]         { /* Ignore spaces that haven't been handled above. */ }

"and"         { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(AND); }

"break"       { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(BREAK); }

"def"         { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(DEF); }

"elif"        { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(ELIF); }

"else"        { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(ELSE); }

"for"         { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(FOR); }

"if"          { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(IF); }

"not"         { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(NOT); }

"or"          { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(OR); }

"return"      { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(RETURN); }

"while"       { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(WHILE); }

"True"        { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(BOOLEAN); }

"False"       { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(BOOLEAN); }

[a-zA-Z_][a-zA-Z0-9_]*   {
                yylval.str = new std::string(yytext, yyleng);
                PUSH_TOKEN(IDENTIFIER);
              }

-?[0-9]*"."[0-9]+  {
                      yylval.str = new std::string(yytext, yyleng);
                      PUSH_TOKEN(FLOAT);
                   }

-?[0-9]+ {
            yylval.str = new std::string(yytext, yyleng);
            PUSH_TOKEN(INTEGER);
         }

"="           { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(ASSIGN); }


"+"           { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(PLUS); }

"-"           { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(MINUS); }

"*"           { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(TIMES); }

"/"           { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(DIVIDEDBY); }

"=="          { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(EQ); }

"!="          { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(NEQ); }

">"           { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(GT); }

">="          { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(GTE); }

"<"           { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(LT); }

"<="          { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(LTE); }

","           { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(COMMA); }

":"           { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(COLON); }

"("           { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(LPAREN); }

")"           { yylval.str = new std::string(yytext, yyleng); PUSH_TOKEN(RPAREN); }

<<EOF>>       {
                while(_indent_stack.top() != 0) {
                  _indent_stack.pop();
                  /* std::cout << "DEDENT" << std::endl; */
                  yylval.str = new std::string(yytext, yyleng);
                  PUSH_TOKEN(DEDENT);
                }
                int s = yypush_parse(pstate, 0, NULL, NULL);
                yypstate_delete(pstate);
                return s;
              }

%%