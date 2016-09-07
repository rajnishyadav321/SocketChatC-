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
      	struct sockaddr_in  serv_addr ,cli_addr;
	int n;
	if(argc<3)
	{	
		printf("No port provided");
		exit(1);	
	}
	//printf("argument mil gyi sari\n");
	sockfd=socket(AF_INET, SOCK_STREAM,0);
	if(sockfd<0)
	{
		
	printf("Error opening sockt\n");
	exit(1);
	}
	//printf("Socket bhi open ho gya\n");
	bzero((char*)& serv_addr,sizeof(serv_addr));
	portno= atoi(argv[2]);
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port=htons(portno);
	if(bind(sockfd,(struct sockaddr*)& serv_addr,sizeof(serv_addr))<0)
	{
	printf("Error on binding\n");
	exit(1);
	}
	//printf("Bind bhi ho gya\n");
	listen(sockfd,5);
	chilen = sizeof(cli_addr);
	newsockfd=accept(sockfd,(struct sockaddr*)& cli_addr,( socklen_t*)& chilen);
	if(newsockfd<0){
	printf("Error on acceptance\n");
	exit(1);
	}
	//printf("Accept ho gya child socket \n");
	while(1)
	{
		bzero(buffer,256);
		n=read(newsockfd,buffer,255);
		if(n<0){
			printf("Error on reading\n");
			exit(1);
   		}
			//printf("Read bhi ker liya\n");
			printf("Client: %s",buffer);
			bzero(buffer,256);
			char a[256];
			printf("Server: ");
		        fgets(buffer,255,stdin);
			
			n=write(newsockfd,buffer,strlen(buffer));
		if(n<0)
		{
			printf("Error writing\n");
			exit(1);
		}
		//printf("Write bhi ker dia\n");	
	}
    	return 0;
}


