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

#ifndef KV_MATRIX_H
#define KV_MATRIX_H

struct kv_vector_t;

typedef struct kv_matrix_t
{
  int rows;
  int cols;
  int is_int;
  int reserved;
  void* data;
} kv_matrix_t;

/**
 * constructors
 */
void kv_matrix_init(kv_matrix_t* mtx);
/**
 * construct matrix with the 1st row.
 * Transferring ownership of the vector's contents
 */
kv_matrix_t* kv_matrix_alloc(const struct kv_vector_t* vec);
/**
 * destructor
 */
void kv_matrix_fini(kv_matrix_t* mtx);

/**
 * Append matrix with a new row.
 * Transferring ownership of the vector's contents
 * returns 0 if ok
 */
int kv_matrix_add_row(kv_matrix_t* mtx, const struct kv_vector_t* vec);
void kv_matrix_print(const kv_matrix_t* mtx);

#endif /* KV_MATRIX_H */
