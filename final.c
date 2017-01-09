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




int main(){
  int enemy = 3;
  int player = 70; 
   while(1){
    if(!enemy){
      printf("you win\n");
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
      enemy = enemy;
    }

  player --;
  printf("Enemy attacks\n");
    
}
  return 0;
}
