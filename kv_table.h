/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
#ifndef KV_TABLE_H
#define KV_TABLE_H

#include "kv.h"

const struct kv_value_t* kv_table_get(const char* name);
void kv_table_put(const char* name, struct kv_value_t* value);
void kv_table_dump();


#endif /* KV_TABLE_H */
