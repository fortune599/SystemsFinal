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
  int atk;
  int def;
  int matk;
  int mdef;
  int spd;
  char** friends;
};

int randint() {
  int fd = open( "/dev/random", O_RDONLY ); //open file
  int *buff = malloc(sizeof(int)); //initialize buff by allocating mem
  read( fd, buff, sizeof(int) ); //write first 4 bytes to buff

  close(fd); //close

  return *buff; //dereference randomly generated number
}


int main(){
  int enemy = 3;
  int enemyd = 0;
  int player = 3;
  int playerd = 0;
   while(1){
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
