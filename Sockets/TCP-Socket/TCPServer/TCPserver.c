#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>


int main() {
  // 1. Create msg (data) to be shared with clients
  char server_message[256] = "You have reached the server";
  
  // 1. Create a socket 
  int server_socket;
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  
  // 2. Specify an address for the socket 
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9002);
  server_address.sin_addr.s_addr = INADDR_ANY;
  
  // 3. Bind the socket to our specified IP/Port
  bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
  
  // 4. Listen for connections (max = 5)
  listen(server_socket, 5);
  
  // 5. Create integer to hold client sockets and accept connections
  int client_socket;
  client_socket = accept(server_socket, NULL, NULL);
  
  // 6. Send message (data) from server to client
  send(client_socket, server_message, sizeof(server_message), 0);
  
  // 7. Close the socket 
  close(server_socket);
  
  return 0;
}    
