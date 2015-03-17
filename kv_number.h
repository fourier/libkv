/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
#ifndef KV_NUMBER_H
#define KV_NUMBER_H

typedef struct
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
