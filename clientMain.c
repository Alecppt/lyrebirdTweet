#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include "helper.h"

#define h_addr h_addr_list[0] /* for backward compatibility */
/*
#include "stack.h"
#include "decrypt.h"
*/

int main(int argc, char const *argv[])
{
    int sockfd, socket_read, portnum;
    char buff[1024];
    struct sockaddr_in serv_addr;


    if(argc != 3){
        printf("Usage: ./lyrebird.client <IPaddress> <Port>\n");
        exit(EXIT_FAILURE);
    }

    /* create socket */

    serv_addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) < 0) {
        printf("[%s] lyrebird client: can't get the IPaddress\n",getCurrentTime());
        exit(EXIT_FAILURE);
    }
    portnum = atoi(argv[2]);
    serv_addr.sin_port = htons(portnum);
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        printf("[%s] lyrebird client: failed to create socket\n", getCurrentTime());
        exit(EXIT_FAILURE);
    }

    /* connect() */
    if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr) < 0)) {
        printf("[%s] lyrebird client: connect error\n", getCurrentTime());
        exit(EXIT_FAILURE);
    }

    printf("[%s] lyrebird.client: PID %d connected to server %s on port %s.\n",getCurrentTime(), getpid(), argv[1], argv[2]);

    /* write socket */
    socket_read = write(sockfd, "hello", 5);

    /* read socket */
    while( (socket_read = read(sockfd, buff, 1024)) > 0) {
        buff[socket_read] = 0;
        printf("%s\n", buff);
    }



    return 0;
}