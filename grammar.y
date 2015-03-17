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
    struct {
        int is_int;
        int int_val;
        double dbl_val;
    } number;
}
                            
%token OPENPAREN CLOSEPAREN
%token COMMA SEMICOLON ASSIGNMENT
%token  <identifier> IDENTIFIER
%token  <string> STRING
%token  <int_value> INTEGER
%token  <dbl_value> DOUBLE
%type   <number>        number
                        
/* program nonterminal allows us to handle empty input and
 * process the parse finish
 */
%start program

%%
program          : {}
        |       assignments SEMICOLON { kv_table_dump(); }

assignments      : assignment { printf("first assigment\n"); }
        |       assignments SEMICOLON assignment { printf("one more assignment\n"); }

number           : INTEGER { $<number>$.is_int = 1; $<number>$.int_val = $1; }
        |       DOUBLE { $<number>$.is_int = 0; $<number>$.dbl_val = $1; }

matrix           : OPENPAREN matrix_contents CLOSEPAREN

/* contents is a separated list with optional semicolon */
matrix_contents  : separated_list  { printf("matrix done\n"); }
        |       separated_list SEMICOLON { printf("matrix done\n"); }

separated_list   : matrix_row { printf("first row done\n"); }
        |       separated_list SEMICOLON matrix_row { printf("next row done\n"); }

/* matrix row is a list of numbers separated by comma,
 * with the optional comma at the end
 */
matrix_row       : numbers_list
        |       numbers_list COMMA

numbers_list     : number { printf($1.is_int ? "first %d " : "first %f ", $1.is_int ? $1.int_val : $1.dbl_val); }
        |       numbers_list COMMA number { printf($3.is_int ? "rest %d " : "rest %f ", $3.is_int ? $3.int_val : $3.dbl_val); }

assignment    : IDENTIFIER ASSIGNMENT INTEGER { struct kv_value_t val; kv_init_int(&val, $3); kv_table_put($1, &val); }
        |       IDENTIFIER ASSIGNMENT DOUBLE { struct kv_value_t val; kv_init_double(&val, $3); kv_table_put($1, &val); }
        |       IDENTIFIER ASSIGNMENT matrix
        |       IDENTIFIER ASSIGNMENT STRING { struct kv_value_t val; kv_init_string(&val, $3); kv_table_put($1, &val); }

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








