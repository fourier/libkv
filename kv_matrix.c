/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* local includes */
#include "kv_matrix.h"

/* system includes */
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

void kv_matrix_init(kv_matrix_t* mtx)
{
  memset(mtx, 0, sizeof(*mtx));
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
}

