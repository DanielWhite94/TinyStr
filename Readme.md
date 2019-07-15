### Overview

TinyStr is a C library for efficiently dealing with short strings (7 characters at most).

Internally strings are stored as a union between a character array with 8 elements and a 64-bit integer, using bitwise operations on the latter where possible for speed. They are always null terminated and additionally they have the property that any bytes beyond the first null byte, are also null bytes, giving each string a unique representation.

### Documentation

See [here](https://danielwhite94.github.io/TinyStr/tinystr_8h.html).

### Compiling and Using

See the included `Makefile` and `example.c` source file.

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
