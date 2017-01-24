#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void printCharac(char * c1, char * c2){

  char a[256];
  char b[256];
  if (!strlen(c1))
    strcpy(a, "antidisestablishmentarianism");
  else
    strcpy(a, c1);
  if (!strlen(c2))
    strcpy(b, "antidisestablishmentarianism");
  else
    strcpy(b, c2);

  char ** daddy = (char **)malloc(sizeof(char*));
  
  int fd = open( "Players.txt", O_RDONLY );
  char buff[1024];
  read( fd, buff, sizeof(buff) );
  close( fd );

  int i = 0;
  char * s = buff;
  while( s ){
    daddy[i] = strsep(&s, "\n");
    i++;
  }
  
  i--;

  int x = 0;
  for (x; x < i; x++){
    if ( (strstr ( daddy[x], a ) == NULL) && (strstr ( daddy[x], b ) == NULL) ){
      daddy[x] = strsep(&daddy[x],",");
      printf("%s\n", daddy[x]);
    }
  }
}
