%{
    #include <stack> // std::stack
    #include <string> // std::string
    #include <string.h> // strcmp

    std::stack<int> indents; // Stack to track indentation

    /*
     * Function name: handleIndent
     * Arguments: length
     * Function body: tracks indentation by pushing and popping values onto the indents stack. If the scanner
     *                finds indentation, it pushes the length of the whitespace onto the stack. If a line has
     *                less indentation than the number on top of the stack, then that line is dedented, so the
     *                top value is popped off the stack, until the value on top of the stack is equivalent to
     *                the length of the current indentation.
     * Return type: std::string
     */
    std::string handleIndent(int length){
        std::string ret = "";
        // Length == 0
        if(!indents.empty() && length == 0){
            // If the current indentation level is being reset to 0
            for(int i = 0; i <= indents.size(); i++){
                // pop all values off the stack and return equivalent number of dedent tokens
                indents.pop();
                ret += "DEDENT\n";
            }
            return ret;
        }
        else if(indents.empty() && length == 0){
            // Do nothing if the current indentation level is 0 and no indentation is present
            return ret;
        }
        // Length > 0
        if(indents.empty() && length > 0){
            // If the stack is empty and the program is now being indented,
            // push the indentation level and return an indent token
            indents.push(length);
            ret += "INDENT\n";
            return ret;
        }
        else if(indents.top() == length){
            // If the current indentation level has not increased or decreased, do nothing
            return ret;
        }
        else if(indents.top() < length){
            // If the current indentation level is greater than the previous level,
            // push the current level on top of the stack and return an indent token
            indents.push(length);
            ret += "INDENT\n";
            return ret;
        }
        else if(indents.top() > length){
            // If the current indentation level is less than the previous level,
            // pop the previous level off the stack and return a dedent token
            while(indents.top() > length){
                indents.pop();
                ret += "DEDENT\n";
            }
            return ret;
        }
    }
%}

%option noyywrap
%option yylineno

%%

^[ \t]+                             { // Indentation exists
                                        printf("%s", handleIndent(yyleng).c_str());
                                    }

^[^ \t]+\n                          { // Full dedentation
                                        printf("%s", handleIndent(0).c_str());
                                        REJECT
                                    }

^[ \t]*\n                           {/* Do nothing with blank lines */}

#(.*)\n                             {/* Do nothing with comments*/}

\n                                  {
                                        printf("NEWLINE\n");
                                    }

" "                                 {/* Do nothing with between-spaces*/}

True|False                          { // Boolean values
                                        if(!strcmp(yytext, "True")){
                                            printf("BOOLEAN             %d\n", 1);
                                        }
                                        else if(!strcmp(yytext, "False")){
                                            printf("BOOLEAN             %d\n", 0);
                                        }
                                    }

and                                 {
                                        printf("AND                 %s\n", yytext);
                                    }

break                               {
                                        printf("BREAK               %s\n", yytext);
                                    }

def                                 {
                                        printf("DEF                 %s\n", yytext);
                                    }

elif                                {
                                        printf("ELIF                %s\n", yytext);
                                    }

else                                {
                                        printf("ELSE                %s\n", yytext);
                                    }

for                                 {
                                        printf("FOR                 %s\n", yytext);
                                    }

if                                  {
                                        printf("IF                  %s\n", yytext);
                                    }

not                                 {
                                        printf("NOT                 %s\n", yytext);
                                    }

or                                  {
                                        printf("OR                  %s\n", yytext);
                                    }

return                              {
                                        printf("RETURN              %s\n", yytext);
                                    }

while                               {
                                        printf("WHILE               %s\n", yytext);
                                    }

=                                   {
                                        printf("ASSIGN              %s\n", yytext);
                                    }

"+"                                 {
                                        printf("PLUS                %s\n", yytext);
                                    }

"-"                                 {
                                        printf("MINUS               %s\n", yytext);
                                    }

"*"                                 {
                                        printf("TIMES               %s\n", yytext);
                                    }

"/"                                 {
                                        printf("DIVIDEDBY           %s\n", yytext);
                                    }

"=="                                {
                                        printf("EQ                  %s\n", yytext);
                                    }

"!="                                {
                                        printf("NEQ                 %s\n", yytext);
                                    }

">"                                 {
                                        printf("GT                  %s\n", yytext);
                                    }

">="                                {
                                        printf("GTE                 %s\n", yytext);
                                    }

"<"                                 {
                                        printf("LT                  %s\n", yytext);
                                    }

"<="                                {
                                        printf("LTE                 %s\n", yytext);
                                    }

"("                                 {
                                        printf("LPAREN              %s\n", yytext);
                                    }

")"                                 {
                                        printf("RPAREN              %s\n", yytext);
                                    }

,                                   {
                                        printf("COMMA               %s\n", yytext);
                                    }

:                                   {
                                        printf("COLON               %s\n", yytext);
                                    }

([a-zA-Z]|_)([a-zA-Z0-9]|_)*        { // Handle identifiers, start with any alphabetical character or _, then any number of alphanumeric characters or _
                                        printf("IDENTIFIER          %s\n", yytext);
                                    }

"-"?([0-9]+)                        { // Integers can be negative or positive, and are composed of one or more digits (no decimal point)
                                        printf("INTEGER             %d\n", atoi(yytext));
                                    }

"-"?([0-9])*"."([0-9]+)             { // Floats can be negative or positive, and have any number of digits in front of the decimal point, and one ore more digits behind
                                        printf("FLOAT               %f\n", atof(yytext));
                                    }

<<EOF>>                             {
                                        printf("%s", handleIndent(0).c_str());
                                        return 0;
                                    }

%%

int main(){
    // Call the scanner
    yylex();
    return 0;
}
