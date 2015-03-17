/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
#ifndef KV_H
#define KV_H

#include "kv_vector.h"

typedef enum {
  VALUE_STRING,
  VALUE_DOUBLE,
  VALUE_INTEGER,
  VALUE_VECTOR,
  VALUE_MATRIX,
} value_type;

struct kv_value_t {
  value_type type;
  union {
    double dbl_value;
    int int_value;
    void* pointer;
  } data;
};

/**
 * initializers
 */
void kv_init_int(struct kv_value_t* kv, int value);
void kv_init_double(struct kv_value_t* kv, double value);
void kv_init_string(struct kv_value_t* kv, const char* value);
void kv_init_vector(struct kv_value_t* kv, const kv_vector* value);

/**
 * getters
 */
value_type kv_type(const struct kv_value_t* kv);

  
int kv_int(const struct kv_value_t* kv);
double kv_double(const struct kv_value_t* kv);
const char* kv_string(const struct kv_value_t* kv);

/**
 * Auxulary methods
 */
void kv_value_print(const struct kv_value_t* kv);
  

#endif /* KV_H */
