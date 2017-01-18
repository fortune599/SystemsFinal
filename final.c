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
  int itv;
  char* friend;
};

struct character Gordon;
struct character Percy;

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

/*void initialize( char ** daddy ) {
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
  printf("ssdasd\n");
  printf("%s\n", *s);
  
  int x = strlen(*daddy);
  for ( x; x > 0; x-- ){
    printf("%d\n", x);
    printf("%s\n", daddy[x]);
  }
  }*/

/*void initialize(){
  int fd = open( "Players.txt", O_RDONLY );
  char buff[1024];
  read( fd, buff, sizeof(buff) );
  close(fd);
  printf("%s\n", buff);
  char ** b = (char **)(malloc(sizeof(char *)));
  int w = 0;
  char * s = buff;
  printf("cool\n"); 
  while(s){
    b[w] = strsep(&s, "\n");
    printf("%s\n", strsep(&s, "\n"));
    w ++;
  }
  printf("cool\n"); 
  printf("%s\n", b[0]);
  printf("%s\n", b[1]);
  char ** z = (char **)(malloc(sizeof(char *)));
  int y = 0;
  char * v = b;
  while(v){
    int pl = 0;
    while(v[y]){
      z[y] = strsep(&v, ",");
      y ++;

    y  ++;
    
  // int i = 0;
  //while(b[i]){
  //int f = 0;
  //while(b[i][f]){
  //
  //  f ++;
  //}

  //i ++;
}
*/ 



/*void parse(char * a, char * spliter){
  if(a[0] == NULL){
    char ** b = (char **)(malloc(sizeof(char *)));
    int w = 0;
    char * s = b;
    while(s){
      b[w] = strsep(&s, spliter);
      //printf("%s\n", strsep(&s, ";"));
      w ++;
    }
    int i = 0;
    while(b[i], ","){
      parse(b[i], ",");
      i ++;
    }
  }

  else{
    char ** b = (char **)(malloc(sizeof(char *)));
    int w = 0;
    char * s = a;
    while(s){
      b[w] = strsep(&s, spliter);
      //printf("%s\n", strsep(&s, ";"));
      w ++;
    }

    int dw = 0;
    while(b[dw]){
      if(dw == 0){
	setValue(&Gordon.name, b[dw]);
      }
      if(dw == 1){
	setValue(&Gordon.hp, atoi(b[dw]));
      }
      if(dw == 2){
	setValue(&Gordon.ap, atoi(b[dw]));
      }
      if(dw == 3){
	setValue(&Gordon.atk, atoi(b[dw]));
      }
      if(dw == 4){
	setValue(&Gordon.def, atoi(b[dw]));
      }
      if(dw == 5){
	setValue(&Gordon.matk, atoi(b[dw]));
      }
      if(dw == 6){
	setValue(&Gordon.mdef, atoi(b[dw]));
      }
      if(dw == 7){
	setValue(&Gordon.itv, atoi(b[dw]));
      }
      if(dw == 8){
	setValue(&Gordon.friend, b[dw]);
      }

*/



char * initclass(int i){
  char * a[12][9];
  if(i == 0){
    a[0][0] = "Gordan";
    a[0][1] = "1";
    a[0][2] = "1";
    a[0][3] = "1";
    a[0][4] = "1";
    a[0][5] = "1";
    a[0][6] = "1";
    a[0][7] = "1";
    a[0][8] = "Percy";
  }
  return a;
}


int main(){

  //char *a = intitclass(0);
  // printf("%s\n", a[0][0]);
  //setValue(&Gordon.atk, 30);
  //parse(NULL, '\n');
  // printf("%d\n",Gordon.atk);
  //char ** daddy = (char **)malloc(sizeof(char*));
  //char a [1000];
  //initialize();
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
