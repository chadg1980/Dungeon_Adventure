/*
*Chad H Glaser
*CS 344
*Winter 2015
*Dungeon Adventure Game
*
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <string.h>
#include <time.h>

int permissions(){
	/*I got a hint about file permission being octal
	http://bytes.com/topic/c/answers/459585-string-octal */
	
	/*folder permissions 770, in octal*/
	char chMod[] = "0770";
	int octal = strtol(chMod, 0, 8);

	return octal;
}


int main(){
	
	/*get the permissions for the directory*/	
	int i;
	int perm = permissions();
	char dirname[33] = "glaserc.rooms.";
	
	/*------------get PID as int then int to string-----------*/
	int myPid = getpid();
	char buffer[33];
	snprintf(buffer, 33, "%d", myPid);
	printf("buffer is: %s\n", buffer);
	
	/*------------append pid to dirname--------*/
	strcat(dirname, buffer);
	mkdir(dirname, perm);
	
	
	/*Print for error checking*/
	printf("dirname: %s\n", dirname);
	printf("PID: %d\n", myPid);
	
	/*Starting with file creation*/
	/*room names*/
	
	
	for (i = 0; i < 6; i++){
		char roomName[80];
		char file[80];
		sprintf(roomName, "room%d.txt", i);
		printf ("%s\n", roomName); 
		
	sprintf(file, "./%s/%s", dirname, roomName);
	FILE *fp;
	fp = fopen(file, "a");
		
		printf("file%d: %s\n",i, file);
		if (fp == 0)
			{
			fprintf(stderr, "Could not open %s\n", file);
			exit(1);
			}
		
		
		fclose(fp);
			
	}
	
	
exit(0);
	
}
