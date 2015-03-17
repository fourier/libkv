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
    kv_number num;
}
                            
%token OPENPAREN CLOSEPAREN
%token COMMA SEMICOLON ASSIGNMENT
%token  <identifier> IDENTIFIER
%token  <string> STRING
%token  <int_value> INTEGER
%token  <dbl_value> DOUBLE
%type   <num>        number
                        
/* program nonterminal allows us to handle empty input and
 * process the parse finish
 */
%start program

%%
program          : {}
        |       assignments SEMICOLON { kv_table_dump(); }

/* assignments are semicolon-separated */
assignments      : assignment { printf("first assigment\n"); }
        |       assignments SEMICOLON assignment { printf("one more assignment\n"); }

/* number is a nonterminal for heterogeneous vector/matrix */
number           : INTEGER { KV_NUMBER_SET_INT($<num>$, $1); }
        |       DOUBLE { KV_NUMBER_SET_DBL($<num>$, $1); }

/* vector is either single value in [], like [1], or list of semicolon-separated
 * values
 */
vector           : OPENPAREN vector_contents CLOSEPAREN { printf("\nvector done\n"); }

vector_contents  :
/* handle single values */
        |       number {
            printf("single: "); KV_NUMBER_PRINT($1); 
 }

        |       number COMMA {
            printf("single: "); KV_NUMBER_PRINT($1); 
}
        |       number SEMICOLON  {
            printf("single: "); KV_NUMBER_PRINT($1); 
}
        |       number COMMA SEMICOLON  {
            printf("single: "); KV_NUMBER_PRINT($1); 
}
/* handle list of values */
        |       vector_column
        |       vector_column SEMICOLON

/* list of values is at least 2 elements */
vector_column     : number SEMICOLON number { KV_NUMBER_PRINT($1); printf(", "); KV_NUMBER_PRINT($3)}
        |       vector_column SEMICOLON number { printf(", "); KV_NUMBER_PRINT($3); }


matrix           : OPENPAREN matrix_contents CLOSEPAREN

/* contents is a separated list with optional semicolon */
matrix_contents  : separated_list  { printf("matrix done\n"); }
        |       separated_list SEMICOLON { printf("matrix done\n"); }

separated_list   : matrix_row { printf("\nfirst row done\n"); }
        |       separated_list SEMICOLON matrix_row { printf("\nnext row done\n"); }

/* matrix row is a list of numbers separated by comma,
 * with the optional comma at the end
 */
matrix_row       : numbers_list
        |       numbers_list COMMA

/* list of numbers shall contain at least 2 comma-separated numbers */
numbers_list     : number COMMA number { KV_NUMBER_PRINT($1); printf(", "); KV_NUMBER_PRINT($3);}
        |       numbers_list COMMA number { printf(", "); KV_NUMBER_PRINT($3); }



/* all possible assignments */
assignment    : IDENTIFIER ASSIGNMENT INTEGER { struct kv_value_t val; kv_init_int(&val, $3); kv_table_put($1, &val); }
        |       IDENTIFIER ASSIGNMENT DOUBLE { struct kv_value_t val; kv_init_double(&val, $3); kv_table_put($1, &val); }
        |       IDENTIFIER ASSIGNMENT matrix
        |       IDENTIFIER ASSIGNMENT vector
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








