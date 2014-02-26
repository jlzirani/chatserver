#include "log.h"
#include <stdio.h>
#include <string.h>
#undef logging

const char *levels[] = {"DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"};
unsigned int triggerLevel = 0;

void loggingVoid(const char* file, const char* func, int line, unsigned int level, const char *msg, va_list vargs)
{
}

void loggingNormal(const char* file, const char* func, int line, unsigned int level, const char *msg, va_list vargs)
{
	if(level > 4) level = 4;
	if(level >= triggerLevel)
	{
		printf("[%s:%s:%i] - %s: ", file, func, line, levels[level]);
		vprintf(msg, vargs);
		printf("\n");
	}
}

void loggingColor(const char* file, const char* func, int line, unsigned int level, const char *msg, va_list vargs)
{
	if(level > 4) level = 4;
	if(level >= triggerLevel)
	{
		printf("[\x1b[31m%s\x1b[0m:\x1b[32m%s\x1b[0m:\x1b[34m%i\x1b[0m] - %s : ", file, func, line, levels[level]);
		vprintf(msg, vargs);
		printf("\n");
	}
}


void (*logging)(const char* file, const char* func, int line, unsigned int level, const char* msg, va_list varg) = loggingVoid;

void loggin( const char* file, const char *func, int line, int level, const char *msg, ...) 
{
	va_list arg;
	va_start(arg, msg);
	(*logging)(file, func, line, level, msg, arg);
	va_end(arg);
}


void init_logger(const char *logger, unsigned int level)
{
	if(logger != 0)
	{
		if(strncmp(logger, "stdout", 6) == 0)
			logging = &loggingNormal;
		if(strncmp(logger, "color", 5) == 0)
			logging = &loggingColor;
	}
}
