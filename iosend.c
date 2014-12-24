#include<stdio.h>
#include<netdb.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
main()
{
  int s=socket(AF_INET,SOCK_STREAM,0);
  perror("After socket");

  struct sockaddr_in myAddr,addr;
  myAddr.sin_family=AF_INET;
  myAddr.sin_port=htons(1212);
  myAddr.sin_addr.s_addr=htonl(INADDR_ANY);
  
  int b=bind(s,(struct sockaddr*)&myAddr,sizeof(struct sockaddr_in));
  perror("After bind");

  addr.sin_family=AF_INET;
  addr.sin_port=htons(2121);
  addr.sin_addr.s_addr=htonl(INADDR_ANY);
  int con=connect(s,(struct sockaddr*)&addr,sizeof(struct sockaddr_in));
  perror("After connect");
 
//  send(s, "Hi\0",3,0);
  perror("After send");
}
