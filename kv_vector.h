/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
#ifndef KV_VECTOR_H
#define KV_VECTOR_H

#include "kv_number.h"

typedef struct
{
  int size;
  int reserved;
  int is_int;
  void* data;
} kv_vector_t;

/**
 * constructors
 */
kv_vector_t* kv_vector_alloc_one_elt(const kv_number_t* number);
kv_vector_t* kv_vector_alloc_two_elts(const kv_number_t* number1,
                                    const kv_number_t* number2);

/**
 * destructor
 */
void kv_vector_fini(kv_vector_t* vec);

/**
 * push the number to the back and convert array if necessary
 */
void kv_vector_push_back(kv_vector_t* vec, const kv_number_t* number);

/**
 * dump vector contents
 */
void kv_vector_print(const kv_vector_t* vec);

#endif /* KV_VECTOR_H */
