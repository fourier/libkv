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
   const char* g_filename = 0;
   void yyerror (char const *s);
   static int g_verbose = 0;
}

/* we don't need yywrap since we assume what we will
 * parse one file at a time
 */
%option noyywrap
%option yylineno
                        
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
letter               [[:alpha:]]|"_"
identifier-symbol    {letter}|[[:digit:]]
identifier           {letter}{identifier-symbol}*

/* parens */                                    
open-paren            "["
close-paren           "]"

/* assignments */
assign                "="                                                

/* commas */
comma                 [[:space:]]*","[[:space:]]*                        

/* semicolons */
semicolon             [[:space:]]*";"[[:space:]]*
                                                
/* comments */
comment               [#%].*\n
                        
%%

{integer-number}        {
      //yylval.atom = atom_token_integer_alloc(yytext,yytext+yyleng);
      //return ATOM;
      int value = strtol(yytext, 0, 10);
      if (g_verbose) printf("Integer: %d\n", value);
      yylval.int_value = value;
      return INTEGER;
    }
    
{floating-point-number} {
      /* yylval.atom = atom_token_float_alloc(yytext,yytext+yyleng); */
      /* return ATOM; */
      double value = strtod(yytext, 0);
      if (g_verbose) printf("Double: %f\n", value);
      yylval.dbl_value = value;
      return DOUBLE;
    }
    
{string}                {
      /* yylval.atom = atom_token_string_alloc(yytext+1,yytext+yyleng-1); */
      /* return ATOM; */
      char* str = malloc(yyleng-1);
      memcpy(str, yytext+1, yyleng-2);
      str[yyleng-1] = '\0';
      if (g_verbose) printf("String: %s\n", str);
      yylval.string = str;
      return STRING;
    }

{identifier}                {
      /* yylval.atom = atom_token_symbol_alloc(yytext,yytext+yyleng); */
      /* return ATOM;     */
      char* str = malloc(yyleng+1);
      memcpy(str, yytext, yyleng);
      str[yyleng] = '\0';
      if (g_verbose) printf("Identifier: %s\n", str);
      yylval.identifier = str;
      return IDENTIFIER;
    }
    
{open-paren}            {
      if (g_verbose) printf("Open paren\n");
      return OPENPAREN;
    }

{close-paren}           {
      if (g_verbose) printf("Close paren\n");
      return CLOSEPAREN;
    }

{assign}           {
      if (g_verbose) printf("Assign\n");
      return ASSIGNMENT;
    }

{comma}           {
      if (g_verbose) printf("Comma\n");
      return COMMA;
    }

{semicolon}           {
      if (g_verbose) printf("Semicolon\n");
      return SEMICOLON;
    }

{comment}           {
      if (g_verbose) printf("Comment\n");
      /* return CLOSEPAREN; */
    }
                
[\n \t]+          /* eat up whitespace */

.                   {
      char message[25];
      sprintf(message, "Unknown character %c\n", yytext[0]);
      yyerror(message);
    }

%%

void yyerror (char const *s)
{
  if (g_filename) 
    fprintf(stderr, "%s:%d: %s at %s\n", g_filename, yylineno, s, yytext);
  else
    fprintf(stderr, "%d: %s at %s\n", yylineno, s, yytext);
}

