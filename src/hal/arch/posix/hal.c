#include <stdarg.h>
#include <stdio.h>

#include <px4/hal/hal.h>

void loginfo(const char *fmt, ...)
{
	va_list argptr;
	va_start(argptr, fmt);
	vfprintf(stdout, fmt, argptr);
	va_end(argptr);
}
