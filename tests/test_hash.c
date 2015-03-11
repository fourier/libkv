/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
#include "libkv.h"

int main(int argc, char *argv[])
{
  const char* str1 = "hello";
  const char* str2 = "world";
  kv_value_t val;
  kv_init_int(&val, 19);
  kv_put("A", &val);
  kv_init_double(&val, 2.74);
  kv_put("numberE", &val);
  kv_init_string(&val, str1);
  kv_put("A", &val);
  kv_init_string(&val, str2);
  kv_put("some_message", &val);
  kv_dump();
  
  return 0;
}
