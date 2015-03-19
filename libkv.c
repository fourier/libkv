/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
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
    kv_table_deep_free(table);
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
    kv_table_deep_free(table);
    return 0;
  }

  return table;
}
