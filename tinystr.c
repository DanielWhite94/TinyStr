#include <assert.h>
#include <string.h>

#include "tinystr.h"

bool tinyStrEqual(TinyStr str1, TinyStr str2) {
	assert(tinyStrIsValid(str1));
	assert(tinyStrIsValid(str2));

	// Simply compare perfect hashes.
	return tinyStrMinPerfectHash(str1)==tinyStrMinPerfectHash(str2);
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
	strncpy((char *)tinyStr.array, cstr, 7);

	assert(tinyStrIsValid(tinyStr));
	return tinyStr;
}

TinyStr tinyStrNew(void) {
	// Create string of all null bytes.
	TinyStr str={.integer=0};
	assert(tinyStrIsValid(str));
	return str;
}

uint64_t tinyStrMinPerfectHash(TinyStr str) {
	assert(tinyStrIsValid(str));
	return str.integer;
}

