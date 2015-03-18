/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
#ifndef KV_MATRIX_H
#define KV_MATRIX_H

struct kv_vector_t;

typedef struct kv_matrix_t
{
  int rows;
  int cols;
  int is_int;
  int reserved;
  void* data;
} kv_matrix_t;

/**
 * constructors
 */
void kv_matrix_init(kv_matrix_t* mtx);
/**
 * construct matrix with the 1st row.
 * Transferring ownership of the vector's contents
 */
kv_matrix_t* kv_matrix_alloc(const struct kv_vector_t* vec);
/**
 * destructor
 */
void kv_matrix_fini(kv_matrix_t* mtx);

/**
 * Append matrix with a new row.
 * Transferring ownership of the vector's contents
 * returns 0 if ok
 */
int kv_matrix_add_row(kv_matrix_t* mtx, const struct kv_vector_t* vec);
void kv_matrix_print(const kv_matrix_t* mtx);

#endif /* KV_MATRIX_H */
