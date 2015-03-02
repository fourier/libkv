/*
 * Lexer for key-value library
 */

%top{
   /* This code goes at the "top" of the generated file. */
   #include <stdint.h>
   #include <inttypes.h>
   #include <stdio.h>

   //#include "atomtoken.h"
   #include "libkv.tab.h"
}

/* we don't need yywrap since we assume what we will
 * parse one file at a time
 */
%option noyywrap

/* numbers */
sign                  "+"|"-"
decimal-point         "."
exponent-marker       "e"|"E"
exponent              {exponent-marker}{sign}?[[:digit:]]+
integer-number        {sign}?[[:digit:]]+
floating-point-number {sign}?[[:digit:]]*{decimal-point}[[:digit:]]*{exponent}?|{sign}?[[:digit:]]+({decimal-point}[[:digit:]]*)?{exponent}

/* strings */
escape                \\
double-quote          \"
escaped-double-quote {escape}{double-quote}
string-char          [[:graph:]]{-}["]
string               {double-quote}({string-char}|[[:space:]]|{escaped-double-quote})*{double-quote}

/* identifiers */
letter              [[:alpha:]]|"_"
identifier-symbol   {letter}|[[:digit:]]
identifier          {letter}{identifier-symbol}*

/* parens */                                    
open-paren           "["
close-paren          "]"

/* assignments */
assign               "="                                                

/* dividers */
divider              [[:space:]]*","[[:space:]]*                        

/* separator */
separator              [[:space:]]*";"[[:space:]]*
                                                
/* comments */
comment "%".*
                        
%%

{integer-number}        {
      //yylval.atom = atom_token_integer_alloc(yytext,yytext+yyleng);
      //return ATOM;
      int value = strtol(yytext, 0, 10);
      printf("Integer: %d\n", value);
    }
    
{floating-point-number} {
      /* yylval.atom = atom_token_float_alloc(yytext,yytext+yyleng); */
      /* return ATOM; */
      double value = strtod(yytext, 0);
      printf("Double: %f\n", value);
    }
    
{string}                {
      /* yylval.atom = atom_token_string_alloc(yytext+1,yytext+yyleng-1); */
      /* return ATOM; */
      char* str = malloc(yyleng-1);
      memcpy(str, yytext+1, yyleng-2);
      str[yyleng-1] = '\0';
      printf("String: %s\n", str);
      free(str);
    }

{identifier}                {
      /* yylval.atom = atom_token_symbol_alloc(yytext,yytext+yyleng); */
      /* return ATOM;     */
      char* str = malloc(yyleng+1);
      memcpy(str, yytext, yyleng);
      str[yyleng] = '\0';
      printf("Identifier: %s\n", str);
      free(str);
    }
    
{open-paren}            {
      printf("Open paren\n");
      /* return OPENPAREN; */
    }

{close-paren}           {
      printf("Close paren\n");
      /* return CLOSEPAREN; */
    }

{assign}           {
      printf("Assign\n");
      /* return CLOSEPAREN; */
    }

{divider}           {
      /* printf("Divider\n"); */
      /* return CLOSEPAREN; */
    }

{separator}           {
      printf("Separator\n");
      /* return CLOSEPAREN; */
    }


{comment}           {
      printf("Comment\n");
      /* return CLOSEPAREN; */
    }
                

[ \t\n]+          /* eat up whitespace */

%%

