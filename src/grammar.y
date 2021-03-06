/*
 Copyright (C) 2015 Alexey Veretennikov (alexey dot veretennikov at gmail.com)
 
 This file is part of Libkv.

 Libkv is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published
 by the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Libkv is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with Libkv.  If not, see <http://www.gnu.org/licenses/>.
*/

%{
#include <stdio.h>

/* lexer forward declaration */
/*
int yylex(void);
int yylex_destroy (void );
void* yy_scan_string (const char *yy_str);
*/

/* increase limit for maximum number of shift states
 * without reduce - necessary for big files
 */
#define YYMAXDEPTH 100000
#define YYINITDEPTH 10000

extern FILE* yyin;

%}
/* parsing argument - supplied to yyparse */                       
%parse-param {struct kv_table_t* table}
/* verbose error messages */
/* allow debug mode */
%debug
/* code to be placed to the header file */
%code requires {
#include "libkv.h"
}
                        
/* all possible data in lexing/parsing process */
%union {
    const char* identifier;
    const char* string;
    double dbl_value;
    int int_value;
    kv_number_t num;
    kv_vector_t* vector;
    kv_matrix_t* matrix;
}
                            
%token OPENPAREN CLOSEPAREN
%token COMMA SEMICOLON ASSIGNMENT
%token  <identifier> IDENTIFIER
%token  <string> STRING
%token  <int_value> INTEGER
%token  <dbl_value> DOUBLE
%type   <num>        number
%type   <vector>     vector;
%type   <vector>     vector_contents;
%type   <vector>     vector_column;
%type   <matrix>     matrix;
%type   <matrix>     matrix_contents;
%type   <matrix>     separated_list
%type   <vector>     matrix_row;
%type   <vector>     numbers_list
                        
/* program nonterminal allows us to handle empty input and
 * process the parse finish
 */
%start program

%%
program          : {}
        |       assignments {}


/* assignments are semicolon-separated */
assignments      : assignment SEMICOLON
        |       assignments assignment SEMICOLON

/* number is a nonterminal for heterogeneous vector/matrix */
number           : INTEGER { KV_NUMBER_SET_INT($<num>$, $1); }
        |       DOUBLE { KV_NUMBER_SET_DBL($<num>$, $1); }

/* vector is either single value in [], like [1], or list of semicolon-separated
 * values
 */
vector           : OPENPAREN vector_contents CLOSEPAREN {
            $<vector>$ = $2;
}

vector_contents  :
/* handle single values */
               number {
            $<vector>$ = kv_vector_alloc_one_elt(&$1);
 }

        |       number COMMA {
            $<vector>$ = kv_vector_alloc_one_elt(&$1);
}
        |       number SEMICOLON  {
            $<vector>$ = kv_vector_alloc_one_elt(&$1);
}
        |       number COMMA SEMICOLON  {
            $<vector>$ = kv_vector_alloc_one_elt(&$1);
}
/* handle list of values */
        |       vector_column { $<vector>$ = $1; }
        |       vector_column SEMICOLON { $<vector>$ = $1; }

/* list of values is at least 2 elements */
vector_column     : number SEMICOLON number {
            $<vector>$ = kv_vector_alloc_two_elts(&$1, &$3);
}
     |       vector_column SEMICOLON number { kv_vector_push_back($<vector>$, &$3); }


matrix           : OPENPAREN matrix_contents CLOSEPAREN
                { $<matrix>$ = $2; }

/* contents is a separated list with optional semicolon */
matrix_contents  : separated_list  { $<matrix>$ = $1; }
        |       separated_list SEMICOLON { $<matrix>$ = $1; }

separated_list   : matrix_row {
            $<matrix>$ = kv_matrix_alloc($1);
            free($1);
}
        |       separated_list SEMICOLON matrix_row {
            if (kv_matrix_add_row($<matrix>$, $3))
            {
              char msg[80];
              sprintf(msg, "Incorrect row size %d for matrix with number of columns %d", $3->size, $<matrix>$->cols);
              yyerror(table, msg);
              /* free the matrix contents */
              kv_matrix_fini($<matrix>$);
              /* free the matrix struct */
              free($<matrix>$);
              /* free the vector contents */
              kv_vector_fini($3);
              /* free the vector struct */
              free($3);
              /* free the identifier 3 steps above in stack */
              free((char*)yyvsp[-3].identifier);
              YYABORT;
            }
            free($3);
 }

/* matrix row is a list of numbers separated by comma,
 * with the optional comma at the end
 */
matrix_row       : numbers_list { $<vector>$ = $1; }
        |       numbers_list COMMA { $<vector>$ = $1; }

/* list of numbers shall contain at least 2 comma-separated numbers */
numbers_list     : number COMMA number { $<vector>$ = kv_vector_alloc_two_elts(&$1, &$3); }
        |       numbers_list COMMA number { kv_vector_push_back($<vector>$, &$3); }



/* all possible assignments */
assignment    : IDENTIFIER ASSIGNMENT INTEGER { struct kv_value_t val; kv_init_int(&val, $3); kv_table_put(table, $1, &val); free((char*)$1); }
|       IDENTIFIER ASSIGNMENT DOUBLE { struct kv_value_t val; kv_init_double(&val, $3); kv_table_put(table, $1, &val); free((char*)$1); }
|       IDENTIFIER ASSIGNMENT vector { struct kv_value_t val; kv_init_vector(&val, $3); kv_table_put(table, $1, &val); free((char*)$1); }
|       IDENTIFIER ASSIGNMENT matrix {
    struct kv_value_t val;
    if ($3->rows == 1)
    {
        kv_init_vector(&val, kv_matrix_convert_vector($3));
        free($3);
    }
    else
      kv_init_matrix(&val, $3);
    kv_table_put(table, $1, &val);
    free((char*)$1);
 }
|       IDENTIFIER ASSIGNMENT STRING { struct kv_value_t val; kv_init_string(&val, $3); kv_table_put(table, $1, &val); free((char*)$1); }


%%











