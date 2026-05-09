/*
 * The <sys/types.h> header defines a variety of system specific data types which keep the code portable across
 * different versions of Linux. 
 *
 * <sys/socket.h> is the primary header for socket programming. Defines the actual system callls being used. 
 * Includes key fucntions such as socket(), bind(), listen(), accept(), send()
 * Also has constants AF_INET and SOCK_STREAM
 *
 *
 * <netdb.h> This functions like networks database library, mainly turning human readable names such as 'google.com'
 * into IP addresses. Has keyfunctions such as getaddrinfo() which looks up a hosts IP address
 * */



#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char *argv[]){
	
	// The function getaddrinfo() requires that a certain configuration structure is set up to 
	// accept its return. The hints structure tells the function what kind of connection 
	// is expected. By default, gettaddrinfo() returns dozens of options (ipv4, ipv6, TCP, UDP), 
	// this is filtered. 
	//
	// The *res pointer contains the information that is actually stored by the function. 
	// This contains the results 
	struct addrinfo hints, *res, *p;
	int status;
	char ipstr[INET6_ADDRSTRLEN];

	if (argc != 2){
		fprintf(stderr, "usage: showip hostname\n");
		return 1;
	}
	
	// memset() is a function used to fill a block of memory with a specific value
	// It is a sort of a 'bulk reset'. This is used in socket programming to clear 
	// garbage data from new variables before being used. 
	// void *memset(void *ptr, int value, size_t num)
	// ptr: The starting address of memory that needs to be filled
	// value: The value it needs to be filled with
	// num: The number of bytes to fill
	memset(&hints, 0, sizeof hints);
	

	// Here the ai_family is set to AF_UNSPEC, indicating it could be either IPV4 or IPV6
	// This could be set to AF_INET or AF_INET6 for ipv4 and ipv6 respectively	
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	// The below statement makes the function call to obtain the IP address
	// If there is an error (a non-zero value is returned) this is printed
	if((status = getaddrinfo(argv[1], NULL, &hints, &res )) != 0){
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 2;
	}


	printf("IP addresses for %s:\n\n", argv[1]);

	for(p = res; p != NULL; p = p->ai_next){
		void *addr;
		char *ipver;				// Stores IP version 4 or 6
		struct sockaddr_in *ipv4;
		struct sockaddr_in6 *ipv6;

		if (p->ai_family == AF_INET){
			ipv4 = (struct sockaddr_in *) p->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		}else{
			ipv6 = (struct sockaddr_in6 *) p->ai_addr;
			addr = &(ipv6->sin6_addr);
			ipver = "IPv6";
		}

		// Convert the IP to a string and print it
		inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
		printf(" %s %s\n", ipver, ipstr);
	
	}

	
	// Make a socket
	
	int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	if(sockfd == -1){
		perror("socket");
	}

	printf("Socket Descriptor: %d\n", sockfd);

	// Establish a connection
	
	int connect(sockfd, );

	freeaddrinfo(res);
	
	return 0;

}





