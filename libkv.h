/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
#ifndef LIBKV_H
#define LIBKV_H

typedef enum {
  VALUE_STRING,
  VALUE_DOUBLE,
  VALUE_INTEGER,
  VALUE_INT_VECTOR,
  VALUE_DOUBLE_VECTOR,
  VALUE_INT_MATRIX,
  VALUE_DOUBLE_MATRIX
} value_type;

typedef struct  {
  value_type type;
  union {
    double double_value;
    int int_value;
    void* pointer;    
  } data;
} kv_value_t;

const kv_value_t* kv_get(const char* name);
void kv_put(const char* name, kv_value_t* value);


#endif /* LIBKV_H */

