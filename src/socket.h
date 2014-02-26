#ifndef __SOCKET_H__
#define __SOCKET_H__

typedef struct {
	int fd;
	unsigned short port;
	char addr[16];
} sSocket;


sSocket createSocket( unsigned int port );
int socketIsValid( sSocket sock );
int socketBind(sSocket *sock);
void socketListen(sSocket sock, unsigned int backlog);

sSocket acceptClient(sSocket sock);

void socketSend(sSocket sock, void *buffer, unsigned int size);
int socketReceve(sSocket sock, void *buffer, unsigned int size);

void socketClose(sSocket *sock);


#endif
