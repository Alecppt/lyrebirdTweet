#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <unistd.h>
#pragma once

#define BACKLOG 10

int socket_setup();
int  getPortNum(int sockfd);
void getIPAddr(char* ip);
