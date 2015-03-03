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
 /*%code requires {#include "libsexp.h"}*/

/* all possible data in lexing/parsing process */

/* %token<atom> ATOM */
%token OPENPAREN CLOSEPAREN
%token SEPARATOR ASSIGNMENT NEWLINE
%token IDENTIFIER NUMBER
/* %type <sexp> sexp list list_contents */
/* program nonterminal allows us to handle empty input and
 * process the parse finish
 */
%start program

%%
program       : {}
        |       assignments { printf("parsed\n"); }

assignments   : assignment { printf("single assigment\n"); }
        |       assignments SEPARATOR assignment { printf("new assignment\n"); }

assignment    : IDENTIFIER ASSIGNMENT NUMBER SEPARATOR
/*      | sexp {g_parsed = $1;}; */
/* sexp          : */
/*        ATOM   {$$ = sexp_item_create_atom($1);} */
/*      | list   {$$ = $1;}; */
/* list          : */
/*        OPENPAREN CLOSEPAREN {$$ = sexp_item_create_atom(atom_token_nil_alloc()); } */
/*      | OPENPAREN list_contents CLOSEPAREN { $$ = $2; }; */
/* list_contents : */
/*        sexp { $$ = sexp_item_create_cons($1,sexp_item_create_atom(atom_token_nil_alloc()));} */
/*      | sexp list_contents { $$ = sexp_item_create_cons($1,$2); } */

%%

void yyerror (char const *s)
{
  fprintf (stderr, "libkv parse error: %s\n", s);
}


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








