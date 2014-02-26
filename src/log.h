#ifndef __LOG_H__
#define __LOG_H__

void (*logging)(unsigned int level, const char* msg, const char* file, const char* func, int line);
void init_logger(const char *logger, unsigned int level);

#define logging(level,msg)	(*logging)(level, msg, __FILE__, __FUNCTION__, __LINE__)

#endif
