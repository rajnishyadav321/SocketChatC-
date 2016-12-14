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

      	struct sockaddr_in  serv_addr ,cli_addr;
	int n;
socklen_t addr_size;
	if(argc<3)
	{	
		printf("No port provided");
		exit(1);	
	}
	//printf("argument mil gyi sari\n");
	sockfd=socket(PF_INET, SOCK_DGRAM,0);
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
/*Initialize size variable to be used later on*/
  addr_size = sizeof cli_addr;

  while(1){
    /* Try to receive any incoming UDP datagram. Address and port of 
      requesting client will be stored on serverStorage variable */
    nBytes = recvfrom(sockfd,buffer,1024,0,(struct sockaddr *)& cli_addr, &addr_size);
printf("recieved\n");
    /*Convert message received to uppercase*/
   

    /*Send uppercase message back to client, using serverStorage as the address*/
    sendto(sockfd,buffer,nBytes,0,(struct sockaddr *)& cli_addr,addr_size);
printf("sent\n");
  }       

    	return 0;
}


