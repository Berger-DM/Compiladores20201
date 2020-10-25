%{
    #include <stdio.h>
    #include <stdlib.h>
    int getLineNumber(void);
    int yylex();
    int yyerror();
%}

%token KW_CHAR
%token KW_INT
%token KW_FLOAT
%token KW_BOOL

%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_LOOP
%token KW_READ
%token KW_PRINT
%token KW_RETURN

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_DIF
%token TK_IDENTIFIER

%token LIT_INTEGER
%token LIT_FLOAT
%token LIT_TRUE
%token LIT_FALSE
%token LIT_CHAR
%token LIT_STRING

%token TOKEN_ERROR

%start program
%right '='
%left '^' '~' '|'
%left '.' '&'
%left OPERATOR_EQ OPERATOR_GE OPERATOR_LE OPERATOR_DIF '>' '<'
%left '+' '-'
%left '*' '/'
%right KW_IF KW_THEN KW_ELSE
%%

program
    : declaration
    ;
    
declaration
    : declares declaration
    | declares
    ;
    
declares
    : var_global ';'
    | function ';'
    ;

function
    : TK_IDENTIFIER '(' parameter_list ')' '=' type command_block
    ;
    
var_global
    : TK_IDENTIFIER '=' type ':' literal
    | TK_IDENTIFIER '=' type '[' LIT_INTEGER ']' ':' literal_list
    | TK_IDENTIFIER '=' type '[' LIT_INTEGER ']'
    ;
    
literal_list
    : literal literal_list
    | literal
    | 
    ;
    
literal
    : LIT_TRUE
    | LIT_FALSE
    | LIT_INTEGER
    | LIT_FLOAT
    | LIT_CHAR
    ;
    
parameter_list
    : parameter ',' parameter_list
    | parameter
    | 
    ;
    
parameter
    : TK_IDENTIFIER '=' type
    ;
    
type
    : KW_BOOL
    | KW_INT
    | KW_FLOAT
    | KW_CHAR
    ;
    
command_sequence
    : command command_sequence
    |
    ;
    
command
    : TK_IDENTIFIER '=' expression
    | TK_IDENTIFIER '[' expression ']' '=' expression
    | KW_READ TK_IDENTIFIER
    | KW_PRINT print_list
    | KW_RETURN expression
    | flow_control
    | command_block
    |  
    ;
    
command_block
    : '{' command_sequence '}'
    ;
    
print_list
    : print_element ',' print_list
    | print_element
    ;
    
print_element
    : LIT_STRING
    | expression
    ;
    
flow_control
    : KW_IF '(' expression ')' KW_THEN command
    | KW_IF '(' expression ')' KW_THEN command KW_ELSE command
    | KW_WHILE '(' expression ')' command
    | KW_LOOP '(' TK_IDENTIFIER ':' expression ',' expression ',' expression ')' command
    ;
    
expression
    : TK_IDENTIFIER
    | TK_IDENTIFIER '[' expression ']'
    | TK_IDENTIFIER '(' parameter_list ')'
    | LIT_INTEGER
    | LIT_FLOAT
    | LIT_CHAR
    | '(' expression ')'
    | expression OPERATOR_LE expression
    | expression OPERATOR_GE expression
    | expression OPERATOR_EQ expression
    | expression OPERATOR_DIF expression
    | expression '+' expression
    | expression '-' expression
    | expression '*' expression
    | expression '/' expression
    | expression '<' expression
    | expression '>' expression
    | expression '|' expression
    | expression '^' expression
    | expression '~' expression
    | expression '.' expression
    | expression '&' expression
    ;

%%

int yyerror(char *msg)
{
    fprintf(stderr, "Syntax error at line %d. \n", getLineNumber());
    exit(3);
}
