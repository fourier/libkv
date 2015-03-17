/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* local includes */
#include "kv_matrix.h"
#include "kv_vector.h"

/* system includes */
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

void kv_matrix_init(kv_matrix_t* mtx)
{
  memset(mtx, 0, sizeof(*mtx));
}

kv_matrix_t* kv_matrix_alloc(const struct kv_vector_t* vec)
{
  kv_matrix_t* mtx = malloc(sizeof(kv_matrix_t));
  assert(mtx);
  kv_matrix_init(mtx);
  mtx->rows = 1;
  mtx->cols = vec->size;
  return mtx;
}

void kv_matrix_fini(kv_matrix_t* mtx)
{
  int i;
  int** intptr = (int**)mtx->data;
  double** dblptr = (double**)mtx->data;

  if (mtx->is_int)
    for (i = 0; i < mtx->rows; ++ i)
      free(intptr[i]);
  else
    for (i = 0; i < mtx->rows; ++ i)
      free(dblptr[i]);
  free(mtx->data);
  kv_matrix_init(mtx);
}
#if 0
static void kv_vector_try_convert_double(kv_vector_t* vec)
{
  assert(vec);
  if (vec->is_int)
  {
    double *ptr;
    int i;
    ptr = (double*)malloc(sizeof(double)*vec->reserved);
    assert(ptr);
    for (i = 0; i < vec->size; ++ i)
      ptr[i] = (double)(*((int*)vec->data+i));
    free(vec->data);
    vec->data = ptr;
    vec->is_int = 0;
  }
}


static void kv_vector_grow(kv_vector_t* vec)
{
  assert(vec);
  vec->reserved = kv_vector_new_size(vec->reserved);
  vec->data = realloc(vec->data,
                      vec->reserved*(vec->is_int ? sizeof(int) : sizeof(double)));
  assert(vec->data);
}

static void kv_vector_grow_double(kv_vector_t* vec)
{
  assert(vec);
  vec->reserved = kv_vector_new_size(vec->reserved);
  kv_vector_try_convert_double(vec);
}
#endif

void kv_matrix_add_row(kv_matrix_t* mtx, const struct kv_vector_t* vec)
{
  assert(mtx);
  assert(vec);
  printf("row added\n");
  
  mtx->rows++;
}


void kv_matrix_print(const kv_matrix_t* mtx)
{
  if (mtx)
  {
    printf("matrix dump");
  }
}
