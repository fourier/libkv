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
