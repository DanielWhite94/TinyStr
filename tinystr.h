#ifndef TINYSTR_H
#define TINYSTR_H

#include <stdbool.h>
#include <stdint.h>

#define tinyStrToC(tinyStr) ((const char *)(tinyStr).array)

typedef union TinyStr {
  uint64_t integer;
  char array[8];
} TinyStr;

bool tinyStrEqual(TinyStr str1, TinyStr str2);

bool tinyStrIsValid(TinyStr str);

TinyStr tinyStrFromC(const char *cstr);

TinyStr tinyStrNew(void); // Empty string.

uint64_t tinyStrPerfectHash(TinyStr str); // Returns a unique 64 bit integer for each valid string.

TinyStr tinyStrSub(TinyStr str, unsigned offset, unsigned length);

TinyStr tinyStrTruncate(TinyStr str, unsigned length);

#endif
