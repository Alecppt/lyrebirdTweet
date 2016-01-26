/*
(1) student's name:     Alec Chen
(2) student ID:         301187669
(3) SFU user name:      cca169
(4) lecture section:    CMPT 300 D1 (Fall 2015)
(5) instructor's name:  Brian Booth
(6) TA's name:          Scott Kristjansonnclude
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <string.h>
#include "stack.h"
#include "decrypt.h"
#include "helper.h"
#include "network.h"

int main(int argc, char const *argv[])
{
    int socket_fd, port, retval, fdmax, listener, newfd, nbytes, i;
    struct sockaddr_storage client_addr;
    socklen_t addrlen;
    addrlen = sizeof(client_addr);
    char client_data[256];
    char server_ip_adress[16];
    char client_ip_adress[16];
    FILE *config, *log;

    fd_set fd_list; /*  main fd list */
    fd_set fd_select_copy; /* temp fd list for select() */
    struct timeval tv;
    fd_set fd_list_copy;


    /*  check argv[]  */
    if(argc != 3) {
        printf("%s\n", "Usage: ./lyrebird.server config_file.txt log_file.txt");
        exit(EXIT_FAILURE);
    }
    config = fopen(argv[1] , "r");
    log = fopen(argv[2], "w");
    if(config == NULL){
        printf("File: %s is not found\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    /* server setup */
    socket_fd = socket_setup();
    port = getPortNum(socket_fd);
    getIPAddr(server_ip_adress);
    printf("[%s] lyrebird.server: PID %d on host %s, port %d\n", getCurrentTime(), getpid(),server_ip_adress, port);

    /* main operation */
    fdmax = socket_fd;
    while(1){
        fd_select_copy = fd_list;
        if(select(fdmax+1, &fd_select_copy, NULL, NULL, NULL) == -1){
            printf("select failed\n");
            exit(EXIT_FAILURE);
        }
        /* loop through existing connection */
        for(i = 0; i<= fdmax; i++){
            /* check is there data to be read */
            if (FD_ISSET(i, &fd_select_copy)){
                if(i == socket_fd){  /* new connection */
                    newfd = accept(socket_fd, (struct sockaddr *) &client_addr,&addrlen);
                    inet_ntop(client_addr.ss_family, &((struct sockaddr_in *)&client_addr)->sin_addr, client_ip_adress, INET_ADDRSTRLEN);
                    if(newfd != -1){
                        FD_SET(newfd, &fd_list);
                        if(newfd > fdmax){
                            fdmax = newfd;
                        }
                        fprintf(log, "[%s] Successfully connected to lyrebird client %s.\n", getCurrentTime(), client_ip_adress);
                    }
                }
                else
                { /* client send data in */
                    getpeername(i, (struct sockaddr *)&client_addr, &addrlen);
                    inet_ntop(client_addr.ss_family, &((struct sockaddr_in *)&client_addr)->sin_addr, client_ip_adress, INET_ADDRSTRLEN);

                    if(nbytes == recv(i, client_data, sizeof(client_data), 0 ) <= 0){
                        if(nbytes == 0){
                            /* client connection closed */
                            /* should check expectedly */
                            if(1){
                                fprintf(log, "[%s] lyrebird client %s has disconnected unexpectedly\n", getCurrentTime(), client_ip_adress);
                            }
                            else{

                                fprinf(log, "[%s] lyrebird client %s has disconnected expectedly\n", getCurrentTime(), client_ip_adress);
                            }
                        }
                        close(i);
                        FD_CLR(i, &fd_list);
                    }
                    else{ /* nbytes not 0 */

                    }
                }

            }

            {
                /* code */
            }
        }

    }

    printf("[%s] lyrebird server: PID %d completed its tasks and is exiting successfully.\n",getCurrentTime(), getpid());
    close(socket_fd);
    fclose(config);
    fclose(log);
    return 0;
}