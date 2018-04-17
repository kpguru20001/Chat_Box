#include<stdio.h>
#include<netdb.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>

#define PORT 5000

int main(int argc, char const *argv[])
{
  // initiallzing socket structure containing address variables
  char ip[9] = "127.0.0.1";
  int sock = 0, valread;
  struct sockaddr_in serv_addr;
  struct hostent *host;

  host = gethostbyname("127.0.0.1");
  char *hello = "Hello from client";
  char buffer[1024] = {0};
  //socket Creation
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
      perror("Socket");
      exit(1);
  }
  //setting memory or address containing serv_addr as 0 uptill the complete length of serv_addr is filled
  //memset(&serv_addr, '0', sizeof(serv_addr));
  //assigning values to variables in serv_addr
  serv_addr.sin_family = AF_INET;
  //htons converts unsigned short value from host byt168e order to network byte order
  serv_addr.sin_port = htons(8000);
  //getting from hostent the required addr to sockaddr_in struct
  serv_addr.sin_addr = *((struct in_addr *)host->h_addr);
  bzero(&(serv_addr.sin_zero),8);
  // USING PRINTABLE TO NETWORK FUNCTION
  /*if(inet_pton(AF_INET, ip , serv_addr.sin_addr)<=0){
    perror("address not found!!");
    exit(EXIT_FAILURE);
  }*/
  //checking for connection with server socket descriptor, pointer to serv addres n serv addr length n if return is -1 means fail
  if(connect(sock , (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1)
  {
    perror("connection failed!!");
    exit(1);
  }
  //sending message to server
  send(sock, hello, strlen(hello),0);
  printf("\nchat box open!!\n");
  valread = recv(sock,buffer,1024,0);
  //recieving server message to start conversation
  printf("\n%s\n",buffer);
  //continue chatting till end string is entered by both server and client
  char s[40];
  do{
    char s[40]={0},buffer[1024]={0};
    printf("\nClient:");
    scanf("%s",s);
    send(sock,s,strlen(s),0);
    valread = recv(sock,buffer,1024,0);
    printf("Server:%s\n",buffer);
  } while(1);
  return 0;
}
