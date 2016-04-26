#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "tinystr.h"

#define tinyStrToCNoConst(tinyStr) ((char *)(tinyStr).array)

////////////////////////////////////////////////////////////////////////////////
// Private prototypes.
////////////////////////////////////////////////////////////////////////////////

unsigned tinyStrBitScanReverse(uint64_t x);

////////////////////////////////////////////////////////////////////////////////
// Public functions.
////////////////////////////////////////////////////////////////////////////////

int tinyStrCmp(TinyStr str1, TinyStr str2) {
	assert(tinyStrIsValid(str1));
	assert(tinyStrIsValid(str2));

	uint64_t hash1=tinyStrPerfectHashOrderPreserving(str1);
	uint64_t hash2=tinyStrPerfectHashOrderPreserving(str2);

	int64_t diff=hash1-hash2;
	int result=(diff==0 ? 0 : (diff<0 ? -1 : 1));

	assert(result==strcmp(tinyStrToC(str1), tinyStrToC(str2)));
	return result;
}

bool tinyStrEqual(TinyStr str1, TinyStr str2) {
	assert(tinyStrIsValid(str1));
	assert(tinyStrIsValid(str2));

	// Simply compare perfect hashes.
	return tinyStrPerfectHash(str1)==tinyStrPerfectHash(str2);
}

bool tinyStrIsValid(TinyStr str) {
	bool nullFound=false;
	unsigned i;
	for(i=0;i<8;++i)
		if (str.array[i]=='\0')
			// Found a null byte.
			nullFound|=true;
		else if (nullFound)
			// Hit a non-null char after already finding a null.
			return false;
	return nullFound; // We require at least one null terminator.
}

TinyStr tinyStrFromC(const char *cstr) {
	// Create empty string.
	TinyStr tinyStr=tinyStrNew();

	// Copy string.
	strncpy(tinyStrToCNoConst(tinyStr), cstr, 7);

	assert(tinyStrIsValid(tinyStr));
	return tinyStr;
}

unsigned tinyStrLen(TinyStr str) {
	assert(tinyStrIsValid(str));

	// Special case for empty string.
	if (str.integer==0)
		return 0;

	// Otherwise find first non-zero bit (which will be in the first non-zero byte), and find which byte it is in.
	// FIXME: Assumes little-endian.
	unsigned msb=tinyStrBitScanReverse(str.integer);
	return msb/8+1;
}

TinyStr tinyStrNew(void) {
	// Create string of all null bytes.
	TinyStr str={.integer=0};
	assert(tinyStrIsValid(str));
	return str;
}

uint64_t tinyStrPerfectHash(TinyStr str) {
	assert(tinyStrIsValid(str));
	return str.integer;
}

uint64_t tinyStrPerfectHashOrderPreserving(TinyStr str) {
	assert(tinyStrIsValid(str));
	// FIXME: Assumes little-endian.
	return __bswap_64(str.integer);
}

TinyStr tinyStrPrintf(const char *format, ...) {
	assert(format!=NULL);

	va_list ap;
	va_start(ap, format);
	TinyStr str=tinyStrVPrintf(format, ap);
	va_end(ap);

	return str;
}

TinyStr tinyStrSub(TinyStr str, unsigned offset, unsigned length) {
	assert(tinyStrIsValid(str));

	// Trim first offset number of chars.
	// FIXME: Assumes little-endian.
	str.integer>>=offset*8;
	assert(tinyStrIsValid(str));

	// Truncate to length.
	str=tinyStrTruncate(str, length);

	return str;
}

TinyStr tinyStrTruncate(TinyStr str, unsigned length) {
	assert(tinyStrIsValid(str));

	// Restrict length to maximum of 7.
	if (length>7)
		length=7;

	// Mask out last length positions with 0 bits.
	// FIXME: Assumes little-endian.
	static const uint64_t allOnes=~((uint64_t)0);
	const uint64_t mask=(allOnes >> ((8-length)*8));
	str.integer&=mask;

	assert(tinyStrIsValid(str));
	return str;
}

TinyStr tinyStrVPrintf(const char *format, va_list ap) {
	assert(format!=NULL);

	TinyStr str=tinyStrNew();
	vsnprintf(tinyStrToCNoConst(str), 8, format, ap);
	return str;
}

////////////////////////////////////////////////////////////////////////////////
// Private functions.
////////////////////////////////////////////////////////////////////////////////

static const unsigned tinyStrBitScanReverseIndex64[64]={
    0, 47,  1, 56, 48, 27,  2, 60,
   57, 49, 41, 37, 28, 16,  3, 61,
   54, 58, 35, 52, 50, 42, 21, 44,
   38, 32, 29, 23, 17, 11,  4, 62,
   46, 55, 26, 59, 40, 36, 15, 53,
   34, 51, 20, 43, 31, 22, 10, 45,
   25, 39, 14, 33, 19, 30,  9, 24,
   13, 18,  8, 12,  7,  6,  5, 63
};

unsigned tinyStrBitScanReverse(uint64_t x) {
	assert(x!=0);

	const uint64_t debruijn64=0x03f79d71b4cb0a89;

	x|=x>>1;
	x|=x>>2;
	x|=x>>4;
	x|=x>>8;
	x|=x>>16;
	x|=x>>32;

	return tinyStrBitScanReverseIndex64[(x*debruijn64)>>58];
}

