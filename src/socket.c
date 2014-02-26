#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>
#include "socket.h"
#include "log.h"

sSocket createSocket(unsigned int port)
{
	sSocket server;
	server.fd = socket(AF_INET, SOCK_STREAM, 0);
	server.port = port;
	return server;
}

int socketIsValid( sSocket sock )
{
	return sock.fd >= 0;
}

int socketBind(sSocket *sock)
{
	struct sockaddr_in serv;

	bzero((char *) &serv, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = INADDR_ANY;	
	serv.sin_port = htons(sock->port);

	strncpy(sock->addr, inet_ntoa(serv.sin_addr), 16);
	return bind(sock->fd, (struct sockaddr *) &serv, sizeof(serv));
}

void socketListen(sSocket sock, unsigned int backlog)
{
	listen(sock.fd, backlog);
}

sSocket acceptClient(sSocket sock)
{
	struct sockaddr_in cli;
	sSocket client;
	socklen_t clisize = sizeof(struct sockaddr_in);
	client.fd = accept(sock.fd, (struct sockaddr *)&cli, &clisize);

	strncpy(client.addr, inet_ntoa(cli.sin_addr), 16);
	client.port = ntohs( cli.sin_port );
	return client;
}

void socketSend(sSocket sock, void *buffer, unsigned int size)
{	send(sock.fd, buffer, size,0);	}

int socketReceve(sSocket sock, void *buffer, unsigned int size)
{	return recv(sock.fd, buffer, size,0);	}


void socketClose(sSocket *sock)
{
	if(sock != 0 && socketIsValid(*sock))
	{
		close(sock->fd);	
		sock->fd = -1;
	}
}


