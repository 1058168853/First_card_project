#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>
#include "tcpserver.h"

#define DEFAULT_PORT 8341
#define DEFAULT_BACKLOG 128
#define DEFAULT_IP "127.0.0.1"


void main() {
	uv::TCPServer* pServer = new uv::TCPServer();
	pServer->Start(DEFAULT_IP, DEFAULT_PORT);

}