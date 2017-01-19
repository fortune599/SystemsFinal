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
struct character questioning;

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
    }
    else if(x == 1){
      //printf("%s\n",daddy[x]);	    
      //printf("affirmative\n");
      addToStruct( &man2, daddy[x] );
    }
    //gogojuice[x] = strsep(&daddy[x], ",");
    //printf("%s\n", gogojuice[x]);
  }
}

int main(){
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
  option[2] = questioning;
  struct character using[3];
  int chosen = 0;
  while(1){
    if(!chosen){
      printf("Welcome\n");
      printf("Choose 3 classes with the corresponding number keys seperated by spaces\n");
      printf("(1)Gordon\n");
      printf("(2)Percy\n");
      printf("(3)????\n");
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
    printf("Your health is: %d\n", player); 
    printf("Enter a to attack, enter s to cast spell, enter d to defend\n");
    fgets(a,sizeof(a),stdin);
    playerd = 0;
    if(a[0] == 'a'){
      if(enemyd == 1){
	printf("enemy defends attack\n");
      }
      else{
	enemy --;
      }
    }
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
	printf("You defended enemy attack\n");
      }
      else{
	printf("Enemy attacks\n");
	player --;
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
