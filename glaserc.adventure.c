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
	
	char file1[80];
	char room1[33] = "bunker.txt";
	
	sprintf(file1, "./%s/%s", dirname, room1);
	int fd1 = open(file1, O_RDWR | O_CREAT, perm);
		
		printf("file1: %s\n", file1);
		if (fd1 == -1)
			{
			fprintf(stderr, "Could not open %s\n", room1);
			exit(1);
			}
		else
			printf("start with roome one\n");
	
	
	
	

	exit(0);
}
