#ifndef __LOG_H__
#define __LOG_H__

#include <stdarg.h>

void init_logger(const char *logger, unsigned int level);

void loggin( const char* file, const char *func, int line, int level,  const char *msg, ... );

#define logging( level,  ... )	loggin(__FILE__, __FUNCTION__, __LINE__, level,  __VA_ARGS__ ) 

#endif
