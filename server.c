#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "networking.h"

void process( char * s );
void sub_server( int sd );

int doit = 1;
int sending;

char get[MESSAGE_BUFFER_SIZE];

void set(int i){
  doit = i;
}

void sendclient(char send[MESSAGE_BUFFER_SIZE]){
  strncpy(get,send,MESSAGE_BUFFER_SIZE);
  sending = 1;
}


int serve() {

  int sd, connection;

  sd = server_setup();
    
  

    connection = server_connect( sd );

    if (doit) { 
      
    int f = fork();
    if ( f == 0 ) {

      close(sd);
      sub_server( connection );

      exit(0);
    }
    else {
      close( connection );
    }
  }
  return 0;
}


void sub_server( int sd ) {

  char buffer[MESSAGE_BUFFER_SIZE];
  while (read( sd, buffer, sizeof(buffer) )) {

    printf("[SERVER %d] received: %s", getpid(), buffer );
    process( buffer );
    write( sd, buffer, sizeof(buffer));
    if(sending){
      write( sd, get, sizeof(get));
    }
  }
  
}
void process( char * s ) {

  while ( *s ) {
    *s = (*s - 'a' + 13) % 26 + 'a';
    s++;
  }
}












