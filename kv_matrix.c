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

static void kv_matrix_init_with_row(kv_matrix_t* mtx, const struct kv_vector_t* vec)
{
  assert(mtx);
  assert(vec);
  kv_matrix_init(mtx);
  mtx->rows = 1;
  mtx->cols = vec->size;
  mtx->reserved = 1;
  mtx->is_int = vec->is_int;
  if (vec->is_int)              /* integer matrix */
  {
    int** ptr = malloc(sizeof(int*));
    ptr[0] = (int*)vec->data;
    mtx->data = ptr;
  }
  else
  {
    double** ptr = malloc(sizeof(double*));
    ptr[0] = (double*)vec->data;
    mtx->data = ptr;
  }
}

kv_matrix_t* kv_matrix_alloc(const struct kv_vector_t* vec)
{
  kv_matrix_t* mtx = malloc(sizeof(kv_matrix_t));
  assert(mtx);
  kv_matrix_init_with_row(mtx, vec);
  printf("matrix with row of size %d created\n", mtx->cols);
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

static void kv_matrix_try_convert_double(kv_matrix_t* mtx)
{
  assert(mtx);
  if (mtx->is_int)
  {
    double **ptr;
    int i;
    ptr = (double**)malloc(sizeof(double*)*mtx->reserved);
    assert(ptr);
    for (i = 0; i < mtx->rows; ++ i)
    {
      double* row;
      int* oldrow = ((int**)mtx->data)[i];
      int j;
      row = (double*)malloc(sizeof(double)*mtx->cols);
      assert(row);
      for (j = 0; j < mtx->cols; ++ j)
        row[j] = (double)oldrow[j];
      ptr[i] = row;
      free(oldrow);
    }
    free(mtx->data);
    mtx->data = ptr;
    mtx->is_int = 0;
  }
}

static int kv_matrix_new_size(int old_size)
{
  int size = 0;
  if (old_size == 1)
    size = 4;
  else if (old_size < 10)
    size = old_size*2;
  else
    size = (int)(old_size*1.25) + 1;
  return size;
}

static void kv_matrix_grow(kv_matrix_t* mtx)
{
  assert(mtx);
  mtx->reserved = kv_matrix_new_size(mtx->reserved);
  mtx->data = realloc(mtx->data,
                      mtx->reserved*(mtx->is_int ? sizeof(int*) : sizeof(double*)));
  assert(mtx->data);
}

static void kv_matrix_grow_double(kv_matrix_t* mtx)
{
  assert(mtx);
  mtx->reserved = kv_matrix_new_size(mtx->reserved);
  kv_matrix_try_convert_double(mtx);
}

static void kv_matrix_simple_add_row(kv_matrix_t* mtx, const struct kv_vector_t* vec)
{
  if (mtx->is_int)
  {
    ((int**)mtx->data)[mtx->rows++] = (int*)vec->data;
  }
  else if (!mtx->is_int && !vec->is_int)
  {
    ((double**)mtx->data)[mtx->rows++] = (double*)vec->data;
  }
  else                          /* matrix is of double, vector of int */
  {
    double* row = (double*)malloc(sizeof(double)*vec->size);
    int i;
    for (i = 0; i < vec->size; ++ i)
      row[i] = vec->is_int ? (double)((int*)vec->data)[i] : ((double*)vec->data)[i];
    ((double**)mtx->data)[mtx->rows++] = row;
    /* since transferring ownership, clear the vector data */
    free(vec->data);
  }
}

int kv_matrix_add_row(kv_matrix_t* mtx, const struct kv_vector_t* vec)
{
  assert(mtx);
  assert(vec);
  if (mtx->cols != vec->size)
    return -1;
  if (mtx->rows == 0)           /* new matrix */
  {
    kv_matrix_init_with_row(mtx, vec);    
  }
  else if (mtx->rows == mtx->reserved) /* need to grow */
  {
    if (mtx->is_int && !vec->is_int) /* need to convert */
      kv_matrix_grow_double(mtx);
    else
      kv_matrix_grow(mtx);
    kv_matrix_simple_add_row(mtx, vec);
  }
  else                          /* normal case */
  {
    if (mtx->is_int && !vec->is_int) /* need to convert */
      kv_matrix_try_convert_double(mtx);
    kv_matrix_simple_add_row(mtx, vec);
  }
  return 0;
}


void kv_matrix_print(const kv_matrix_t* mtx)
{
  if (mtx)
  {
    int i,j;
    for (i = 0; i < mtx->rows; ++ i)
    {
      for (j = 0; j < mtx->cols; ++ j)
        if (mtx->is_int)
          printf("%d ", ((int**)mtx->data)[i][j]);
        else
          printf("%f ", ((double**)mtx->data)[i][j]);
      printf("\n");
    }
  }
}
