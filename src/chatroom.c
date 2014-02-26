#include "chatroom.h"
#include "log.h"

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define dieIfFail(cond, level) if(cond) { logging(level, "Test failed"); exit(1); }

sSocket *initClients(unsigned int maxUser)
{
	sSocket *clients = malloc( sizeof(sSocket)*maxUser );
	logging(0, "Creating the list of clients");

	while((maxUser--) > 0)
		clients[maxUser].fd=-1;

	return clients;
}

void loop(sSocket server, unsigned int maxUser)
{
	fd_set read_fd_set;
	sSocket *clients = initClients(maxUser);
	int max_fd = 0;


	logging(0, "starting loop");

	while(1)
	{
		unsigned int i = 0;
		
		logging(0, "initialize the set of FD");
		FD_ZERO(&read_fd_set);
		FD_SET (server.fd, &read_fd_set);
		max_fd = server.fd;

		logging(0, "select");
		for(i=0; i < maxUser; ++i)
			if(socketIsValid(clients[i]))
			{
				FD_SET( clients[i].fd, &read_fd_set);
				max_fd = clients[i].fd > max_fd ?  clients[i].fd : max_fd;
			}

		dieIfFail( select (max_fd+1, &read_fd_set, NULL, NULL, NULL) < 0, 4);
		logging( 0, "testing all clients");
		for(i=0; i < maxUser; ++i)
		{
			sSocket client = clients[i];
			if(socketIsValid(client) && FD_ISSET(client.fd, &read_fd_set))
			{
				unsigned int j = 0;
				int size =0;
				char buffer[255];
				size = socketReceve(client, buffer, 255);
				
				if(size <= 0)
				{
					/* using clients[i] instead of client
					// beacause client is a copy of clients[i] */ 
					socketClose(&clients[i]);
				}
				else
				{
					buffer[size] = '\0';
					logging(1, "%s:%i - %s", client.addr, client.port, buffer);

					for(; j < maxUser; ++j)
						if(socketIsValid(clients[j]) && j != i)
							socketSend(clients[j], buffer, size+1);
				}
			}
		}
		logging( 0, "testing server");
		if(FD_ISSET(server.fd, &read_fd_set))
		{
			unsigned int index = 0;
			sSocket client = acceptClient(server);
			logging(0, "new connection");

			while(index < maxUser && socketIsValid(clients[index]))
				++index;

			if(index == maxUser)
			{
				socketSend(client, "Server is full\n", 15);
				socketClose(&client);
			}
			else
			{
				int i = 0;
				logging(0,"new client at %i", index);
				for(; i < maxUser; ++i)
					if(socketIsValid(clients[i]))
						socketSend(clients[i], "New client !\n", 13); 	
				clients[index] = client;
				socketSend(client, "Welcome !\n", 10);
			}
		}
	}
}
