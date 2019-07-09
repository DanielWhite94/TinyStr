### Overview

TinyStr is a C library for efficiently dealing with short strings (7 characters at most).

Internally strings are stored as a union between a character array with 8 elements and a 64-bit integer, using bitwise operations on the latter where possible for speed. They are always null terminated and additionally they have the property that any bytes beyond the first null byte, are also null bytes, giving each string a unique representation.

### Compiling and Using

See the included `Makefile` and `example.c` source file.

### Operations

| Operation | Prototype | Notes |
|-----------|-----------|--------------|
| Create New | TinyStr tinyStrNew(void) | Returns empty string |
| Create From C-string | TinyStr tinyStrFromC(const char *cstr) | Only at most the first 7 characters are copied. |
| Get Length | unsigned tinyStrLen(TinyStr str) | |
| Test Equality | bool tinyStrEqual(TinyStr str1, TinyStr str2) | |
| Compare | int tinyStrCmp(TinyStr str1, TinyStr str2) | Acts as strcmp |
| Hash | uint64_t tinyStrPerfectHash(TinyStr str) | Returns a unique 64 bit integer for each valid string. |
| Hash (order perserving) | uint64_t tinyStrPerfectHashOrderPreserving(TinyStr str) | Same as the above but if a<b (asciibetically) then f(a)<f(b), for all valid strings a and b. |
| Sub-string | TinyStr tinyStrSub(TinyStr str, unsigned offset, unsigned length) | |
| Concatenate | TinyStr tinyStrCat(TinyStr str1, TinyStr str2) |  |
| Truncate | TinyStr tinyStrTruncate(TinyStr str, unsigned length) |  |
| printf | TinyStr tinyStrPrintf(const char *format, ...) | See vprintf |
| vprintf | TinyStr tinyStrVPrintf(const char *format, va_list ap) | Uses stdlib vsnprintf so acts identically. |
| Check Validity | bool tinyStrIsValid(TinyStr str) | As all unused bytes have to be null only a subset of all possible states are valid. |

Note: almost all functions are constant time, such as tinyStrLen, tinyStrCat and tinyStrCmp.

There is also a macro - tinyStrToC - which gives a safe way to use a TinyStr as a const c-string.

### Terms of use

TinyStr is free, and distributed under the **GNU General Public License**
(GPL). Essentially, this means that you are free to do almost exactly
what you want with the program, including distributing it among your
friends, making it available for download from your web site, selling
it (either by itself or as part of some bigger software package), or
using it as the starting point for a software project of your own.

The only real limitation is that whenever you distribute TinyStr in
some way, you must always include the full source code, or a pointer
to where the source code can be found. If you make any changes to the
source code, these changes must also be made available under the GPL.

For full details, read the copy of the GPL found in the file named
*Copying.txt*.
