#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#define BUFLEN 500
#define SA struct sockaddr
#define SA_in struct sockaddr_in

int main(int argc, char **argv){
	if(argc != 3){
		printf("\tInvalid parameters!!!\n");
		printf("\tUsage %s <Server IP> <Server Port>\n", argv[0]);
		exit(-1);
	}
	char *ServerIP = argv[1];
	int ServerPort = atoi(argv[2]);

	int sockfd = 0; // socket file descriptor
	sockfd = socket(AF_INET, SOCK_STREAM, 0); // create socket
	if (sockfd == -1) { // vertify socket
		printf("[x] Socket creation failed...\n"); 
		exit(-1); 
	}

	SA_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr)); 

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(ServerIP);
	servaddr.sin_port = htons(ServerPort);

	
	// connenct to server 
	if(connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) < 0){
		printf("[x] Failed to connect to %s:%d\n", ServerIP, ServerPort);
		exit(-1);
	}
	else{
		// printf("[*] Connected to %s:%d\n", ServerIP, ServerPort);
		printf("********************************\n** Welcome to the BBS server. **\n********************************\n%c ", 37);
	}

	char buf[BUFLEN];
	while(fgets(buf, sizeof(buf), stdin)){
		send(sockfd, buf, strlen(buf), 0); // send msg to server
		if(strncmp("exit", buf, 4) == 0){
			// sleep(1);
			break; 
		}
		recv(sockfd, buf, sizeof(buf), 0); // recv msg from server
		printf("%s%c ", buf, 37);
	}
	close(sockfd);
	// shutdown(sockfd, SHUT_RDWR);
	return 0;
}