#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/types.h>
 
#define MAXLINE 8192
#define PORT 27993
#define ADDRESS 128.119.243.147
int clientfd;
char* doMath(int numb1,char op,int numb2){
  int result;
  char* toReturn = (char *) malloc(MAXLINE);
  if(op == '+'){
    result = numb1 + numb2;
  }
  else if(op == '*'){
    result = numb1 * numb2;
  }
  else if(op == '-'){
    result = numb1 - numb2;
  }
  else{
    result = numb1 / numb2;
  }
  printf("%i\n",result);
  sprintf(toReturn,"cs230 %i\n",result);
  return toReturn;
}
int open_clientfd(char *hostname, int port) {
  // The client's socket file descriptor.
  int clientfd;

  // The hostent struct is used to get the IP address of the server
  // using DNS.
  //
  // struct hostent {
  //   char *h_name;        // official domain name of host
  //   char **h_aliases;    // null-terminated array of domain names
  //   int  h_addrtype;     // host address type (AF_INET)
  //   int  h_length;       // length of an address, in bytes
  //   char **h_addr_list;  // null-terminated array of in_addr structs
  // };
  struct hostent *hp;

  // serveraddr is used to record the server information (IP address
  // and port number).
  //
  // struct sockaddr_in {
  //   short            sin_family;   // e.g. AF_INET
  //   unsigned short   sin_port;     // e.g. htons(3490)
  //   struct in_addr   sin_addr;     // see struct in_addr, below
  //   char             sin_zero[8];  // zero this if you want to
  // };
  struct sockaddr_in serveraddr;

  printf("Echo Client is creating a socket.\n");

  // First, we create the socket file descriptor with the given
  // protocol and protocol family.
  if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;

  // Query DNS for the host (server) information.
  if ((hp = gethostbyname(hostname)) == NULL) return -2;

  // The socket API requires that you zero out the bytes!
  bzero((char *)&serveraddr, sizeof(serveraddr));

  // Record the protocol family we are using to connect.
  serveraddr.sin_family = AF_INET;

  // Copy the IP address provided by DNS to our server address
  // structure.
  bcopy((char *)hp->h_addr_list[0], (char *)&serveraddr.sin_addr.s_addr,
        hp->h_length);

  // Convert the port from host byte order to network byte order and
  // store this in the server address structure.
  serveraddr.sin_port = htons(port);

  printf("Echo Client is trying to connect to %s (%s:%d).\n", hostname,
         inet_ntoa(serveraddr.sin_addr), port);

  // Establish a connection with the server.
  if (connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    return -1;

  printf("Echo Client connected.\n");

  // Return the connected file descriptor.
  return clientfd;
}
int main(int argc, char **argv) {
 // The client socket file descriptor.
  int clientfd;

  // The port number.
  int port;
  
  // Variable to store the host/server domain name.
  char *host;
  char *words[MAXLINE];
  char *buf = (char *) malloc(MAXLINE);
  char *massage = (char *) malloc(MAXLINE);
  char *firstid;
  char *secondid = (char *)malloc(MAXLINE); 
  // A buffer to receive data from the server.
  bool isFirst = true;
  char *flag;
  char *word;
  int index;
  strcat(secondid,argv[1]);
  strcat(secondid,"\n");
  if(argc != 4){
    fprintf(stderr, "usage: %s <identification> <host IP> <port>\n", argv[0]);
    exit(0);
  }
  host = argv[3];
  port = atoi(argv[2]);
  firstid = argv[1];
  // Open the client socket file descriptor given the host and port:
  clientfd = open_clientfd(host, port);
  if(clientfd < 0){
    fprintf(stderr, "failed to connect to the host <%s> in the port <%i>.\n", host, port);
    exit(0);
  }
  // Print "type: " and fflush to stdout:
  fflush(stdout);
  while(true){
    buf[strcspn(buf, "\n")] = '\0';
    if(!isFirst){
      printf("entering non first");
      flag = strstr(buf,"BYE");
      if(flag == NULL){
        printf("entering math");
        index = 0;
        word = strtok(buf," ");
        while(true){
        if(word != NULL){
          words[index] = word;
          index++;
          word = strtok(NULL," ");
        }
        else{
          break;
        }
        }
        if(strcmp(words[1],"STATUS")!=0){
          printf("invalid massage");
          exit(0);
        }
        int firNum = atoi(words[2]);
        char *oppt = words[3];
        char op = oppt[0];
        int secNum =atoi(words[4]);
        massage = doMath(firNum,op,secNum);
        printf("exiting math");
      }
      else{
        printf("entering non math");
        return 0;
      }
    }
    else{
      printf("entering first");
      strcpy(massage,"cs230 HELLO ");
      strcat(massage,secondid);
      isFirst = false;
      printf("exiting first");
    }
    ssize_t ns = send(clientfd, massage, strlen(massage), 0);
    ssize_t nr = recv(clientfd, buf, MAXLINE, 0);
    // Add a newline back on:
    buf[strlen(buf) + 1] = '\0';
    buf[strlen(buf)] = '\n';
    printf("echo (%ld bytes): ", nr);
    fputs(buf, stdout);
    printf("type: ");
    fflush(stdout);
  }
  return 0;
}
