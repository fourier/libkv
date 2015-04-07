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
#ifndef KV_VECTOR_H
#define KV_VECTOR_H

struct kv_number_t;

typedef struct kv_vector_t
{
  int size;
  int reserved;
  int is_int;
  void* data;
} kv_vector_t;

/**
 * constructors
 */
kv_vector_t* kv_vector_alloc_one_elt(const struct kv_number_t* number);
kv_vector_t* kv_vector_alloc_two_elts(const struct kv_number_t* number1,
                                    const struct kv_number_t* number2);

/**
 * destructor
 */
void kv_vector_fini(kv_vector_t* vec);

/**
 * push the number to the back and convert array if necessary
 */
void kv_vector_push_back(kv_vector_t* vec, const struct kv_number_t* number);

/**
 * dump vector contents
 */
void kv_vector_print(const kv_vector_t* vec);

#endif /* KV_VECTOR_H */
