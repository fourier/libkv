/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
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

/* local includes */
#include "libkv.h"
#include "libkv.yy.h"
#include "libkv.tab.h"

/* system includes */
#include <assert.h>

/* older bison not generates yyparse in header, so declare it here */
int yyparse (struct kv_table_t* table);

struct kv_table_t* libkv_parse_file(FILE* file)
{
  struct kv_table_t* table = kv_table_alloc();
  assert(file);
  yyin = file;
  if (yyparse(table))
  {
    kv_table_free(table);
    return 0;
  }
  return table;
}

struct kv_table_t* libkv_parse_string(const char* string)
{
  struct kv_table_t* table = kv_table_alloc();
  YY_BUFFER_STATE string_buffer;
  assert(string);
  string_buffer = yy_scan_string(string); 
  yy_switch_to_buffer( string_buffer ); 
  if (yyparse(table))
  {
    kv_table_free(table);
    return 0;
  }

  return table;
}
