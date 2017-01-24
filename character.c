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

void describe(char * name){
  if (!strcmp(name,"DonWalf"))
    printf("Please pass us");
  else if (!strcmp(name,"Suwamik"))
    printf("Swagamick");
  else if (!strcmp(name,"Fortune"))
    printf("I wish you good fortune");
  else if (!strcmp(name,"Jackson"))
    printf("JP Morgan");
  else if (!strcmp(name,"Kart Mario"))
    printf("Not copyrighted");
  else if (!strcmp(name,"Goku"))
    printf("Kakarot");
  else if (!strcmp(name,"Zelda"))
    printf("You mean link?");
  else if (!strcmp(name,"Samus"))
    printf("actually a girl");
  else if (!strcmp(name,"Flash Gordon"))
    printf("fastest train ever");
  else if (!strcmp(name,"Beelzebub"))
    printf("wtf is this");
  else if (!strcmp(name,"Starman"))
    printf("David Bowe???");
  else if (!strcmp(name,"BoJack Horseman"))
    printf("Bo Jackson???");
  else if (!strcmp(name,"Darth Daddy"))
    printf("Force choke me");
  else if (!strcmp(name,"Donald Drumpf"))
    printf("All hail");
  else if (!strcmp(name,"Bill Nye the Science Guy"))
    printf("BILL BILL BILL BILL");
  else if (!strcmp(name,"Honey Boo Boo"))
    printf("gogo juice");
  else
    printf("wtf fortune");
}


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
      printf("%s: ", daddy[x]);
      describe(daddy[x]);
      printf("\n");
    }
  }
}

