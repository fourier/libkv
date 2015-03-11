/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
#include "kv.h"

#include <stdio.h>

void kv_init_int(struct kv_value_t* kv, int value)
{
  kv->type = VALUE_INTEGER;
  kv->data.int_value = value;
}

void kv_init_double(struct kv_value_t* kv, double value)
{
  kv->type = VALUE_DOUBLE;
  kv->data.dbl_value = value;
}

void kv_init_string(struct kv_value_t* kv, const char* string)
{
  kv->type = VALUE_STRING;
  kv->data.pointer = (void*)string;
}

value_type kv_type(const struct kv_value_t* kv)
{
  return kv->type;
}

int kv_int(const struct kv_value_t* kv)
{
  return kv->data.int_value;
}

double kv_double(const struct kv_value_t* kv)
{
  return kv->data.dbl_value;
}

const char* kv_string(const struct kv_value_t* kv)
{
  return (const char*)kv->data.pointer;
}


void kv_value_print(const struct kv_value_t* kv)
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
  case VALUE_INT_VECTOR:
    break;
  case VALUE_DOUBLE_VECTOR:
    break;
  case VALUE_INT_MATRIX:
    break;
  case VALUE_DOUBLE_MATRIX:
    break;
  default:
    break;
  }
}
