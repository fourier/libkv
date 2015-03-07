/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
#include "libkv.h"
#include <string.h>
#include <stdlib.h>

/* simple hash table of fixed size */
#define HASH_ELTS 9997

/* key-value bucket */
struct kv_bucket
{ 
  const char* name;
  kv_value_t value;
  struct kv_bucket* next;
};

static struct kv_bucket* hash_table[HASH_ELTS];

/*
 * Hash function for strings, from K&P "The Practice of Programming"
 * chapter 2.9
 */
static long hash_function(int size,const char* str)
{
  /* Constant for hash function from K&P*/
  static const int MULTIPLIER = 31;      /* other can be 37 */

  long h = 0;
  unsigned char* p;
  for ( p = (unsigned char*)str; *p != '\0'; ++p )
    h = MULTIPLIER * h + *p;
  return h % size;
}

const kv_value_t* kv_get(const char* name)
{
  struct kv_bucket* bucket = hash_table[hash_function(HASH_ELTS, name)];
  return bucket ? &bucket->value : 0;
}

void kv_put(const char* name, kv_value_t* value)
{
  long hash_index = hash_function(HASH_ELTS, name);
  struct kv_bucket* bucket = hash_table[hash_index];
  /* find hash collisions */
  if (bucket)
  {
    struct kv_bucket* last = bucket;
    while (bucket && strcmp(name, bucket->name))
    {
      last = bucket;
      bucket = bucket->next;
    }
    if (!bucket)                /* create a new */
    {
      bucket = malloc(sizeof(*bucket));
      bucket->name = strdup(name);
      bucket->next = 0;
      /* member-wise copy */
      bucket->value = *value;
      last->next = bucket;
    }
  }
  else                          /* new element */
  {
    bucket = malloc(sizeof(*bucket));
    bucket->name = strdup(name);
    bucket->next = 0;
    /* member-wise copy */
    bucket->value = *value;
    hash_table[hash_index] = bucket;
  }
  
}

