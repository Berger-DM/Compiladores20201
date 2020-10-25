%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "ast.h"
    #include "hash.h"
    
    #define SYMBOL_AST(x) ASTcria(AST_SYMBOL, x, NULL, NULL, NULL, NULL, NULL)
    
    AST* ASTraiz = NULL;
    
    int getLineNumber(void);
    int yylex();
    int yyerror();
    AST *ASTcria(int type, HASH_NODE *symbol, AST* s0, AST* s1, AST* s2, AST* s3, AST* s4);
%}

%union
{
    HASH_NODE *symbol;
    AST *ast;
}

%token<symbol> KW_CHAR
%token<symbol> KW_INT
%token<symbol> KW_FLOAT
%token<symbol> KW_BOOL

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
%token<symbol> TK_IDENTIFIER

%token<symbol> LIT_INTEGER
%token<symbol> LIT_FLOAT
%token<symbol> LIT_TRUE
%token<symbol> LIT_FALSE
%token<symbol> LIT_CHAR
%token<symbol> LIT_STRING
%token<symbol> TOKEN_ERROR

%start program
%left '|' '^'
%left '.' '&'
%left OPERATOR_EQ OPERATOR_GE OPERATOR_LE OPERATOR_DIF '>' '<'
%left '+' '-'
%left '*' '/'
%left '~'

%type<ast> program
%type<ast> declaration
%type<ast> function
%type<ast> func_header
%type<ast> func_params
%type<ast> var_global
%type<ast> vetor
%type<ast> literal_list
%type<ast> literal
%type<ast> parameter_list
%type<ast> p_list
%type<ast> type
%type<ast> command_sequence
%type<ast> command
%type<ast> command_block
%type<ast> print_list
%type<ast> print_element
%type<ast> flow_control
%type<ast> expr
%type<ast> func_call
%type<ast> call_param
%type<ast> c_list
%%

program
    : declaration                                                       {$$ = $1; ASTraiz = $$;}
    ;
    
declaration
    : var_global ';' declaration                                        {$$ = ASTcria(AST_DECL, NULL, $1, $3, NULL, NULL, NULL);}
    | function ';' declaration                                          {$$ = ASTcria(AST_DECL, NULL, $1, $3, NULL, NULL, NULL);}
    |                                                                   {$$ = NULL;}
    ;

function
    : func_header command_block                                         {$$ = ASTcria(AST_FUNC, NULL, $1, $2, NULL, NULL, NULL);}
    ;
    
func_header
    : TK_IDENTIFIER func_params '=' type                                {$$ = ASTcria(AST_FUNC_HD, NULL, SYMBOL_AST($1), $2, $4, NULL, NULL);} 
    ;
    
func_params
    : '(' parameter_list ')'                                            {$$ = $2;}
    | '(' ')'                                                           {$$ = NULL;}
    ;
    
var_global
    : TK_IDENTIFIER '=' type ':' literal                                {$$ = ASTcria(AST_DECL_ID, NULL, SYMBOL_AST($1), $3, $5, NULL, NULL);}
    | vetor                                                             {$$ = $1;}
    ;
    
vetor
    : TK_IDENTIFIER '=' type '[' LIT_INTEGER ']' ':' literal_list       {$$ = ASTcria(AST_DECL_VEC, NULL, SYMBOL_AST($1), $3, SYMBOL_AST($5), $8, NULL);}
    | TK_IDENTIFIER '=' type '[' LIT_INTEGER ']'                        {$$ = ASTcria(AST_DECL_VEC, NULL, SYMBOL_AST($1), $3, SYMBOL_AST($5), NULL, NULL);}
    ;
    
literal_list
    : literal literal_list                                              {$$ = ASTcria(AST_LIT_LIST, NULL, $1, $2, NULL, NULL, NULL);}
    | literal                                                           {$$ = ASTcria(AST_LIT_LIST, NULL, $1, NULL, NULL, NULL, NULL);}
    ;
    
literal
    : LIT_TRUE                                                          {$$ = SYMBOL_AST($1);}
    | LIT_FALSE                                                         {$$ = SYMBOL_AST($1);}
    | LIT_INTEGER                                                       {$$ = SYMBOL_AST($1);}
    | LIT_FLOAT                                                         {$$ = SYMBOL_AST($1);}
    | LIT_CHAR                                                          {$$ = SYMBOL_AST($1);}
    ;
    
parameter_list
    : TK_IDENTIFIER '=' type p_list                                     {$$ = ASTcria(AST_PARAM_LIST, NULL, SYMBOL_AST($1), $3, $4, NULL, NULL);}
    ;
    
p_list
    : ',' parameter_list                                                {$$ = $2;}
    |                                                                   {$$ = NULL;}
    ;
    
type
    : KW_BOOL                                                           {$$ = SYMBOL_AST($1);}
    | KW_INT                                                            {$$ = SYMBOL_AST($1);}
    | KW_FLOAT                                                          {$$ = SYMBOL_AST($1);}
    | KW_CHAR                                                           {$$ = SYMBOL_AST($1);}
    ;
    
command_sequence
    : command command_sequence                                          {$$ = ASTcria(AST_COM_SEQ, NULL, $1, $2, NULL, NULL, NULL);}
    | command                                                           {$$ = ASTcria(AST_COM_SEQ, NULL, $1, NULL, NULL, NULL, NULL);}
    ;
    
