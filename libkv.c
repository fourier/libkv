/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* local includes */
#include "libkv.h"
#include "libkv.yy.h"
#include "libkv.tab.h"

/* system includes */
#include <assert.h>

struct kv_table_t* libkv_parse_file(FILE* file)
{
  struct kv_table_t* table = kv_table_alloc();
  assert(file);
  if (g_verbose)
    printf("verbose\n");
  yyin = file;
  yyparse(table);
  
  return table;
}

struct kv_table_t* libkv_parse_string(const char* string)
{
  struct kv_table_t* table = kv_table_alloc();
  assert(string);

  return table;
}
