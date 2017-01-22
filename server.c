#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>


#include "networking.h"

void process( char * s );
void sub_server( int sd );

int doit = 1;
int sending;
int getting;
int done; 

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

//char * gotvalue(){
//return give;
//}

void sdone(){
  done = 1;
}

int sd;

int serve() {
  int connection;

  
  if(!done){
  sd = server_setup();
  }
  

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
  //printf("give: %s\n", give);
  return 0;
}


void sub_server( int sd ) {
  //printf("silly");
  char buffer[MESSAGE_BUFFER_SIZE];
  read( sd, buffer, sizeof(buffer) );
  strcpy(give,buffer);
  int fd = open( "store.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644 );
  write(sd,give,sizeof(give));
  //printf("give: %s\n", give);
  //process( buffer );
  write( sd, buffer, sizeof(buffer));
  if(sending){
    write( fd, get, sizeof(get));
  }
  close(fd);
  //printf("give: %s\n", give);
}
  

void process( char * s ) {

  while ( *s ) {
    *s = (*s - 'a' + 13) % 26 + 'a';
    s++;
  }
}
