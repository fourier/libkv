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

#ifndef KV_H
#define KV_H

#include "kv_vector.h"
#include "kv_matrix.h"

typedef enum {
  VALUE_STRING,
  VALUE_DOUBLE,
  VALUE_INTEGER,
  VALUE_VECTOR,
  VALUE_MATRIX,
} value_type;

typedef struct kv_value_t {
  value_type type;
  union {
    double dbl_value;
    int int_value;
    void* pointer;
  } data;
} kv_value_t;

/**
 * initializers
 */
void kv_init_int(kv_value_t* kv, int value);
void kv_init_double(kv_value_t* kv, double value);
void kv_init_string(kv_value_t* kv, const char* value);
void kv_init_vector(kv_value_t* kv, const kv_vector_t* value);
void kv_init_matrix(kv_value_t* kv, const kv_matrix_t* value);
/**
 * destructor (doesn't deallocate the struct itself)
 */
void kv_fini(kv_value_t* kv); 

/**
 * getters
 */
value_type kv_type(const kv_value_t* kv);
int kv_int(const kv_value_t* kv);
double kv_double(const kv_value_t* kv);
const char* kv_string(const kv_value_t* kv);
const kv_vector_t* kv_vector(const kv_value_t* kv);
const kv_matrix_t* kv_matrix(const kv_value_t* kv);

/**
 * Auxulary methods
 */
void kv_value_print(const kv_value_t* kv);
  

#endif /* KV_H */
