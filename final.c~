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


int randint() {
  int fd = open( "/dev/random", O_RDONLY ); //open file
  int *buff = malloc(sizeof(int)); //initialize buff by allocating mem
  read( fd, buff, sizeof(int) ); //write first 4 bytes to buff

  close(fd); //close

  return *buff; //dereference randomly generated number
}


int main(){
  int enemy = 3;
  int player = 3;
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
    if(a[0] == 'a'){
      enemy --;
    }
    if(a[0] == 's'){
      enemy --;
    }
    if(a[0] == 'd'){
      enemy = enemy; // implement further
    }

    // glitch sometimes no action is taken
    if(ai == 0){
      printf("Enemy attacks\n");
      player --;
    }
    if(ai == 1){
      printf("Enemy casts spell\n");
      player --;
    }
    if(ai == 2){
      printf("Enemy defends\n");// implement further 
    }
    
    
    printf("------------------\n");
  
    
}
  return 0;
}
