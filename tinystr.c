#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "tinystr.h"

#define tinyStrToCNoConst(tinyStr) ((char *)(tinyStr).array)

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
