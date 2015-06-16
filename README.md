[![Build Status](https://travis-ci.org/fourier/libkv.svg?branch=master)](https://travis-ci.org/fourier/libkv)

## Simple library for parsing MATLAB/Octave-like matrix input
### Introduction
The purpose of this library is to provide simple parser for text files with the data specified in key-value format (hence the name *libkv*). The types of values could be ASCII-strings, integers, floating point numbers. It also supports MATLAB/Octave-like syntax for vectors and matricies of integers and doubles, therefore making it convinient to test own numeric-oriented libraries against MATLAB/Octave prototypes.

### Syntax
An input file consists of a set of assignments with MATLAB/Octave-like syntax.
Every assignment should ends with semicolon ';'. The r-values (types) are the following:
* integers: ```a = 5;```
* floats: ```pi = 3.15;```
* strings (surrounded with '"'): ```message="hello"```
* arrays of integers or floats: ```vec = [1;2;3];```
* matrix of integers or floats:
```MATLAB
mtx = [1,    2,    3;
       4,    5, -1.5;
       0, -1.2,    4];
```
Newlines and comments (starting with *#* or *%*) are ignored.

### Usage
Link against the output library **libkv**. See the code example in [main.c](https://github.com/fourier/libkv/blob/master/main.c).

Include the library header:
```c
#include "libkv.h"
```

Parse the file
```c
struct kv_table_t* table = libkv_parse_file(file);
```
or string
```c
struct kv_table_t* table = libkv_parse_string(file);
```
into the key-value table.

Access the values using the ```kv_table_get``` method declared in [kv_table.h](https://github.com/fourier/libkv/blob/master/kv_table.h).
This method returns the pointer to the appropriate ```kv_value_t``` struct (or null if not found). One can operate with this struct using the set of methods declared in [kv.h](https://github.com/fourier/libkv/blob/master/kv.h) or by just accessing fields.

If needed to transfer ownership on values, like strings, vectors and matricies, one can use the ```kv_table_drop``` to get rid of the value in the table. Therefore the when the ```kv_table_free``` method called this values will not be deallocated.

Example:
```c
const char* string = 0;
struct kv_table_t* table = libkv_parse_file(file);
const struct kv_value_t* value = kv_table_get(table, "myvariable");
if (value && kv_type(value) == VALUE_STRING)
{
   string = kv_string(value); /* transferring ownership, now we are responsible
                               * for freeing it later
                               */
   kv_table_drop(table, "myvariable");
}
kv_table_free(table);
```

Deallocate the table using the ```kv_table_free``` method. It will perform *deep* deallocation, therefore copy values or take ownership and drop them from table before deallocating.

### Note on matricies and vectors
The library assumes integers in input until it encounters the first floating-point value. When the library converts the vector/matrix to the double format.

The vector-row or vector-column interpreted by the library equally and represented as ```kv_vector_t```.


