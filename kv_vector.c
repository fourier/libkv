/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
#include "kv_vector.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

static void kv_vector_init(kv_vector_t* vec)
{
  assert(vec);
  memset(vec, 0, sizeof(*vec));
}

static void kv_vector_init_one_elt(kv_vector_t* vec, const kv_number_t* number)
{
  assert(vec);
  kv_vector_init(vec);
  vec->size = 1;
  vec->reserved = 1;
  vec->is_int = number->is_int;
  vec->data = malloc(number->is_int ? sizeof(int) : sizeof(double));
  assert(vec->data);
  if (number->is_int)
    *(int*)vec->data = number->val.i_val;
  else
    *(double*)vec->data = number->val.f_val;    
}

static void kv_vector_init_two_elts(kv_vector_t* vec,
                                    const kv_number_t* number1,
                                    const kv_number_t* number2)
{
  assert(vec);
  kv_vector_init(vec);
  vec->size = 2;
  vec->reserved = 4;
  vec->is_int = number1->is_int && number2->is_int;
  if (vec->is_int)
  {
    int* ptr;
    vec->data = malloc(sizeof(int) * vec->reserved);
    assert(vec->data);
    ptr = (int*)vec->data;
    ptr[0] = number1->val.i_val;
    ptr[1] = number2->val.i_val;
  }
  else
  {
    double* ptr;
    vec->data = malloc(sizeof(double) * vec->reserved);
    assert(vec->data);
    ptr = (double*)vec->data;
    ptr[0] = number1->is_int ? (double) number1->val.i_val : number1->val.f_val;
    ptr[1] = number2->is_int ? (double) number2->val.i_val : number2->val.f_val;
  }
  
}

kv_vector_t* kv_vector_alloc_one_elt(const kv_number_t* number)
{
  kv_vector_t* vec = malloc(sizeof(kv_vector_t));
  assert(vec);
  kv_vector_init_one_elt(vec, number);
  return vec;
}

kv_vector_t* kv_vector_alloc_two_elts(const kv_number_t* number1,
                                    const kv_number_t* number2)
{
  kv_vector_t* vec = malloc(sizeof(kv_vector_t));
  assert(vec);
  kv_vector_init_two_elts(vec, number1, number2);
  return vec;
}



void kv_vector_fini(kv_vector_t* vec)
{
  assert(vec);
  if (vec && vec->size)
  {
    free(vec->data);
    kv_vector_init(vec);
  }
}

static int kv_vector_new_size(int old_size)
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

static void kv_vector_simple_push_back(kv_vector_t* vec, const kv_number_t* number)
{
  if (vec->is_int)            /* add as integer */
  {
    int* ptr = (int*)vec->data;
    ptr[vec->size++] = number->val.i_val;
  }
  else
  {
    double* ptr = (double*)vec->data;
    ptr[vec->size++] = number->is_int ? (double) number->val.i_val : number->val.f_val;
  }
}

void kv_vector_push_back(kv_vector_t* vec, const kv_number_t* number)
{
  assert(vec);
  /* simple case when not yet created array */
  if (vec->size == 0)
  {
    kv_vector_init_one_elt(vec, number);    
  }
  else if (vec->size == vec->reserved) /* exceed, need to extend */
  {
    if (vec->is_int && !number->is_int) /* need to convert */
      kv_vector_grow_double(vec);
    else
      kv_vector_grow(vec);
    kv_vector_simple_push_back(vec, number);
  }
  else                          /* normal case */
  {
    if (vec->is_int && !number->is_int) /* need to convert */
      kv_vector_try_convert_double(vec);
    kv_vector_simple_push_back(vec, number);
  }
}

void kv_vector_print(const kv_vector_t* vec)
{
  int i;
  assert(vec);
  if (vec->is_int)
  {
    for (i = 0; i < vec->size; ++ i)
    {
      int val = *((int*)vec->data + i);
      if (i < vec->size-1)
        printf("%d ", val);
      else
        printf("%d", val);
    }
  }
  else
  {
    for (i = 0; i < vec->size; ++ i)
    {
      double val = *((double*)vec->data + i);
      if (i < vec->size-1)
        printf("%f ", val);
      else
        printf("%f", val);
    }
  }
}
