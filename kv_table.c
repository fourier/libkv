/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* local includes */
#include "kv_table.h"

/* system includes */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* simple hash table of fixed size */
#define HASH_ELTS 9997

/* key-value bucket */
struct kv_bucket
{ 
  char* name;
  struct kv_value_t value;
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

const struct kv_value_t* kv_table_get(const char* name)
{
  struct kv_bucket* bucket = hash_table[hash_function(HASH_ELTS, name)];
  return bucket ? &bucket->value : 0;
}

void kv_table_put(const char* name, struct kv_value_t* value)
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
      bucket->name = malloc(strlen(name)+1);
      strcpy(bucket->name, name);
      bucket->next = 0;
      /* member-wise copy */
      bucket->value = *value;
      last->next = bucket;
    }
    else                        /* found with the same name, replace */
    {
      bucket->value = *value;
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


static void kv_table_dump_bucket(struct kv_bucket* bucket)
{
  printf("Identifier: %s\n", bucket->name);
  kv_value_print(&bucket->value);
}

void kv_table_dump()
{
  int i = 0;
  for (; i < HASH_ELTS; ++ i)
  {
    struct kv_bucket* bucket;
    if ((bucket = hash_table[i]))
    {
      while (bucket)
      {
        kv_table_dump_bucket(bucket);
        bucket = bucket->next;
      }
    }
  }
}
