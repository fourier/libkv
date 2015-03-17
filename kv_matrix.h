/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
#ifndef KV_MATRIX_H
#define KV_MATRIX_H

typedef struct kv_matrix_t
{
  int rows;
  int cols;
  int is_int;
  void* data;
} kv_matrix_t;

void kv_matrix_init(kv_matrix_t* mtx);
void kv_matrix_fini(kv_matrix_t* mtx);

#endif /* KV_MATRIX_H */
