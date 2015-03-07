%{
#include <stdio.h>

/* #include "atomtoken.h" */
/* #include "sexpitem.h" */

/* error handler */
void yyerror (char const *s);
/* lexer forward declaration */
int yylex(void);
int yylex_destroy (void );
void* yy_scan_string (const char *yy_str);

/* /\* parse result goes here *\/ */
/* static sexp_item* g_parsed = 0; */

/* increase limit for maximum number of shift states
 * without reduce - necessary for big files
 */
#define YYMAXDEPTH 100000
#define YYINITDEPTH 10000

extern FILE* yyin;

%}

/* allow debug mode */
%debug
/* code to be placed to the header file */
%code requires {#include "libkv.h"}
                        
/* all possible data in lexing/parsing process */
%union {
    const char* identifier;
    const char* string;
    double dbl_value;
    int int_value;
}
                            
/* %token<atom> ATOM */
%token OPENPAREN CLOSEPAREN
%token COMMA SEMICOLON ASSIGNMENT
%token  <identifier> IDENTIFIER
%token  <string> STRING
%token  <int_value> INTEGER
%token  <dbl_value> DOUBLE
/* %type <sexp> sexp list list_contents */
/* program nonterminal allows us to handle empty input and
 * process the parse finish
 */
%start program

%%
program          : {}
        |       assignments SEMICOLON { printf("parsed\n"); }

assignments      : assignment { printf("first assigment\n"); }
        |       assignments SEMICOLON assignment { printf("one more assignment\n"); }

number           : INTEGER | DOUBLE

matrix           : OPENPAREN matrix_contents CLOSEPAREN

/* contents is a separated list with optional semicolon */
matrix_contents  : separated_list  { printf("matrix\n"); }
        |       separated_list SEMICOLON { printf("matrix\n"); }

separated_list   : matrix_row
        |       separated_list SEMICOLON matrix_row

/* matrix row is a list of numbers separated by comma,
 * with the optional comma at the end
 */
matrix_row       : numbers_list
        |       numbers_list COMMA

numbers_list     : number
        |       numbers_list COMMA number

assignment    : IDENTIFIER ASSIGNMENT number
        |       IDENTIFIER ASSIGNMENT matrix
        |       IDENTIFIER ASSIGNMENT STRING

%%



/* sexp_item* sexp_parse_file(FILE* input) */
/* { */
/*     sexp_item* result = 0; */
/*     yyin = input; */
/*     if (yyparse() == 0) result = g_parsed; */
/*     yylex_destroy(); */
    
/*     return result; */
/* } */


/* sexp_item* sexp_parse_str(const char* read_buffer) */
/* { */
/*     sexp_item* result = 0; */
/*     yy_scan_string(read_buffer); */
/*     if (yyparse() == 0) result = g_parsed; */
/*     yylex_destroy(); */
    
/*     return result; */
/* } */








