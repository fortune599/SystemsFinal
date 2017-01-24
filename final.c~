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

//#include "networking.c"
//#include "networking.h"
//#include "server.c"
//#include "client.c"
#include "character.c"

struct character man1;
struct character man2;
struct character man3;

struct character en1;
struct character en2;
struct character en3;

struct character party[3];
struct character opponent[3];



//test case
struct character test;
char  save[1000];


void getvalue(){
  int fd = open( "store.txt", O_RDONLY);
  read(fd,save,sizeof(save));
  close(fd);
  //printf("wtf %s\n", save);
}


void setValue(int * stat, int newVal){
  *stat = newVal;
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
  char *x;
  while ( w < 8 ){
    x = strsep(&stuff, ",");
    if (w == 0){
      //      printf("this is going in: %s\n", x);
      dude -> name = x;
    }
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
  //printf("this is coming out: %s\n", dude->name);
}

void copystruct(struct character *s1, struct character *s2){
  s1->name = s2->name;
  s1->hp = s2->hp;
  s1->ap = s2->ap;
  s1->atk = s2->atk;
  s1->def = s2->def;
  s1->matk = s2->matk;
  s1->mdef = s2->mdef;
  s1->initv = s2->initv;
  //printf("%s %s\n", s1->name, s2->name);
}

int myCharacter(char * name){
  int i;
  for(i = 0; i < 3; i++){
    if ( strstr( party[i].name, name ) != NULL)
      return 1;
  }
  return 0;
}

void initialize(char * c1, char * c2, char *c3, struct character array[], struct character a, struct character b, struct character c){
  char ** daddy = (char **)malloc(sizeof(char*));

  printf("-%s\n",c1);
  printf("-%s\n",c2);
  printf("-%s\n",c3);
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

  int x = 0;
  int z = 0;
 
  for ( x; x < i - 1; x++ ){
    if (strstr(daddy[x],c1) != NULL){
      //      printf("%s\n", daddy[x]);
      addToStruct( &a, daddy[x] );
      //      printf("%s\n", a.name);
      array[z] = a;
      z++;
    }
    else if (strstr(daddy[x],c2) != NULL){
      //      printf("%s\n", daddy[x]);
      addToStruct( &b, daddy[x] );
      //      printf("%s\n", b.name);
      array[z] = b;
      z++;
    }
    else if (strstr(daddy[x],c3) != NULL){
      //      printf("%s\n", daddy[x]);
      addToStruct( &c, daddy[x] );
      //      printf("%s\n", c.name);
      array[z] = c;
      z++;
    }
  }
}


int main(){
  printf("Do you want to play against AI? type y or n\n");
  char m[5];
  fgets(m,sizeof(m),stdin);
  //m[strcspn(m, "\n")] = 0;
  if (m[0] == 'y'){
 
    struct character player;

    player.name = "DonWalf";
    player.hp = 3750;
    player.ap = 1;
    player.atk = 100;
    player.def = 250;
    player.matk =1;
    player.mdef = 1;
    player.initv = 299;
    

    struct character enemy;

    enemy.name = "Suwamik";
    enemy.hp = 3500;
    enemy.ap = 1;
    enemy.atk = 150;
    enemy.def = 175.5;
    enemy.matk = 1;
    enemy.mdef = 1;
    enemy.initv = 250;
    
    //addToStruct(&enemy,"Suwamik,3500,1,275,175,1,1,250");
    
    while(1){
      int ai = randint() % 3;
      if(enemy.hp < 0){
	printf("you win\n");
	return 0;
      }
      if(player.hp < 0){
	printf("you lose\n");
	return 0;
      }
      char a[256];
      printf("Enemy health is: %d\n", enemy.hp);
      printf("Your health is: %d\n", player.hp); 
      printf("Enter a to attack, enter s to cast spell, enter d to defend\n");
      fgets(a,sizeof(a),stdin);
      if(a[0] == 'a'){
	if(ai == 2){
	  printf("enemy defends\n");
	  enemy.hp -= player.atk * 2 /1.5;
	}
	else{
	  printf("you attack\n");
	  enemy.hp -= player.atk * 2 - enemy.def;
	}
      }
      if(a[0] == 's'){
	if(ai == 2){
	  printf("enemy defends the spell\n");
	  enemy.hp -= player.atk * 4 - (1.5 * enemy.def);
	}
	else{
	  printf("you cast a powerful spell\n");
	  enemy.def -= player.atk *4;
	}
      }
      if(a[0] == 'd'){
	printf("your defense rises\n");
	player.def+=50; // implement further
      }

      // glitch sometimes no action is taken
      if(ai == 0){
	if(a[0] == 1){
	  printf("You defended enemy attack\n\n");
	  player.hp -= enemy.atk *2/ 1.5;
	}
	else{
	  printf("Enemy attacks\n");
	  player.hp-= enemy.atk * 2 -player.def;
	}
      }
      if(ai == 1){
	if(a[0] == 1){
	  printf("You defended enemy spell\n");
	  player.hp -= enemy.atk *4 - player.def;
	}
	else{
	  printf("Enemy casts spell\n");
	  player.hp -= enemy.atk * 4;
	}
      }
      if(ai == 2){
	printf("Enemy defends\n");
	enemy.def += 50;// implement further 
      }
    
    
    printf("------------------\n");
  
    
    }

  }
  else{
      
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
      //sendclient("sending basic message from server to client\n"); // by putting this here can send custom info from server to client (string only)
      set(1);
      serve();
      sdone();
      //set(0);
    }
    char k[100];
    char *args[2];
    args[0]= "client";
  
    if (isServer == 0){
      //sendserv("custom message for server\n"); // allows you to send custom info from client to the server (string only)
      char z[256];
      printf("Please enter the IP you wish to connect to\n");
      fgets(z,sizeof(z),stdin);
      z[strcspn(z, "\n")] = 0;
      args[1] = z;
      set1(1);
      clien(2,args);
      sdone1();
      //set1(0);
    }

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
	    printf("\nChoose your first character. Type the name:\n");
	  if (k == 1)
	    printf("\nChoose your second character. Type the name:\n");
	  if (k == 2)
	    printf("\nChoose your third character. Type the name:\n");
	
	  //where we would need to list all the possible people, preety easy
	  printCharac(c1,c2);
	  if (k == 0)
	    fgets(class2,sizeof(class2),stdin); // this first fgets is getting something else strange, need to do twice

	  int fd = open( "Players.txt", O_RDONLY );
	  char buff[1024];
	  read( fd, buff, sizeof(buff) );
	  close( fd );

	  strcpy(class, "antidisestablishmentarianism");

	  while ( strstr(buff, class) == NULL ){
	    printf("\nPlease type name only, exactly as seen:\n> ");
	    fgets(class,sizeof(class),stdin);
	    class[strcspn(class, "\n")] = 0;
	    //printf("%s\n", class);
	    //printf("%s\n", buff);
	  }

	  if (k == 0)
	    strcpy(c1,class);
	  if (k == 1)
	    strcpy(c2,class);
	  if (k == 2)
	    strcpy(c3,class);
	  k++;
	
	  printf("%s selected.\n", class);
	}
      
	chosen = 1;
	char e1[256];
	char e2[256];
	char e3[256];

	if (isServer){
	  sendclient(c1);
	  serve();//dies after this
	  strcpy(e1,gotvalue());
	  sendclient(c2);
	  serve();
	  strcpy(e2,gotvalue());
	  sendclient(c3);
	  serve();
	  strcpy(e3,gotvalue());
	  initialize(e1,e2,e3,opponent,en1,en2,en3);
	}
	else if(!isServer){
	  sendserv(c1);
	  clien(1,args);//dies after this
	  strcpy(e1,gotvalue1());
	  sendserv(c2);
	  clien(1,args);
	  strcpy(e2,gotvalue1());
	  sendserv(c3);
	  clien(1,args);
	  strcpy(e3,gotvalue1());
	  initialize(e1,e2,e3,opponent,en1,en2,en3);
	}
	initialize(c1,c2,c3,party,man1,man2,man3);
      
	//printf("party member #1: %s\n", party[0].name);
	//printf("party member #2: %s\n", party[1].name);
	//printf("party member #3: %s\n", party[2].name);
      }
      else{
	int myHP = 1;
	int enHP = 1;
	int curse;
	int turn = 0;
	struct character attacker;
	char commands[256];

	struct character everyone[6];
	int mymax = 0;
	int enmax = 0;
	int curse2;
	for (curse = 0; curse < 6; curse++){//sorting by initiative
	  for (curse2 = 0; curse2 < 3; curse2++){
	    if (party[curse2].initv > party[mymax].initv)
	      mymax = curse2;
	  }
	  for (curse2 = 0; curse2 < 3; curse2++){
	    if (opponent[curse2].initv > opponent[enmax].initv)
	      enmax = curse2;
	  }
	  if (party[mymax].initv > opponent[enmax].initv){
	    copystruct(&everyone[curse], &party[mymax]);
	    party[mymax].initv = -1;
	  }
	  else{
	    copystruct(&everyone[curse], &opponent[enmax]);
	    opponent[enmax].initv = -1;//sorry buddy
	  }
	}

	while (myHP > 0 && enHP > 0){
	  for(curse = 0; curse < 3; curse++){
	    myHP += party[curse].hp;
	  }
	  for(curse = 0; curse < 3; curse++){
	    enHP += opponent[curse].hp;
	  }
	  //game itself begins here
	  turn = turn % 6;
	  copystruct(&attacker, &everyone[turn]);

	  if (!isServer){//DELETE DIAGNOSTIC PRINTFS LATER
	    if (myCharacter(attacker.name)){
	      printf("this is a client character\n");
	      if ( strstr( everyone[(turn + 1) % 6].name, attacker.name ) != NULL ){//response here
		printf("the client gets next turn: (n)%s (c)%s\n", everyone[(turn + 1) % 6].name, attacker.name);
		respond(isServer, &enHP, args);
	      }//if the next character has the same name
	      else{//insert actions here
		act(isServer, &myHP, attacker, opponent, commands, args);
	      }
	    }//if it's the client's character
	    else{//response here
	      printf("this is not your character, client\n");
	      respond(isServer, &enHP, args);
	    }
	  }//if it's the client
	  else{
	    if (myCharacter(attacker.name)){
	      if ( strstr( everyone[(turn + 5) % 6].name, attacker.name ) != NULL ){//response here
		printf("the server got last turn: (n)%s (c)%s\n", everyone[(turn + 5) % 6].name, attacker.name);
		respond(isServer, &enHP, args);
	      }//if the previous character has the same name
	      else{//insert actions here
		act(isServer, &myHP, attacker, opponent, commands, args);
	      }
	    }//if it's the server's character
	    else{//response here
	      printf("this is not your character, server\n");
	      respond(isServer, &enHP, args);
	    }
	  }//if it's the server
	  turn++;
	}//end HP while loop
	if (myHP > 0){
	  printf("YOU WIN\n");
	  break;
	}
	else{
	  printf("OPPONENT WON\n");
	  break;
	}
      }
    }
  }
  return 0;
}
