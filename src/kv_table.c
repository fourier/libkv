/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 Copyright (C) 2015 Alexey Veretennikov (alexey dot veretennikov at gmail.com)
 
 This file is part of Libkv.

 Libkv is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published
 by the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Libkv is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with Libkv.  If not, see <http://www.gnu.org/licenses/>.
*/

/* local includes */
#include "kv_table.h"

/* system includes */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* simple hash table of fixed size */
#define HASH_ELTS 9997

/* key-value bucket */
typedef struct kv_bucket_t
{ 
  char* name;
  struct kv_value_t value;
  struct kv_bucket_t* next;
} kv_bucket_t;

/* table containing fixed size array of buckets */
typedef struct kv_table_t
{
  kv_bucket_t** buckets;
  int size;
} kv_table_t;


/*
 * Hash function for strings, from K&P "The Practice of Programming"
 * chapter 2.9
 */
static long hash_function(int size,const char* str)
{
  /* Constant for hash function from K&P */
  static const int MULTIPLIER = 31;      /* other can be 37 */

  long h = 0;
  unsigned char* p;
  for ( p = (unsigned char*)str; *p != '\0'; ++p )
    h = MULTIPLIER * h + *p;
  return h % size;
}

kv_table_t* kv_table_alloc()
{
  kv_table_t* table = malloc(sizeof(*table));
  table->size = HASH_ELTS;
  table->buckets = malloc(sizeof(kv_bucket_t*)*table->size);
  memset(table->buckets, 0, sizeof(kv_bucket_t*)*table->size);
  return table;
}

static void kv_bucket_free(kv_bucket_t* bucket)
{
  if (bucket)
  {
    free(bucket->name);
    free(bucket);
  }
}

static void kv_bucket_deep_free(kv_bucket_t* bucket)
{
  if (bucket)
  {
    free(bucket->name);
    kv_fini(&bucket->value);
    free(bucket);
  }
}

void kv_table_free(struct kv_table_t* table)
{
  if (table)
  {
    int i;
    for (i = 0; i < table->size; ++ i)
      if (table->buckets[i])
      {
        kv_bucket_t* bucket = table->buckets[i];
        kv_bucket_t* last = bucket;
        while (bucket)
        {
          last = bucket;
          bucket = bucket->next;
          kv_bucket_deep_free(last);
        }
      }
    free(table->buckets);
    free(table);
  }
}


const struct kv_value_t* kv_table_get(kv_table_t* table, const char* name)
{
  kv_bucket_t* bucket = table->buckets[hash_function(table->size, name)];
  while (bucket && strcmp(name, bucket->name))
  {
    bucket = bucket->next;
  }
  
  return bucket ? &bucket->value : 0;
}

void kv_table_drop(struct kv_table_t* table, const char* name)
{
  kv_bucket_t* bucket = table->buckets[hash_function(table->size, name)];
  kv_bucket_t* prev = bucket;
  while (bucket && strcmp(name, bucket->name))
  {
    prev = bucket;
    bucket = bucket->next;
  }
  if (bucket)
  {
    kv_bucket_t* next = bucket->next;
    if (prev == bucket)         /* if it was the 1st in row */
    {
      table->buckets[hash_function(table->size, name)] = next;
    }
    else
    {
      prev->next = next;
    }
    kv_bucket_free(bucket);
  }
  
  assert(table);
  assert(name);
}

void kv_table_put(kv_table_t* table, const char* name, struct kv_value_t* value)
{
  long hash_index = hash_function(table->size, name);
  kv_bucket_t* bucket = table->buckets[hash_index];
  /* find hash collisions */
  if (bucket)
  {
    kv_bucket_t* last = bucket;
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
    bucket->name = malloc(strlen(name)+1);
    strcpy(bucket->name, name);
    bucket->next = 0;
    /* member-wise copy */
    bucket->value = *value;
    table->buckets[hash_index] = bucket;
  }
  
}


static void kv_table_dump_bucket(kv_bucket_t* bucket)
{
  printf("Identifier: %s\n", bucket->name);
  kv_value_print(&bucket->value);
}

void kv_table_dump(const kv_table_t* table)
{
  int i = 0;
  for (; i < table->size; ++ i)
  {
    kv_bucket_t* bucket;
    if ((bucket = table->buckets[i]))
    {
      while (bucket)
      {
        kv_table_dump_bucket(bucket);
        bucket = bucket->next;
      }
    }
  }
}
