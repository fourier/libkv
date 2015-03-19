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

/*
 * Lexer for key-value library
 */

%top{
   /* This code goes at the "top" of the generated file. */
   #include <stdint.h>
   #include <inttypes.h>
   #include <stdio.h>

   #include "libkv.tab.h"
   void yyerror (struct kv_table_t* table, char const *s);
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
      int value = strtol(yytext, 0, 10);
      yylval.int_value = value;
      return INTEGER;
    }
    
{floating-point-number} {
      double value = strtod(yytext, 0);
      yylval.dbl_value = value;
      return DOUBLE;
    }
    
{string}                {
      int size = yyleng-2; /* skip quotation characters */
      char* str = malloc(size+1); /* including 0 */
      memcpy(str, yytext+1, size);
      str[size] = '\0';
      yylval.string = str;
      return STRING;
    }

{identifier}                {
      char* str = malloc(yyleng+1);
      memcpy(str, yytext, yyleng);
      str[yyleng] = '\0';
      yylval.identifier = str;
      return IDENTIFIER;
    }
    
{open-paren}            {
      return OPENPAREN;
    }

{close-paren}           {
      return CLOSEPAREN;
    }

{assign}           {
      return ASSIGNMENT;
    }

{comma}           {
      return COMMA;
    }

{semicolon}           {
      return SEMICOLON;
    }

{comment}           {
      /* return CLOSEPAREN; */
    }
                
[\n \t]+          /* eat up whitespace */ {}


.                   {} /* ignore all other characters */

%%

void yyerror (struct kv_table_t* table, char const *s)
{
    fprintf(stderr, "error in line %d: %s\n", yylineno, s, yytext);
}

