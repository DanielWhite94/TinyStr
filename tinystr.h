/** @file tinystr.h */

/*! \mainpage TinyStr
 *
 * See tinystr.h
 *
 */

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

/**
* Append str2 to the end of str1 and return the reult.
* @param str1 first string
* @param str2 second string
* @return combined string
*/
TinyStr tinyStrCat(TinyStr str1, TinyStr str2);

int tinyStrCmp(TinyStr str1, TinyStr str2);

/**
* Compare two TinyStr objects for equality.
* @param str1 first string to compare
* @param str2 second string to compare
* @return true if equal, false otherwise
*/
bool tinyStrEqual(TinyStr str1, TinyStr str2);

/**
* Check if the given TinyStr is valid, i.e. has all unused bytes set to 0.
* @param str string to inspect
* @return true if valid, false otherwise
*/
bool tinyStrIsValid(TinyStr str);

/**
* Create a TinyStr from a standard C character array.
* @param cstr Null-terminated C-string to use as input
* @return newly created TinyStr
*/
TinyStr tinyStrFromC(const char *cstr);

/**
* Find the length of the given TinyStr.
* @param str string to find length of
* @return length of the given string
*/
unsigned tinyStrLen(TinyStr str);

/**
* Create a new TinyStr with length 0.
* @return newly created TinyStr
*/
TinyStr tinyStrNew(void); // Empty string.

/**
* Calculate a fast and unique 64 bit hash value for the given TinyStr.
* @param str string to calculate hash for
* @return hash value
*/
uint64_t tinyStrPerfectHash(TinyStr str); // Returns a unique 64 bit integer for each valid string.

/**
* Calculate a unque 64 bit hash for the given TinyStr which is order-preserving, alphabetically/asciibetically speaking. This is generally slightly slower than tinyStrPerfectHash() so is the order-preserving property is not required, use that instead.
* @param str string to calculate hash for
* @return hash value
*/
uint64_t tinyStrPerfectHashOrderPreserving(TinyStr str); // Same as the above but if a<b (asciibetically) then f(a)<f(b), for all valid strings a and b.

/**
* Acts as printf from the standard library, but returns a TinyStr. Uses the current stdlib version of vprintf and so supports the same features.
* @param format printf-style format string
* @return newly created TinyStr
*/
TinyStr tinyStrPrintf(const char *format, ...);

/**
* Extract a sub-string from a TinyStr
* @param str input string
* @param offset offset into the input string to start the sub-string
* @param max length of the sub-string to extract
* @return newly created TinyStr
*/
TinyStr tinyStrSub(TinyStr str, unsigned offset, unsigned length);

/**
* Truncate the given TinyStr by removing characters from the end until the desired length is reached.
* @param str string to truncate
* @return truncated string
*/
TinyStr tinyStrTruncate(TinyStr str, unsigned length);

/**
* Acts as vprintf from the standard library, but returns a TinyStr. Uses the current stdlib version of vprintf and so supports the same features.
* @param format printf-style format string
* @param ap va_list representing arguments
* @return newly created TinyStr
*/
TinyStr tinyStrVPrintf(const char *format, va_list ap);

#endif
