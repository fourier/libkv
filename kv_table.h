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
