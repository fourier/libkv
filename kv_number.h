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
#ifndef KV_NUMBER_H
#define KV_NUMBER_H

typedef struct kv_number_t
{
  int is_int;
  union 
  {
    int i_val;
    double f_val;
  } val;
} kv_number_t;


#define KV_NUMBER_SET_INT(n, i) { (n).is_int = 1; (n).val.i_val = (i); }
#define KV_NUMBER_SET_DBL(n, f) { (n).is_int = 0; (n).val.f_val = (f); }
#define KV_NUMBER_PRINT(n) { if ((n).is_int) printf("%d", (n).val.i_val); else printf("%f", (n).val.f_val); }

#endif /* KV_NUMBER_H */
