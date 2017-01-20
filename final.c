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
  char* friend;
};

struct character man1;
struct character man2;
struct character man3;

struct character party[3];

//test case
struct character test;

void setValue(int * stat, int newVal){
  *stat = newVal;
}

void damage(int platk, int endef, int enhp){
  enhp -=  (platk * platk) / endef;
}

void mdamage(int plmatk, int platk, int plap, int enmdef, int enhp, int cost){
  plap -= cost;
  enhp -= ((plmatk * plmatk) + platk) / enmdef;
}

int randint() {
  int fd = open( "/dev/random", O_RDONLY ); //open file
  int *buff = malloc(sizeof(int)); //initialize buff by allocating mem
  read( fd, buff, sizeof(int) ); //write first 4 bytes to buff

  close(fd); //close

  return *buff; //dereference randomly generated number
}

void addToStruct( struct character *dude, char *stuff ){
  int w = 0;
  char * x;
  while ( w < 9 ){
    x = strsep(&stuff, ",");
    if (w == 0)
      dude -> name = x;
    else if (w == 1)
      dude -> hp = atoi(x);
    else if (w == 2)
      dude -> ap = atoi(x);
    else if (w == 3)
      dude -> atk = atoi(x);
    else if (w == 4)
      dude -> def = atoi(x);
    else if (w == 5)
      dude -> matk = atoi(x);
    else if (w == 6)
      dude -> mdef = atoi(x);
    else if (w == 7)
      dude -> initv = atoi(x);
    else
      dude -> friend = x;
    w++;
  }
}

void initialize( ) {  
  char ** gogojuice = (char **)malloc(sizeof(char*));
  char ** daddy = (char **)malloc(sizeof(char*));
  
  int fd = open( "Players.txt", O_RDONLY );
  char buff[1024];
  read( fd, buff, sizeof(buff) );
  close( fd );
  //printf("%s\n", buff);
  
  int i = 0;
  
  char * s = buff;
  //printf("hi\n");
  
  while( s ){
    daddy[i] = strsep(&s, "\n");
    i++;
  }
  printf("test1\n");
  int x = 0;
  for ( x; x < i - 1; x++ ){
    printf("%s\n", daddy[x]);
    if(x == 0){
      addToStruct( &man1, daddy[x] );
      party[x] = man1;
    }
    else if(x == 1){
      //printf("%s\n",daddy[x]);	    
      //printf("affirmative\n");
      addToStruct( &man2, daddy[x] );
      party[x] = man2;
    }
    else if(x == 2){
      //printf("%s\n",daddy[x]);	    
      //printf("affirmative\n");
      addToStruct( &man3, daddy[x] );
      party[x] = man3;
    }
    //gogojuice[x] = strsep(&daddy[x], ",");
    //printf("%s\n", gogojuice[x]);
  }
}

int main(){
  int isServer = -1;
  char b[2];
  while (isServer == -1){
    printf("Do you want to be a server (type s) or client (type c)?\n");
    fgets(b,sizeof(b),stdin);
    if (b[0] == 's')
      isServer = 1;
    else if (b[0] == 'c')
      isServer = 0;
    else
      isServer = -1;
  }

  if (isServer == 1){
    set(1);
    serve();
  }
  char k[100];
  char *args[2];
  args[0]= "client";
  
  if (isServer == 0){
    printf("Please enter IP address of server you would like to join\n");
    fgets(k,sizeof(k),stdin);
    args[1] = k;
    clien(1,args);
  }
	  
  
  //char * t = "Snowden,5,5,5,5,5,5,5,Edward";
  //addToStruct(&test,t); didnt work for some reason
  test.name = "Edward";
  test.hp = 5;
  test.ap = 5;
  test.atk = 5;
  test.def = 5;
  test.matk = 5;
  test.mdef = 5;
  test.initv = 5;
  test.friend = "Snowden";
  printf("%s\n\n", test.friend);
  
  initialize();
  printf("test2\n");
  printf("[1] name: %s; friend: %s\n", man1.name, man1.friend);
  printf("[2] name: %s; friend: %s\n", man2.name, man2.friend);
  printf("\n");
  //printf("%s\n", man1.friend);
  //printf("%s\n", man2.friend);
  int enemy = 3;
  int enemyd = 0;
  int player = 3;
  int playerd = 0;
  // make array with all classes
  //then array for ones in use
  struct character option[12];
  option[0] = man1;
  option[1] = man2;
  option[2] = man3;
  struct character using[3];
  int chosen = 0;
  while(1){
    if(!chosen){
      printf("Welcome\n");
      printf("Choose 3 characters with the corresponding number keys seperated by spaces\n");
      printf("(1)Gordon [Bad]\n");
      printf("(2)Percy [Decent stats]\n");
      printf("(3)Thomas [All-around high stats]\n");
      char class[266];
      fgets(class,sizeof(class),stdin);
      //using[0] = option[class[atoi(0)] -1];
      //using[1] = option[class[atoi(2)] -1];
      //using[2] = option[class[atoi(3)] -1];
      // printf("working: %s", using[0].atk);
      chosen ++;


    }

     
    int ai = randint() % 3;
    if(!enemy){
      printf("you win\n");
      return 0;
    }
    if(!player){
      printf("you lose\n");
      return 0;
    }
    char a[256];
    printf("Enemy health is: %d\n", enemy);
    //printf("Your health is: %d\n", player); 
    printf("Enter a to attack, enter s to cast spell, enter d to defend\n");
    fgets(a,sizeof(a),stdin);
    playerd = 0;
    if(a[0] == 'a'){
      printf("Which enemy?"); //gonna have an array of enemies to select who to attack
      
      if(enemyd == 1){
	printf("enemy defends attack\n");
	//at this point only gordon is attack for test purposes
	// also the 10 is relative at this point
	damage(man1.atk, test.def + 10, test.hp);
      }
      else{
	damage(man1.atk, test.def, test.hp);
      }
    }
    // we cant do magic attacks until we get the different spells we are going to use
    if(a[0] == 's'){
      if(enemyd == 1){
	printf("enemy defends spell\n");
      }
      else{
	enemy --;
      }
    }
    if(a[0] == 'd'){
      playerd ++; // implement further
    }

    // glitch sometimes no action is taken
    enemyd = 0;
    if(ai == 0){
      if(playerd == 1){
	//should randomly select an enemy
	printf("You defended enemy attack\n");
	damage(test.atk, man1.def + 10, man1.hp);	
      }
      else{
	printf("Enemy attacks\n");
	damage(test.atk, man2.def + 10, man1.hp);
      }
    }
    if(ai == 1){
      if(playerd == 1){
	printf("You defended enemy spell\n");
      }
      else{
	printf("Enemy casts spell\n");
	player --;
      }
    }
    if(ai == 2){
      printf("Enemy defends\n");
      enemyd ++;// implement further 
    }
    
    
    printf("------------------\n");
  
    
  }
  return 0;
}
