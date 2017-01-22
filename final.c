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
  while ( w < 8 ){
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
    else 
      dude -> initv = atoi(x);
    w++;
  }
}

void copystruct(struct character *s1, struct character *s2){
  s1 -> name = s2 -> name;
  s1 -> hp = s2 -> hp;
  s1 -> ap = s2 -> ap;
  s1 -> atk = s2 -> atk;
  s1 -> def = s2 -> def;
  s1 -> matk = s2 ->matk;
  s1 -> mdef = s2 ->mdef;
  s1 -> initv = s2 -> initv;
}

void initialize(char * c1, char * c2, char *c3) {  
  char ** gogojuice = (char **)malloc(sizeof(char*));
  char ** daddy = (char **)malloc(sizeof(char*));

  printf("c1: %s\n",c1);
  printf("c2: %s\n",c2);
  printf("c3: %s\n",c3);
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
  int z = 0;

  //printf("%s\n",strstr(daddy[1],"Gordon"));
  
  for ( x; x < i - 1; x++ ){
    if (strstr(daddy[x],c1) != NULL){
      printf("%s\n", daddy[x]);
      addToStruct( &man1, daddy[x] );
      z++;
    }
    else if (strstr(daddy[x],c2) != NULL){
      printf("%s\n", daddy[x]);
      addToStruct( &man2, daddy[x] );
      party[z] = man2;
      z++;
    }
    else if (strstr(daddy[x],c3) != NULL){
      printf("%s\n", daddy[x]);
      addToStruct( &man2, daddy[x] );
      party[z] = man3;
      z++;
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
    sendclient("sending basic message from server to client\n"); // by putting this here can send custom info from server to client (string only)
    set(1);
    serve();
    sdone();
    //set(0);
  }
  char k[100];
  char *args[2];
  args[0]= "client";
  
  if (isServer == 0){
    sendserv("custom message for server\n"); // allows you to send custom info from client to the server (string only)
    set1(1);
    clien(1,args);
    sdone1();
    //set1(0);
  }

  char t[] = "Edward,5,5,5,5,5,5,5";
  addToStruct(&test,t);

  int chosen = 0;
  
  while(1){
    if(!chosen){
      char c1[256];
      char c2[256];
      char c3[256];
      char class[266];
      char class2[266];
      printf("Welcome\n");

      int k = 0;
      while (k < 3){
	if (k == 0)
	  printf("\nChoose Your first character. Type the name\n");
	if (k == 1)
	  printf("\nChoose your second character. Type the name\n");
	if (k == 2)
	  printf("\nChoose Your third character. Type the name\n");
	
	//where we would need to list all the possible people, preety easy
	printf("Gordon [Bad]\n");
	printf("Percy [Decent stats]\n");
	printf("Thomas [All-around high stats]\n");
	if (k == 0)
	  fgets(class2,sizeof(class2),stdin); // this first fgets is getting something else strange, need to do twice	
	fgets(class,sizeof(class),stdin);
	class[strcspn(class, "\n")] = 0;
	if (k == 0)
	  strcpy(c1,class);
	if (k == 1)
	  strcpy(c2,class);
	if (k == 2)
	  strcpy(c3,class);
	k++;
      }
      printf("we made it here\n");
      initialize(c1,c2,c3);
      
      chosen = 1;

      if (isServer){
	sendclient(c1);
	printf("what is up %s\n",serve());
      }    
      else if(!isServer){
	sendserv(c1);
	clien(1,args);
	printf(gotvalue1());
      }
      
      if (isServer){
	
	
	printf("what is up %s\n",gotvalue());
      }    
      }
  else{
    break;
  }
      /*int ai = randint() % 3;
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
	printf("Which enemy?\n"); //gonna have an array of enemies to select who to attack
      
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
  
    
      }*/
  }
  return 0;
}
