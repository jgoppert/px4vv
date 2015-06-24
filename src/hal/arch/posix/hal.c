#include <hal/hal.h>

#include <stdarg.h>
#include <stdio.h>

void loginfo(const char *fmt, ...)
{
	va_list argptr;
	va_start(argptr, fmt);
	vfprintf(stdout, fmt, argptr);
	va_end(argptr);
}
