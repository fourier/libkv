## Simple library for parsing MATLAB/Octave-like matrix input
### Syntax
An input file consists of a set of assignments with MATLAB/Octave-like syntax.
Every assignment should ends with semicolon ';'. The r-values (types) are the following:
* integers: ```a = 5;```
* floats: ```pi = 3.15;```
* strings (surrounded with '"'): ```message="hello"```
* arrays of integers or floats: ```vec = [1,2,3];```
* matrix of integers or floats:
```MATLAB
mtx = [1, 2, 3;
4, 5, -1.5;
0, -1.2, 4];
```


