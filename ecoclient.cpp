#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>



int main(int argc, char *argv[])
{
	int sockfd,newsockfd,portno,chilen;
	char buffer[256];
      	struct sockaddr_in  serv_addr ;
	struct hostent *server;
	if(argc<3)
	{	
		printf("No port provided");
		exit(1);	
	}
	portno = atoi(argv[2]);
	//printf("argument mil gyi sari\n");
	sockfd=socket(AF_INET, SOCK_STREAM,0);
	if(sockfd<0)
	{
		printf("Error opening sockt\n");
		exit(1);
	}
	//printf("Socket bhi open ho gya\n");
	server = gethostbyname(argv[1]);
	bzero((char*)& serv_addr,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port=htons(portno);
	bcopy((char*) server->h_addr, (char*)& serv_addr.sin_addr.s_addr,server->h_length);
	serv_addr.sin_port=htons(portno);
	if(connect(sockfd,(struct sockaddr*)& serv_addr, sizeof(serv_addr))<0)
	{
		printf("Connection failed\n");
		exit(1);
	}
	while(1)
	{
		printf("Client: ");
		fgets(buffer,255,stdin);
		int n;
		n=write(sockfd, buffer,strlen(buffer));
		if(n<0){
			printf("Error on writing\n");
			exit(1);
   		}
		//printf("write bhi ker dia\n");
		bzero(buffer,256);
		n=read(sockfd, buffer, 255);
		if(n<0)
		{
			printf("Error reading\n");
		  	exit(1);
		}
		printf("Server: %s",buffer);
		//printf("Read bhi ker dia\n");
	}
    	return 0;
}


