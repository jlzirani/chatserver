#include "log.h"
#include <stdio.h>
#include <string.h>
#undef logging

const char *levels[] = {"DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"};
unsigned int triggerLevel = 0;


void loggingVoid(unsigned int level, const char *msg, const char* file, const char* func, int line)
{
}


void loggingNormal(unsigned int level, const char* msg, const char* file, const char* func, int line)
{
	if(level > 4) level = 4;
	if(level >= triggerLevel)
		printf("[%s:%s:%i] - %s: %s\n", file, func, line, levels[level], msg);
}

void loggingColor(unsigned int level, const char* msg, const char* file, const char* func, int line)
{
	if(level > 4) level = 4;
	if(level >= triggerLevel)
		printf("[\x1b[31m%s\x1b[0m:\x1b[32m%s\x1b[0m:\x1b[34m%i\x1b[0m] - %s : %s\n", file, func, line, levels[level], msg);
}

void init_logger(const char *logger, unsigned int level)
{
	logging = &loggingVoid;
	if(logger != 0)
	{
		if(strncmp(logger, "stdout", 6) == 0)
			logging = &loggingNormal;
		if(strncmp(logger, "color", 5) == 0)
			logging = &loggingColor;
	}
}
