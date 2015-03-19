/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* local includes */
#include "kv.h"

/* system includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void kv_init_int( kv_value_t* kv, int value)
{
  kv->type = VALUE_INTEGER;
  kv->data.int_value = value;
}

void kv_init_double( kv_value_t* kv, double value)
{
  kv->type = VALUE_DOUBLE;
  kv->data.dbl_value = value;
}

void kv_init_string( kv_value_t* kv, const char* string)
{
  kv->type = VALUE_STRING;
  kv->data.pointer = (void*)string;
}

void kv_init_vector( kv_value_t* kv, const kv_vector_t* value)
{
  kv->type = VALUE_VECTOR;
  kv->data.pointer = (void*)value;
}

void kv_init_matrix(kv_value_t* kv, const kv_matrix_t* value)
{
  kv->type = VALUE_MATRIX;
  kv->data.pointer = (void*)value;
}

void kv_fini(kv_value_t* kv)
{
  switch (kv->type)
  {
  case VALUE_STRING:
    free(kv->data.pointer);
    break;
  case VALUE_VECTOR:
    kv_vector_fini((kv_vector_t*)kv->data.pointer);
    free(kv->data.pointer);
    break;
  case VALUE_MATRIX:
    kv_matrix_fini((kv_matrix_t*)kv->data.pointer);
    free(kv->data.pointer);
    break;
  case VALUE_DOUBLE:
  case VALUE_INTEGER:
  default:
    break;
  }
  memset(kv, 0, sizeof(*kv));
}


value_type kv_type(const  kv_value_t* kv)
{
  return kv->type;
}

int kv_int(const  kv_value_t* kv)
{
  return kv->data.int_value;
}

double kv_double(const  kv_value_t* kv)
{
  return kv->data.dbl_value;
}

const char* kv_string(const  kv_value_t* kv)
{
  return (const char*)kv->data.pointer;
}

const kv_vector_t* kv_vector(const kv_value_t* kv)
{
  return (const kv_vector_t*)kv->data.pointer;
}

const kv_matrix_t* kv_matrix(const kv_value_t* kv)
{
  return (const kv_matrix_t*)kv->data.pointer;
}


void kv_value_print(const  kv_value_t* kv)
{
  switch (kv->type)
  {
  case VALUE_STRING:
    printf("string: %s\n", (const char*)kv->data.pointer);
    break;
  case VALUE_DOUBLE:
    printf("double: %f\n", kv->data.dbl_value);
    break;
  case VALUE_INTEGER:
    printf("int: %d\n", kv->data.int_value);
    break;
  case VALUE_VECTOR:
    printf("vector: ");
    kv_vector_print((const kv_vector_t*)kv->data.pointer);
    printf("\n");    
    break;
  case VALUE_MATRIX:
    printf("matrix:\n");
    kv_matrix_print((const kv_matrix_t*)kv->data.pointer);
    break;
  default:
    break;
  }
}
