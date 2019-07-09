#ifndef TINYSTR_H
#define TINYSTR_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#define tinyStrToC(tinyStr) ((const char *)(tinyStr).array)

typedef union {
  uint64_t integer;
  char array[8];
} TinyStr;

TinyStr tinyStrCat(TinyStr str1, TinyStr str2);

int tinyStrCmp(TinyStr str1, TinyStr str2);

bool tinyStrEqual(TinyStr str1, TinyStr str2);

bool tinyStrIsValid(TinyStr str);

TinyStr tinyStrFromC(const char *cstr);

unsigned tinyStrLen(TinyStr str);

TinyStr tinyStrNew(void); // Empty string.

uint64_t tinyStrPerfectHash(TinyStr str); // Returns a unique 64 bit integer for each valid string.
uint64_t tinyStrPerfectHashOrderPreserving(TinyStr str); // Same as the above but if a<b (asciibetically) then f(a)<f(b), for all valid strings a and b.

TinyStr tinyStrPrintf(const char *format, ...);

TinyStr tinyStrSub(TinyStr str, unsigned offset, unsigned length);

TinyStr tinyStrTruncate(TinyStr str, unsigned length);

TinyStr tinyStrVPrintf(const char *format, va_list ap);

#endif
