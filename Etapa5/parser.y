%{
    #include "ast.h"
    #include "hash.h"
    #include "tacs.h"

    // Helper to create a symbol AST
    #define SYMBOL_AST(x) AST_create(AST_SYMBOL, x, NULL, NULL, NULL, NULL, NULL)

    AST* ASTroot = NULL;
%}


%union{
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

%token TOKEN_ERROR

 // Precedence rules
%left '|' '^'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF
%left '+' '-'
%left '*' '/'
%left '~'

// Types for rules
%type<ast> programa;
%type<ast> ldecl;


%type<ast> any_lit
%type<ast> lit_bool
%type<ast> any_kw_type;

%type<ast> declvar;
%type<ast> declvar_not_vector;
%type<ast> declvar_vector;

%type<ast> lvector;

%type<ast> declfun;
%type<ast> fun_header;
%type<ast> fun_params;
%type<ast> lparam;
%type<ast> rest_params;

%type<ast> comm_block;

%type<ast> comm_seq;
%type<ast> command;
%type<ast> attrib;
%type<ast> return_command;
%type<ast> flow_command;
%type<ast> read_command;
%type<ast> print_command;
%type<ast> lprint;

%type<ast> expression

%type<ast> fun_call
%type<ast> lparam_fun_call
%type<ast> rest_params_fun_call

%{
int yylex();
int yyerror();
%}

%%

programa: ldecl         { $$ = $1; 
                        ASTroot = $$;
                        tacPrintBackwards(codeGen($1));
                        }
    ;

ldecl: declvar ';' ldecl    { $$ = AST_create( AST_LDECL, NULL, $1, $3, NULL, NULL, NULL); }
    | declfun ';' ldecl     { $$ = AST_create( AST_LDECL, NULL, $1, $3, NULL, NULL, NULL); }
    |                       { $$ = NULL; }
    ;

lit_bool: LIT_TRUE      { $$ = SYMBOL_AST($1); }
    | LIT_FALSE         { $$ = SYMBOL_AST($1); }
    ;

any_kw_type: KW_CHAR    { $$ = SYMBOL_AST($1);  }
    | KW_INT            { $$ = SYMBOL_AST($1);  }
    | KW_FLOAT          { $$ = SYMBOL_AST($1);  }
    | KW_BOOL           { $$ = SYMBOL_AST($1);  }
    ;

any_lit: LIT_CHAR       { $$ = SYMBOL_AST($1); }
    | LIT_INTEGER       { $$ = SYMBOL_AST($1); }
    | LIT_FLOAT         { $$ = SYMBOL_AST($1); }
    | lit_bool          { $$ = $1; }
    ;

declvar: declvar_not_vector     { $$ = $1; }
    | declvar_vector            { $$ = $1; }
    ;

declvar_not_vector: TK_IDENTIFIER '=' any_kw_type ':' any_lit     { $$ = AST_create( AST_DECLVAR_NOT_VECTOR, NULL, SYMBOL_AST($1), $3, $5, NULL, NULL); }
    ;

declvar_vector: TK_IDENTIFIER '=' any_kw_type '[' LIT_INTEGER ']' ':' lvector   { $$ = AST_create( AST_DECLVAR_VECTOR, NULL, SYMBOL_AST($1), $3, SYMBOL_AST($5), $8, NULL); }
    | TK_IDENTIFIER '=' any_kw_type '[' LIT_INTEGER ']'                         { $$ = AST_create( AST_DECLVAR_VECTOR, NULL, SYMBOL_AST($1), $3, SYMBOL_AST($5), NULL, NULL); }
    ;

lvector: any_lit lvector            { $$ = AST_create( AST_LVECTOR, NULL, $1, $2, NULL, NULL, NULL); }
    | any_lit                       { $$ = AST_create( AST_LVECTOR, NULL, $1, NULL, NULL, NULL, NULL); }
    ;

declfun: fun_header comm_block        { $$ = AST_create( AST_FUN, NULL, $1, $2, NULL, NULL, NULL); }
    ;

fun_header: TK_IDENTIFIER fun_params '=' any_kw_type  { $$ = AST_create( AST_FUN_HEADER, NULL, SYMBOL_AST($1), $2, $4, NULL, NULL); }
    ;

fun_params: '(' lparam ')'          { $$ = $2; }
    | '(' ')'                       { $$ = NULL; }
    ;

lparam: TK_IDENTIFIER '=' any_kw_type rest_params   { $$ = AST_create( AST_FUN_PARAMS, NULL, SYMBOL_AST($1), $3, $4, NULL, NULL); }
    ;

rest_params: ',' lparam                             { $$ = $2; }
    |                                               { $$ = NULL; }
    ;

comm_block: '{' comm_seq '}'                        { $$ = $2; }
    ;

comm_seq: command comm_seq                          { $$ = AST_create( AST_COMM_SEQ, NULL, $1, $2, NULL, NULL, NULL); }
    | command                                       { $$ = AST_create( AST_COMM_SEQ, NULL, $1, NULL, NULL, NULL, NULL); }
    ;

command: attrib                                     { $$ = $1; }
    | flow_command                                  { $$ = $1; }
    | read_command                                  { $$ = $1; }
    | print_command                                 { $$ = $1; }
    | return_command                                { $$ = $1; }
    | comm_block                                    { $$ = $1; }
    |                                               { $$ = NULL; }
    ;

attrib: TK_IDENTIFIER '=' expression                        { $$ = AST_create(AST_ATTRIB, NULL, SYMBOL_AST($1), $3, NULL, NULL, NULL); }
    | TK_IDENTIFIER '[' expression ']' '=' expression       { $$ = AST_create(AST_ATTRIB_VEC, NULL, SYMBOL_AST($1), $3, $6, NULL, NULL); }
    ;

read_command: KW_READ TK_IDENTIFIER                         { $$ = AST_create(AST_READ, NULL, SYMBOL_AST($2), NULL, NULL, NULL, NULL); }
    ;

print_command: KW_PRINT lprint                              { $$ = AST_create(AST_PRINT, NULL, $2, NULL, NULL, NULL, NULL); }
    ;

lprint: LIT_STRING ',' lprint                               { $$ = AST_create(AST_PRINT_PARAMS, NULL, SYMBOL_AST($1), $3, NULL, NULL, NULL); }
    | LIT_STRING                                            { $$ = AST_create(AST_PRINT_PARAMS, NULL, SYMBOL_AST($1), NULL, NULL, NULL, NULL); }
    | expression ',' lprint                                 { $$ = AST_create(AST_PRINT_PARAMS, NULL, $1, $3, NULL, NULL, NULL); }
    | expression                                            { $$ = AST_create(AST_PRINT_PARAMS, NULL, $1, NULL, NULL, NULL, NULL); }
    ;

return_command: KW_RETURN expression                        { $$ = AST_create(AST_RETURN, NULL, $2, NULL, NULL, NULL, NULL); }
    ;

flow_command: KW_IF '(' expression ')' KW_THEN command                                      { $$ = AST_create(AST_IF, NULL, $3, $6, NULL, NULL, NULL); }
    | KW_IF '(' expression ')' KW_THEN command KW_ELSE command                              { $$ = AST_create(AST_IF_ELSE, NULL, $3, $6, $8, NULL, NULL); }
    | KW_WHILE '(' expression ')' command                                                   { $$ = AST_create(AST_WHILE, NULL, $3, $5, NULL, NULL, NULL); }
    | KW_LOOP '(' TK_IDENTIFIER ':' expression ',' expression ',' expression ')' command    { $$ = AST_create(AST_LOOP, NULL, SYMBOL_AST($3), $5, $7, $9, $11); }
    ;

expression: TK_IDENTIFIER                       { $$ = SYMBOL_AST($1); }
    | TK_IDENTIFIER '[' expression ']'          { $$ = AST_create( AST_SYMBOL_VECTOR, NULL, SYMBOL_AST($1), $3, NULL, NULL, NULL); }
    | any_lit                                   { $$ = $1; }
    | '(' expression ')'                        { $$ = $2; }
    | '-' expression                            { $$ = AST_create(AST_UN_MIN, NULL, $2, NULL, NULL, NULL, NULL); }
    | '~' expression                            { $$ = AST_create(AST_UN_NEG, NULL, $2, NULL, NULL, NULL, NULL); }
    | expression '+' expression                 { $$ = AST_create(AST_ADD, NULL, $1, $3, NULL, NULL, NULL); }
    | expression '-' expression                 { $$ = AST_create(AST_SUB, NULL, $1, $3, NULL, NULL, NULL); }
    | expression '*' expression                 { $$ = AST_create(AST_MUL, NULL, $1, $3, NULL, NULL, NULL); }
    | expression '/' expression                 { $$ = AST_create(AST_DIV, NULL, $1, $3, NULL, NULL, NULL); }
    | expression '<' expression                 { $$ = AST_create(AST_LT, NULL, $1, $3, NULL, NULL, NULL); }
    | expression '>' expression                 { $$ = AST_create(AST_GT, NULL, $1, $3, NULL, NULL, NULL); }
    | expression '|' expression                 { $$ = AST_create(AST_OR, NULL, $1, $3, NULL, NULL, NULL); }
    | expression '^' expression                 { $$ = AST_create(AST_AND, NULL, $1, $3, NULL, NULL, NULL); }
    | expression OPERATOR_LE expression         { $$ = AST_create(AST_LE, NULL, $1, $3, NULL, NULL, NULL); }
    | expression OPERATOR_GE expression         { $$ = AST_create(AST_GE, NULL, $1, $3, NULL, NULL, NULL); }
    | expression OPERATOR_EQ expression         { $$ = AST_create(AST_EQ, NULL, $1, $3, NULL, NULL, NULL); }
    | expression OPERATOR_DIF expression        { $$ = AST_create(AST_DIF, NULL, $1, $3, NULL, NULL, NULL); }
    | fun_call                                  { $$ = $1; }
    ;

fun_call: TK_IDENTIFIER '(' lparam_fun_call ')'     { $$ = AST_create(AST_FUN_CALL, NULL, SYMBOL_AST($1), $3, NULL, NULL, NULL); }
    | TK_IDENTIFIER  '(' ')'                        { $$ = AST_create(AST_FUN_CALL, NULL, SYMBOL_AST($1), NULL, NULL, NULL, NULL); }
    ;

lparam_fun_call: expression rest_params_fun_call    { $$ = AST_create(AST_LPARAM, NULL, $1, $2, NULL, NULL, NULL); }
    ;

rest_params_fun_call: ',' lparam_fun_call           { $$ = $2; }
    |                                               { $$ = NULL; }
    ;


%%

#include <stdio.h>
#include <stdlib.h>
extern int getLineNumber();

int yyerror()
{
    fprintf(stderr, "Syntax error at line %d\n", getLineNumber());
    exit(3);
}