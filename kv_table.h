/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
#ifndef KV_TABLE_H
#define KV_TABLE_H

#include "kv.h"

/* forward declaration of the identifiers table */
struct kv_table_t;

/**
 * constructor and destructor
 */
struct kv_table_t* kv_table_alloc();
void kv_table_free(struct kv_table_t* table);

/**
 * getters and setters
 */
const struct kv_value_t* kv_table_get(struct kv_table_t* table, const char* name);
void kv_table_put(struct kv_table_t* table, const char* name, struct kv_value_t* value);

/**
 * auxulary methods
 */
void kv_table_dump(const struct kv_table_t* table);
/**
 * remove identifier from the table without freeing contents.
 * Useful when ownership is already transferred by using kv_table_get
 */
void kv_table_drop(struct kv_table_t* table, const char* name);


#endif /* KV_TABLE_H */
