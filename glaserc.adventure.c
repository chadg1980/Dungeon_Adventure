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
	
	/*folder permissions 777, in octal*/
	char chMod[] = "0777";
	int octal = strtol(chMod, 0, 8);

	return octal;
}


int main(){
	
	/*get the permissions for the directory*/	
	int perm = permissions();
	
	
	
	/*------------get PID as int then int to string-----------*/
	int myPid = getpid();
	char buffer[33];
	snprintf(buffer, 33, "%d", myPid);
	printf("buffer is: %s\n", buffer);
	
	/*------------append pid to dirname--------*/
	strcat(dirname, buffer);
	
	
	/*make the directory, print out dir name and pid name*/
	mkdir(folder, perm);
	printf("dirname: %s\n", folder);
	printf("PID: %d\n", myPid);

	exit(0);
}
