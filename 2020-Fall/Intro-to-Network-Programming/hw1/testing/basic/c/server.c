#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BUFLEN 1024
#define SA struct sockaddr
#define SA_in struct sockaddr_in

void ChatFunc(int sockfd, SA_in saddr);
void sigCatcher(int sig);
int main(int argc, char const *argv[]){
	if(argc != 2){
		printf("\tInvalid parameters!!!\n");
		printf("\tUsage %s <Listen Port>\n", argv[0]);
		exit(-1);
	}
	int ListenPort = atoi(argv[1]);

	int sockfd = 0; // server file descriptor
	sockfd = socket(AF_INET, SOCK_STREAM, 0); // create master socket
	if (sockfd == -1) { // vertify socket
		printf("[x] Socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("[*] Socket successfully created..\n");

	SA_in servaddr, cliaddr;
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr));

	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = INADDR_ANY; // use INADDR_ANY to listen on 0.0.0.0 
	servaddr.sin_port = htons(ListenPort); 

	// Binding newly created socket to given IP and verification 
	if(bind(sockfd, (SA*)&servaddr, sizeof(servaddr)) < 0){
		printf("[x] Socket bind failed...\n"); 
		exit(0);
	} 
	else
		printf("[*] Socket successfully binded..\n"); 
  
	// Now server is ready to listen and verification 
	if (listen(sockfd, 10) < 0){
		printf("[x] Failed to start listen process\n");
		exit(0);
	}
	else
		printf("[*] Server listening on %s:%d\n", inet_ntoa(servaddr.sin_addr), ListenPort);

	signal(SIGCHLD, sigCatcher); //handler to clear zombie process
	int ssockfd = 0, pid = 0, len = sizeof(cliaddr);
	while(1){
		// accept client connection
		ssockfd = accept(sockfd, (SA*)&cliaddr, &len);
		if(ssockfd < 0){
			printf("[x] Server accept failed\n");
			break;
		}
		printf("[*] Accept connection %d from %s:%d\n", ssockfd, inet_ntoa(cliaddr.sin_addr), (int)ntohs(cliaddr.sin_port));
		pid = fork();
		if(pid < 0){
			printf("E: Process fork() failed\n");
			break;
		}
		else if(pid == 0){
			// child process
			printf("[Child] Child's PID is %d\n", getpid());
			ChatFunc(ssockfd, cliaddr);
			close(ssockfd);
		}
	}

	close(sockfd); // close master socket
	return 0;
} 
void ChatFunc(int sockfd, SA_in saddr){
	// Function designed for chat between client and server.
	char buf[BUFLEN];
	while(1){ // loop for chating
		memset(buf, 0, BUFLEN);
		ssize_t bsize = recv(sockfd, buf, sizeof(buf), 0); // recv msg from client
		if(bsize < 0) continue; // Ignore failed request
		// print buffer which contains the client contents
		printf("Received %ld bytes from %s:%d, %s", bsize, inet_ntoa(saddr.sin_addr), (int)ntohs(saddr.sin_port), buf);
		// if msg contains "Exit" then server exit and chat ended. 
		if(strncmp("exit", buf, 4) == 0) { 
			printf("[!] Client Exit...\n"); 
			return;
		}

		// copy server message in the buffer
		// memset(buf, 0, BUFLEN); // TEST echo
		
		bsize = send(sockfd, buf, sizeof(buf), 0); // send msg of server
		if(bsize < 0) return; // Ignore failed request
	} 
}
void sigCatcher(int sig){
	int retval;
	if ( sig == SIGCHLD ){ 
		wait(&retval);
		printf("CATCH SIGNAL PID=%d\n",getpid());
	}
}
