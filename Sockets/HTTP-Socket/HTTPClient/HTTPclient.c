#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

#include <sys/types.h> 
#include <sys/socket.h> 

#include <netinet/in.h> 

#include <arpa/inet.h> /** additional functionality for converting network addresses */

int main(int argc, char *argv[]) { /** specify which server the (TCP) client will connect to */
  char *address;
  address = argv[1];
  
  // create Client Socket
  int client_socket;
  client_socket = socket(AF_INET, SOCK_STREAM, 0);
  
  // connect to an Address 
  struct sockaddr_in remote_address;
  remote_address.sin_family = AF_INET;
  remote_address.sin_port = htons(80);
  inet_aton(address, &remote_address.sin_addr.s_addr); // convert (string) address from cmd-line to an address structure 
  connect(client_socket, (struct sockaddr *) &remote_address, sizeof(remote_address));
  
  // request & response
  char request[] = "GET / HTTP/1.1\r\n\r\n";
  char response[4096];
  
  // send/receive HTTP request 
  send(client_socket, request, sizeof(request), 0); 
  recv(client_socket, &response, sizeof(response), 0);
  
  // print data sent from server 
  printf("repsonse from the server: %s\n", response);
  
  // close the socket 
  close(client_socket);
   
  return 0;
}
