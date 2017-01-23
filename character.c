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
  char ** daddy = (char **)malloc(sizeof(char*));
  
  int fd = open( "Players.txt", O_RDONLY );
  char buff[1024];
  read( fd, buff, sizeof(buff) );
  close( fd );

  int i = 0;
  char * s = buff;
  while( s ){
    daddy[i] = strsep(&s, "\n");
    if (c1[0] == '\0' && c2[0] == '\0')
      printf("%s\n",strsep(&daddy[i],","));
    if (c1[0] != '\0' && c2[0] != '\0')
      if (strstr(daddy[i],c1) == NULL && strstr(daddy[i],c2) == NULL)
    	printf("%s\n",strsep(&daddy[i],","));
    if (c1[0] != '\0' && c2[0] == '\0')
      if (strstr(daddy[i],c1) == NULL && strstr(daddy[i],c2) != NULL)
    	printf("%s\n",strsep(&daddy[i],","));
    i++;
  }
}

