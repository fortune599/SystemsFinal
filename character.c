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

#include "networking.c"
#include "networking.h"
#include "server.c"
#include "client.c"

struct character{
  char* name;
  int hp;
  int ap;
  int atk;
  int def;
  int matk;
  int mdef;
  int initv;
};

int damage(struct character *pl, struct character *en){
  en->hp -=  (pl->atk * pl->atk) / en->def;
  return en->hp;
}

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
    printf("David Bowie???");
  else if (!strcmp(name,"BoJack Horseman"))
    printf("Bo Jackson???");
  else if (!strcmp(name,"Darth Daddy"))
    printf("Force choke me harder");
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
      printf("%s: [", daddy[x]);
      describe(daddy[x]);
      printf("]\n");
    }
  }
}

void respond(int isServer, int *enHP, char *args[]){
  if (!isServer){
    sendserv("wasted space");
    clien(1, args);//hangs up here
    if ( strstr( gotvalue1(), "enHP 0" ) != NULL){
      *enHP = 0;
    }
  }
  else{
    sendclient("wasted space");
    serve();
    if ( strstr( gotvalue(), "enHP 0" ) != NULL){
      *enHP = 0;
    }
  }
}

void act(int isServer, int *myHP, struct character attacker, struct character opponent[], char commands[], char *args[]){
  char msg[256] = "";
  int dmg;
  char stor[128];

  printf("\nSELECT %s's ACTION:\n", attacker.name);
  printf("Attack | Defend | Concede\n");
  fgets(commands, sizeof(commands), stdin);
  commands[strcspn(commands, "\n")] = 0;
  if (!isServer){
    if ( strstr(commands, "Attack") != NULL ){
      printf("SELECT TARGET\n");
      int i = 0;
      for (i; i < 3; i++){
	printf("%s  ", opponent[i].name);
      }
      printf("\n");
      fgets(commands, sizeof(commands), stdin);
      commands[strcspn(commands, "\n")] = 0;
      for (i = 0; i < 3; i++){
	if (strstr (opponent[i].name, commands) != NULL){
	  strcat(msg, opponent[i].name);
	  strcat(msg, " ");
	  dmg = damage(&attacker, &opponent[i]);
	  sprintf(stor, "%d", dmg);
	  strcat(msg, stor);
	  printf("Enemy %s has %d health remaining!\n", opponent[i].name, dmg);
	  sendserv(msg);
	  clien(1, args);
	  break;
	}
      }
    }
    else if ( strstr(commands, "Concede") != NULL ){
      printf("sending concession");
      strcpy(msg, "enHP 0");
      sendserv(msg);
      clien(1, args);
      *myHP = 0;
    }
  }
  else{
    if ( strstr(commands, "Attack") != NULL ){
      printf("SELECT TARGET\n");
      int i = 0;
      for (i; i < 3; i++){
        printf("%s  ", opponent[i].name);
      }
      printf("\n");
      fgets(commands, sizeof(commands), stdin);
      commands[strcspn(commands, "\n")] = 0;
      for (i = 0; i < 3; i++){
        if (strstr (opponent[i].name, commands) != NULL){
          strcat(msg, opponent[i].name);
          strcat(msg, " ");
          dmg = damage(&attacker, &opponent[i]);
          sprintf(stor, "%d", dmg);
          strcat(msg, stor);
          printf("Enemy %s has %d health remaining!\n", opponent[i].name, dmg);
          sendclient(msg);
          serve();
          break;
        }
      }
    }
    else if ( strstr(commands, "Concede") != NULL ){
      printf("sending concession\n");
      strcpy(msg, "enHP 0");
      sendclient(msg);//hangs up here
      serve();
      *myHP = 0;
    }
  }
}