command
    : TK_IDENTIFIER '=' expr                                            {$$ = ASTcria(AST_ATRIB, NULL, SYMBOL_AST($1), $3, NULL, NULL, NULL);}
    | TK_IDENTIFIER '[' expr ']' '=' expr                               {$$ = ASTcria(AST_ATRIB_VEC, NULL, SYMBOL_AST($1), $3, $6, NULL, NULL);}
    | KW_READ TK_IDENTIFIER                                             {$$ = ASTcria(AST_READ, NULL, SYMBOL_AST($2), NULL, NULL, NULL, NULL);}
    | KW_PRINT print_list                                               {$$ = ASTcria(AST_PRINT, NULL, $2, NULL, NULL, NULL, NULL);}
    | KW_RETURN expr                                                    {$$ = ASTcria(AST_RETURN, NULL, $2, NULL, NULL, NULL, NULL);}
    | flow_control                                                      {$$ = $1;}
    | command_block                                                     {$$ = $1;}
    |                                                                   {$$ = NULL;}
    ;
    
command_block
    : '{' command_sequence '}'                                          {$$ = $2;}
    ;
    
print_list
    : print_element ',' print_list                                      {$$ = ASTcria(AST_PRINT_LIST, NULL, $1, $3, NULL, NULL, NULL);}
    | print_element                                                     {$$ = ASTcria(AST_PRINT_LIST, NULL, $1, NULL, NULL, NULL, NULL);}
    ;
    
print_element
    : LIT_STRING                                                        {$$ = SYMBOL_AST($1);}
    | expr                                                              {$$ = $1;}
    ;
    
flow_control
    : KW_IF '(' expr ')' KW_THEN command                                {$$ = ASTcria(AST_IF, NULL, $3, $6, NULL, NULL, NULL);}
    | KW_IF '(' expr ')' KW_THEN command KW_ELSE command                {$$ = ASTcria(AST_IF_ELSE, NULL, $3, $6, $8, NULL, NULL);}
    | KW_WHILE '(' expr ')' command                                     {$$ = ASTcria(AST_WHILE, NULL, $3, $5, NULL, NULL, NULL);}
    | KW_LOOP '(' TK_IDENTIFIER ':' expr ',' expr ',' expr ')' command  {$$ = ASTcria(AST_LOOP, NULL, SYMBOL_AST($3), $5, $7, $9, $11);}
    ;
    
expr
    : TK_IDENTIFIER                                                     {$$ = SYMBOL_AST($1);}
    | TK_IDENTIFIER '[' expr ']'                                        {$$ = ASTcria(AST_VECTOR, NULL, SYMBOL_AST($1), $3, NULL, NULL, NULL);} 
    | func_call                                                         {$$ = $1;}
    | literal                                                           {$$ = $1;}
    | '(' expr ')'                                                      {$$ = $2;}
    | expr OPERATOR_LE expr                                             {$$ = ASTcria(AST_LE, NULL, $1, $3, NULL, NULL, NULL);}
    | expr OPERATOR_GE expr                                             {$$ = ASTcria(AST_GE, NULL, $1, $3, NULL, NULL, NULL);}
    | expr OPERATOR_EQ expr                                             {$$ = ASTcria(AST_EQ, NULL, $1, $3, NULL, NULL, NULL);}
    | expr OPERATOR_DIF expr                                            {$$ = ASTcria(AST_DIF, NULL, $1, $3, NULL, NULL, NULL);}
    | expr '+' expr                                                     {$$ = ASTcria(AST_ADD, NULL, $1, $3, NULL, NULL, NULL);}
    | expr '-' expr                                                     {$$ = ASTcria(AST_SUB, NULL, $1, $3, NULL, NULL, NULL);}
    | expr '*' expr                                                     {$$ = ASTcria(AST_MUL, NULL, $1, $3, NULL, NULL, NULL);}
    | expr '/' expr                                                     {$$ = ASTcria(AST_DIV, NULL, $1, $3, NULL, NULL, NULL);}
    | expr '<' expr                                                     {$$ = ASTcria(AST_LT, NULL, $1, $3, NULL, NULL, NULL);}
    | expr '>' expr                                                     {$$ = ASTcria(AST_GT, NULL, $1, $3, NULL, NULL, NULL);}
    | expr '|' expr                                                     {$$ = ASTcria(AST_OR, NULL, $1, $3, NULL, NULL, NULL);}
    | expr '^' expr                                                     {$$ = ASTcria(AST_AND, NULL, $1, $3, NULL, NULL, NULL);}
    | '~' expr                                                          {$$ = ASTcria(AST_UN_NEG, NULL, $2, NULL, NULL, NULL, NULL);}
    | '-' expr                                                          {$$ = ASTcria(AST_UN_MIN, NULL, $2, NULL, NULL, NULL, NULL);}
    ;
    
func_call
    : TK_IDENTIFIER '(' call_param ')'                                  {$$ = ASTcria(AST_FUNC_CALL, NULL, SYMBOL_AST($1), $3, NULL, NULL, NULL);}
    | TK_IDENTIFIER '(' ')'                                             {$$ = ASTcria(AST_FUNC_CALL, NULL, SYMBOL_AST($1), NULL, NULL, NULL, NULL);}
    ;
    
call_param
    : expr c_list                                                       {$$ = ASTcria(AST_CALL_PARAM, NULL, $1, $2, NULL, NULL, NULL);}
    ;
    
c_list
    : ',' call_param                                                    {$$ = $2;}
    |                                                                   {$$ = NULL;}
    ;
%%

int yyerror(char *msg)
{
    fprintf(stderr, "Syntax error at line %d. \n", getLineNumber());
    exit(3);
}
