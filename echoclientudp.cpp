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
	int sockfd,newsockfd,portno,chilen,nBytes;
	char buffer[256];

      	struct sockaddr_in  serv_addr ;
	struct hostent *server;
socklen_t addr_size;
	if(argc<3)
	{	
		printf("No port provided");
		exit(1);	
	}
	portno = atoi(argv[2]);
	//printf("argument mil gyi sari\n");
	sockfd=socket(PF_INET, SOCK_DGRAM, 0);
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
	
	  /*Initialize size variable to be used later on*/
  addr_size = sizeof serv_addr;

  while(1){
    printf("Type a sentence to send to server:\n");
    fgets(buffer,1024,stdin);
    printf("You typed: %s",buffer);

    nBytes = strlen(buffer) + 1;
    
    /*Send message to server*/
    sendto(sockfd,buffer,nBytes,0,(struct sockaddr *)& serv_addr,addr_size);

    /*Receive message from server*/
                nBytes = recvfrom(sockfd,buffer,1024,0,NULL, NULL);

    printf("Received from server: %s\n",buffer);

  }
	
	
    	return 0;
}


