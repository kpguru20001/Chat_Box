#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#define PORT 5000
int main(int argc, char const *argv[])
{
  struct sockaddr_in address,cl_ad;
  int opt = 1,con,sin_size;
  int server_fd, new_socket, valread;
  int addrlen = sizeof(address);
  char buffer[1024];
  char *hello = "hello from server";
  //socket descripto for server using socket()

  if((server_fd = socket(AF_INET, SOCK_STREAM, 0 ))== -1)
  {
    perror("Socket failed!!\n");
    exit(EXIT_FAILURE);
  }
  if (setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(int)) == -1)
  {
    perror("Setsockopt");
    exit(1);
  }

  //setting connection family in this case IPv4
  address.sin_family = AF_INET;
  //htons to convert host to network bytes
  address.sin_port = htons(8000);
  //setting destination address using
  address.sin_addr.s_addr =INADDR_ANY;

  bzero(&(address.sin_zero),8);
  //bind the socket to address and the port socket desc, pointer of address and address length
  if(bind(server_fd,(struct sockaddr *)&address,sizeof(struct sockaddr)) < 0)
  {
    perror("Binding Failed\n");
    exit(EXIT_FAILURE);
  }
  puts("waiting for client");
  //waits for client requesting for connection socket desc,backlog i.e max queue
  if(listen(server_fd, 6) == -1)
  {
    perror("listen failure");
    exit(EXIT_FAILURE);
  }
  //accepts 1st connection in queue and sets up a new seperate temporary socket connection witb the client
  fflush(stdout);
  sin_size = sizeof(struct sockaddr_in);
  puts("accepting.....");
  con = accept(server_fd, (struct sockaddr *)&cl_ad,&sin_size);
  //connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);
  puts("connected successfully");
  valread = recv(con, buffer, 1024,0);
  printf("%s\n",buffer);
  send(con, hello, strlen(hello), 0);
  printf("hello message sent\n");
  char s[40];
  do{
    char s[40]={0},buffer[1024]={0};
    valread = recv(con,buffer,1024,0);
    printf("client:%s\n",buffer);
    printf("\nServer:");
    scanf("%s",s);
    send(con, s, strlen(s), 0);
  } while(1);
  return 0;
}
