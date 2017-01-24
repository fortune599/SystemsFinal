# SystemsFinal
In-Terminal Battle Simulator

Fortune Soleil, Jackson Morgan, Suwamik Paul

The purpose of our project was to be a battle simulator. The users can choose three characters to add to their party. Then the server and client exchange the party information. The characters choose an action (attack, defend, ability or concede). This continues till all the characters in one user's party has 0 health.

To compile this program, simply make. To run make run. 

The files that are included in this repository are final.c, client.c, server.c, networking.c, networking.h, character.c, store.txt, and Players.txt, DESIGN.TXT, DEVLOG.TXT, and of course the README.md


To run this program, make and run project. It will ask you if you want to battle an a.i. or not. If you do then select y. This will bring you to a simplified one on one battle in which you can attack, defend, or cast a spell. If you don't want to battle a.i., click n. If you click n it will ask you if you want to be a server or a client. This version lacks the ability to choose an i.p. address. We apologize but our brains stopped functioning at around 4 a.m. Thus, you run the program twice and the loopback i.p. adress is automatically called, simulating network play. 



After the connection has been established, the server and client will both be given the chance to select 3(three) different characters to add to their party. The character with the highest inivitivate would be allowed to perform an action first. If you misspell, type again. Once both sides pick three characters each side is notified of the other teams characters and the game begins. Unfortunately, there is not much more you can do. If you type Concede, it will signal to the enemy that he has won and signal to you that you have lost. If you click enter or attack the turn will keep switching between sides depending on initiative. 


While we hoped to fully implement many more features such as attack and defend we ran into a major unforseen roadblock the day before the assignment was due. Basically, an issue occurred in which sent messages over networking were altering the name variable in the character struct. We spent many hours trying to fix this but could not identify the problem. We know that messages are sent and received correctly, so this seemed odd. It was especially odd because when info was accidently altered we weren't even reading the sent messages which were placeholders, we were instead ignoring them. We soon realized that this was not a minor problem as it made it impossible for us to identify and modify unique classes as their names had been changed to random characters. While we wrote code to try and implement attack and defend, we could never test or develop it due to this hurdle. Eventually we focused on finishing other parts of the project and getting at least a little bit of sleep as some of our group members have finals. Obviously, we are dissapointed by the outcome of this project. We would have liked nothing more than to hand in a complete working program, which has been the case for each member in each of their other final projects. However, even though there are many issues with the code, we are proud of the work we did, the many hours we spent, and the amount of information we learned. We hope you will be understanding. 
