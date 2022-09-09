/* Assignment 8 | CS360
 * Author: Amethyst Skye
 *
 * Description: A program written in C which will will create a server upon executing './assignment8 server' and a client
 * upon execusting 'assignment8 client <address>' where address is a hostname or IP address. The server will keep track of
 * how many clients have connected. Upon connecting to the server, the server will send the current date and time to the
 * client. If any errors occur at runtime, the program will exit and a corrosponding error message will print to stdout.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


#define MY_PORT_NUMBER 49999

int numClients;

int main(int argc, char *argv[]){
    /*improper usage*/
    if(argc < 2){
        printf("Error -- Usage: ./assignment8 server OR ./assignment8 client <address> where address is a hostname or IP address.\n");
        return(-1);
    }

    /*server*/
    if(argc == 2 && (strcmp(argv[1], "server") == 0)){
        /*create server socket*/
        int listenfd = socket(AF_INET, SOCK_STREAM, 0);
        if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0){
            perror("Error:");
            exit(1);
        }

        /*bind socket to port*/
        char buffer[100];
        struct sockaddr_in servAddr;
        memset(&servAddr, 0, sizeof(servAddr));
        memset(buffer, 0, sizeof(buffer));
        servAddr.sin_family = AF_INET;
        servAddr.sin_port = htons(MY_PORT_NUMBER);
        servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

        if(bind(listenfd, (struct sockaddr*)&servAddr , sizeof(servAddr)) < 0){
            perror("Error:");
            exit(1);
        }

        /*listen for connection*/
        listen(listenfd, 1);
        numClients = 0;
        int connectfd, length = sizeof(struct sockaddr_in);
        struct sockaddr_in clientAddr;

        /*waits for client connection*/
        while(1){
            if((connectfd = accept(listenfd, (struct sockaddr *) &clientAddr, &length)) < 0){
                perror("Error:");
                exit(1);
            }
            numClients++;
            if(fork()){
                /*parent*/
                close(connectfd);
            }
            else{
                /*child*/
                /*write date and time to client*/
                time_t data;
                time(&data);
                write(connectfd, ctime(&data), 18);

                /*print info to stdout*/
                char hostName[NI_MAXHOST];
                int hostEntry;
                if((hostEntry = getnameinfo((struct sockaddr*)&clientAddr, sizeof(clientAddr), hostName, sizeof(hostName), NULL, 0, NI_NUMERICSERV)) != 0){
                    perror("getnameinfo\n");
                    exit(1);
                }
                printf("%s %d\n", hostName, numClients);
                close(connectfd);
                exit(1);
            }
        }
        return 0;
    }

    /*client*/
    if(argc == 3 && (strcmp(argv[1], "client") == 0)){
        /*create client socket*/
        int socketfd = socket( AF_INET, SOCK_STREAM, 0);

        /*set up address*/
        struct addrinfo hints, *actualdata;
        memset(&hints, 0, sizeof(hints));
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_family = AF_INET;
        int err;
        if((err = getaddrinfo(argv[2], "49999", &hints, &actualdata)) != 0){
            fprintf(stderr, "Error: %s\n", gai_strerror(err));
            exit(1);
        }

        socketfd = socket(actualdata->ai_family, actualdata->ai_socktype, 0);
        if(connect(socketfd, actualdata->ai_addr, actualdata->ai_addrlen) < 0){
            perror("Error:");
            exit(1);
        }
        int numRead;
        char buffer[100];
        /*read and write 18 bytes from server*/
        int i = 0;
        while((numRead = read(socketfd, buffer, 18)) > 0){
            write(1, buffer, numRead);
            printf("\n");
        }
        close(socketfd);
        return 0;
    }
}
