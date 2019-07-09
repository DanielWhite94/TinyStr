#include <stdio.h>

#include "tinystr.h"

int main(int argc, char **argv) {
	TinyStr hello=tinyStrFromC("Hello ");
	TinyStr world=tinyStrFromC("world!");
	printf("%s%s\n", tinyStrToC(hello), tinyStrToC(world));

	TinyStr cat=tinyStrCat(hello, world);
	printf("%s\n", tinyStrToC(cat));

	TinyStr part=tinyStrSub(cat, 2, 5);
	printf("%s\n", tinyStrToC(part));

	return 0;
}
