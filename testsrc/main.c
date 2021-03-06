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

#include <stdio.h>
#include <stdlib.h>
#include "libkv.h"

int main(int argc, const char* argv[])
{
  FILE* file;
  struct kv_table_t* table;
  ++argv, --argc;  /* skip over program name */
  if ( argc > 0 )
    file  = fopen( argv[0], "r" );
  else
    file = stdin;
  table = libkv_parse_file(file);
  if (table)
  {
    kv_table_dump(table);
  }
  kv_table_free(table);
  return 0;
}
