#include "network.h"


int socket_setup(){

    /* reference: http://beej.us/guide/bgnet/output/html/multipage/getaddrinfoman.html
                  http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html#htonsman
    */
    int flag, sockfd;

    struct addrinfo hints, *servinfo, *host;
    struct addrinfo ;

    memset(&hints, 0 , sizeof(hints));
    hints.ai_family = AF_INET;  /* IPv4 protocol */
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((flag = getaddrinfo(NULL, "0", &hints, &servinfo)) != 0)
    {
       printf("getaddrinfo error: %s\n", gai_strerror(flag));
       exit(1);
    }
    /* check the linked list of addrinfo structs to create/bind socket */

    for ( host = servinfo; host!= NULL; host = host->ai_next ){

        if((sockfd = socket(host->ai_family, host->ai_socktype, host->ai_protocol)) == -1)
        {
            continue;
        }
        int value = 1;
        /* ref: http://pubs.opengroup.org/onlinepubs/7908799/xns/getsockopt.html*/
       if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value)) == -1){
        printf("setsockopt failed\n");
        exit(1);
       }

        if(bind(sockfd, host->ai_addr, host->ai_addrlen) == -1) {
            close(sockfd);
            continue;
        }

        break;
    }
    freeaddrinfo(servinfo);

    /* check whether the bind is successful*/
    if(host == NULL){
        printf("lyrebird.server failed to bind\n");
        exit(1);
    }

    if(listen(sockfd, BACKLOG) == -1){
        printf("lyrebird.server failed to listen\n");
        exit(1);
    }
    return sockfd;
}

int getPortNum(int sockfd){
    int port;

    struct sockaddr_in socket_addr;
    socklen_t addrlen = sizeof(socket_addr);
    if(getsockname(sockfd, (struct sockaddr *)&socket_addr, &addrlen ) == -1){
        printf("getsockname failed\n");
        exit(1);
    }
    return port = ntohs(socket_addr.sin_port);
}

void getIPAddr(char* ip){
    int family;
    struct ifaddrs *ifaddr, *ifa;
    void* addr;
    /* get a linked list of network interface structs */
     if (getifaddrs(&ifaddr) == -1) {
         printf("getifaddrs error\n");
         exit(EXIT_FAILURE);
     }
     for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if(ifa->ifa_addr == NULL){
            continue;
        }
        family = ifa->ifa_addr->sa_family;
        if(family == AF_INET){
            addr =&((struct sockaddr_in *)ifa->ifa_addr )->sin_addr;
            inet_ntop(AF_INET, addr, ip, INET_ADDRSTRLEN );
            if(strcmp(ip, "127.0.0.1") == 0){
                continue;
            }
            else if(strcmp(ip, "0.0.0.0") == 0){
                continue;
            }
            else {
                break;
            }
        }

     }
     if(ip == NULL ){
        printf("inet_ntop failed\n");
        exit(EXIT_FAILURE);
     }
    freeifaddrs(ifaddr);

}