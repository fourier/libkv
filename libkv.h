/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
#ifndef LIBKV_H
#define LIBKV_H

#include "kv.h"
#include "kv_table.h"
#include "kv_number.h"
#include "kv_vector.h"
#include "kv_matrix.h"

#include <stdio.h>

struct kv_table_t* libkv_parse_file(FILE* file);
struct kv_table_t* libkv_parse_string(const char* string);

#endif /* LIBKV_H */
