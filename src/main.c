#include "log.h"
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include "socket.h"
#include "chatroom.h"

#define dieIfFail(cond, level) if(cond) { logging(level, #cond); exit(1); }

void incParam(int *argc, char **argv[])
{
	--*argc;
	++*argv;
}

void parseParameter(int argc, char *argv[])
{
	const char *logger[] = {0, "stdout", "color"};
	int logger_choice = 0;
	while(argc > 0)
	{
		if(strncmp(argv[0], "-d", 2) == 0)
		{
			logger_choice = 1;
			if(argc > 1)
			{
				int inc=0;
				if(strncmp(argv[1], "color", 5) ==0)
				{
					inc=1;
					logger_choice = 2;	
				}
				if(strncmp(argv[1], "stdout", 6) ==0)
					inc=1;
				if(inc)
					incParam(&argc, &argv);
			}
		}
		incParam(&argc, &argv);
	}
	init_logger(logger[logger_choice], 0);
}

int main(int argc, char *argv[])
{
	sSocket server;
	parseParameter( argc - 1, argv +1);
	logging(1, "Creating socket");
	server = createSocket( 4000 );

	dieIfFail( !socketIsValid(server) , 4);

	logging(1, "Binding socket");
	dieIfFail( socketBind(&server) < 0, 4);

	logging(0, "binding addresse %s:%i", server.addr, server.port);

	logging(1, "Listen to the socket");
	socketListen(server, 10);

	loop(server, 25);

	
	return 0;
}
