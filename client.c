 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "networking.h"

int doit1 = 0;
char get1[MESSAGE_BUFFER_SIZE] ;
char give1[MESSAGE_BUFFER_SIZE];
int sending1;
int getting1;
int done1;

void sendserv(char send[MESSAGE_BUFFER_SIZE]){
  strncpy(get1,send,MESSAGE_BUFFER_SIZE);
  sending1 = 1;
}


void set1(int i){
  doit1 = i;
}

void clientget(int i){
  getting1 = i;
}

char * gotvalue1(){
  return give1;
}

void sdone1(){
  done1 = 1;
}

int clien( int argc, char *argv[] ) {

  char *host;
  if (argc != 2 ) {
    printf("host not specified, conneting to 127.0.0.1\n");
    host = "127.0.0.1";
  }
  else
    host = argv[1];
  
  int sd;

  sd = client_connect( host );

  char buffer[MESSAGE_BUFFER_SIZE];
  strncpy(buffer,get1,MESSAGE_BUFFER_SIZE);
  
  if (doit1) {
    //printf("enter message: ");
    //fgets( buffer, sizeof(buffer), stdin );
    //char *p = strchr(buffer, '\n');
    //*p = 0;
  
    write( sd, buffer, sizeof(buffer) );
    read( sd, buffer, sizeof(buffer) );
    //printf( "received: %s\n", buffer );
    read( sd, give1, sizeof(give1) );
    //printf( "give: %s\n", give1 );
    if (sending1){
      write( sd, get1, sizeof(get1) );
    }
  }
  
  return 0;
}
