#include<stdio.h>
#include<netdb.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
main()
{
  int s= socket(AF_INET,SOCK_DGRAM,0);
  perror("After socket");
 
  struct sockaddr_in myAddr,serAddr;
  myAddr.sin_family=AF_INET;
  myAddr.sin_port=htons(1827);
  myAddr.sin_addr.s_addr=htonl(INADDR_ANY);
  
  struct ip_mreqn mreq;
  char add[24]="225.54.6.23";
  char cc=inet_pton(AF_INET,add,&mreq.imr_multiaddr.s_addr);
  mreq.imr_address.s_addr=htonl(INADDR_ANY);
  mreq.imr_ifindex=0;

  int opt=setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(struct ip_mreqn));
  perror("After setsockopt");

  int i=1;
  int opt1=setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&i,sizeof(i));
  perror("After setsckopt");

  int b=bind(s, (struct sockaddr*)&myAddr, sizeof(struct sockaddr_in));
  perror("After bind");

  char msg[100];
  int len=sizeof(struct sockaddr_in);
  int r=recvfrom(s, msg, sizeof(msg), 0, (struct sockaddr*)&serAddr, &len);
  printf("%s",msg);
}
