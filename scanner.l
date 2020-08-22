%{
    #include "tokens.h"
    int Running = 1;
    int lineNumber = 1;
%}

%%
"char"      return KW_CHAR;
"int"       return KW_INT;
"float"     return KW_FLOAT;
"bool"      return KW_BOOL;
"if"        return KW_IF;
"then"      return KW_THEN;
"else"      return KW_ELSE;
"while"     return KW_WHILE;
"loop"      return KW_LOOP;
"read"      return KW_READ;
"print"     return KW_PRINT;
"return"    return KW_RETURN;
"<="        return OPERATOR_LE;
">="        return OPERATOR_GE;
"=="        return OPERATOR_EQ;
"!="        return OPERATOR_DIF;
[_@a-zAz][_@0-9a-zA-z]* return TK_IDENTIFIER;
0[1-9A-F][0-9A-F]*  return LIT_INTEGER;
[0-9A-F]*.[0-9A-F]+ return LIT_FLOAT;
"TRUE"      return LIT_TRUE;
"FALSE"     return LIT_FALSE;
"\'"[a-zA-Z]"\'"    return LIT_CHAR;
"\""        BEGIN(STRING);
"//".*
"/*"        BEGIN(COMMENT);
[ \t]
[,;:(){}[]+-=/<>|^~&$#] return yytext[0];
"\n"        ++lineNumber;

<STRING>
<STRING>"\n" ++lineNumber;
<STRING>"\"" BEGIN(INITIAL);

<COMMENT>.
<COMMENT>"\n"   ++lineNumber;
<COMMENT>"*/"   BEGIN(INITIAL);
%%

//#include "main.c"

int main ()
{
    int tok;
    while (Running)
    {
        tok = yylex();
        switch (tok)
        {

        }
    }
}
