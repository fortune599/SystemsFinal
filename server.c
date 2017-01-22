#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "networking.h"

void process( char * s );
void sub_server( int sd );

int doit = 1;
int sending;
int getting; 

char get[MESSAGE_BUFFER_SIZE];
char give[MESSAGE_BUFFER_SIZE];

void set(int i){
  doit = i;
}

void servget(int i){
  getting = i;
}

void sendclient(char send[MESSAGE_BUFFER_SIZE]){
  strncpy(get,send,MESSAGE_BUFFER_SIZE);
  sending = 1;
}

char * gotvalue(){
  return give;
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
  //printf("silly");
  char buffer[MESSAGE_BUFFER_SIZE];
  while (read( sd, buffer, sizeof(buffer) )) {
    strcpy(give,buffer);
    printf("give: %s\n", give);
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
