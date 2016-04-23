#ifndef TINYSTR_H
#define TINYSTR_H

#include <stdbool.h>
#include <stdint.h>

#define tinyStrToC(tinyStr) ((const char *)(tinyStr).array)

typedef union TinyStr {
  uint64_t integer;
  char array[8];
} TinyStr;

bool tinyStrIsValid(TinyStr str);

TinyStr tinyStrFromC(const char *cstr);

TinyStr tinyStrNew(void); // Empty string.

#endif
