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
} kv_vector;

/**
 * constructors
 */
void kv_vector_init(kv_vector* vec);
void kv_vector_init_one_elt(kv_vector* vec, const kv_number* number);
void kv_vector_init_two_elts(kv_vector* vec,
                             const kv_number* number1,
                             const kv_number* number2);
kv_vector* kv_vector_alloc_one_elt(const kv_number* number);
kv_vector* kv_vector_alloc_two_elts(const kv_number* number1,
                                    const kv_number* number2);

/**
 * destructor
 */
void kv_vector_fini(kv_vector* vec);

/**
 * push the number to the back and convert array if necessary
 */
void kv_vector_push_back(kv_vector* vec, const kv_number* number);

/**
 * dump vector contents
 */
void kv_vector_print(const kv_vector* vec);

#endif /* KV_VECTOR_H */
