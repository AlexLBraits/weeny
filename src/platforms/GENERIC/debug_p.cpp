#include "debug_p.h"
#include <cstdio>

void Debug_p::log(const char* message)
{
	fprintf(stderr, message);
}
