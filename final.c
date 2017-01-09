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
  while(1){
    if(!enemy){
      printf("you win\n");
      return 0;
    }
    char a[256];
    printf("Enemy health is: %d\n", enemy); 
    printf("Enter a to attack, enter s to cast spell, enter d to skip turn\n");
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
    
  }
  return 0;
}
