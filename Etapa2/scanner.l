%{
    //Autor: Nicolas Mauro de Moreira Bohnenberger - 00207160
    #include "y.tab.h"
    #include "hash.h"
    int Running = 1;
    int lineNumber = 1;
%}

%x COMMENT

%%
"TRUE"                  	                        {hashInsert(SYMBOL_LIT_TRU, yytext); return LIT_TRUE;}
"FALSE"                 	                        {hashInsert(SYMBOL_LIT_FLS, yytext); return LIT_FALSE;}
"char"                  	                        return KW_CHAR;
"int"                   	                        return KW_INT;
"float"                 	                        return KW_FLOAT;
"bool"                  	                        return KW_BOOL;
"if"                    	                        return KW_IF;
"then"                  	                        return KW_THEN;
"else"                  	                        return KW_ELSE;
"while"                 	                        return KW_WHILE;
"loop"                  	                        return KW_LOOP;
"read"                  	                        return KW_READ;
"print"                 	                        return KW_PRINT;
"return"                	                        return KW_RETURN;
"<="                    	                        return OPERATOR_LE;
">="                    	                        return OPERATOR_GE;
"=="                    	                        return OPERATOR_EQ;
"!="                    	                        return OPERATOR_DIF;
[0-9][0-9A-F]*		 		                        {hashInsert(SYMBOL_LIT_INT, yytext); return LIT_INTEGER;}
[0-9A-F]*\.[0-9A-F]+    	                        {hashInsert(SYMBOL_LIT_FLT, yytext); return LIT_FLOAT;}

"\'"[a-zA-Z]"\'"        	                        {hashInsert(SYMBOL_LIT_CHR, yytext); return LIT_CHAR;}
[a-zAz_@]+[0-9a-zA-z_@]*		                    {hashInsert(SYMBOL_TOK_IDT, yytext); return TK_IDENTIFIER;}
"//".*			
[ \t]			
[\,\;\:\(\)\[\]\{\}\+\-\*\/\<\>\=\|\^\~\&\$\#]  	return yytext[0];
"\n"                                            	++lineNumber;
.			 				                        return TOKEN_ERROR;

\"([^\"\\\n]|\\.)*\"                      	 	    {hashInsert(SYMBOL_LIT_STR, yytext); return LIT_STRING;}

"/*"                                        	    BEGIN(COMMENT);
<COMMENT>"\n"                               	    ++lineNumber;
<COMMENT>"*/"                               	    BEGIN(INITIAL);
<COMMENT>.
%%

// #include "y.tab.c"
// #include "main.c"
// #include "hash.c"

void initMe(void)
{
    lineNumber = 1;
    hashInit();
}

int getLineNumber(void)
{
    return lineNumber;
}

int isRunning(void)
{
    return Running;
}

int yywrap()
{
	Running = 0;
	fprintf(stderr, "Line count: %d", lineNumber);
	return 1;
}
