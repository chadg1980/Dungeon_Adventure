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

/*Helper function for randomize*/
void swap (int *a, int *b){

	int temp = *a;
	*a = *b;
	*b = temp;
}
/*function to randomize the rooms*/
void randArr(int arr[], int n){
	int j, k;
	
	( time(NULL)); 
	for (j = n-1; j > 0; j--){
		k = rand() % (j+1);
		swap(&arr[j], &arr[k]);
	}
}

int permissions(){
	/*I got a hint about file permission being octal
	http://bytes.com/topic/c/answers/459585-string-octal */
	
	/*folder permissions 770, in octal*/
	char chMod[] = "0770";
	int octal = strtol(chMod, 0, 8);

	return octal;
}


int main(){
	
	/*seeding random numbers*/
	( time(NULL)); 
	
	int i, j, k, q;
	char dirname[33] = "glaserc.rooms.";
	const char *title[10];
	int n = 10;
	int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,};
	randArr(arr, n);
	
	/*ger permissions (octal)*/
	int perm = permissions();
	
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
	title[arr[0]] = "Bunker";
	title[arr[1]] = "Stairway";
	title[arr[2]] = "Tunnel";
	title[arr[3]] = "Cavern";
	title[arr[4]] = "Cliff";
	title[arr[5]] = "Crystal Room";
	title[arr[6]] = "Spring Lake";
	title[arr[7]] = "Toadstool";
	title[arr[8]] = "Gully";
	title[arr[9]] = "The Dark";
	
	/*creating files*/
	for (i = 0; i < 6; i++){
		
		char file[80];
			
		sprintf(file, "./%s/%s", dirname, title[i]);
		FILE *fp;
		fp = fopen(file, "a");
		printf("file%d: %s\n",i, file);
		
		if (fp == 0){
			fprintf(stderr, "Could not open %s\n", file);
			exit(1);
		}
		/*Putting the room name inside the text*/
		fprintf(fp, "\nROOM NAME: %s\n", title[i]);
		
		/*Assinging Connectionsrand */
		
			q = rand() % 4;
			q = q+3;
		for (k =1; k < q; k++){
			if(i == 0){
			fprintf(fp, "CONNECTION %d: %s\n",k, title[i+k]);
						
			}
			else if( i == 5){
			fprintf(fp, "CONNECTION %d: %s\n",k, title[i-k]);
			}
			else {
				if (i < k)
					fprintf(fp, "CONNECTION %d: %s\n",k, title[k-i]);
				if(i >= k)
					fprintf(fp, "CONNECTION %d: %s\n",k, title[i+k]);
			}
			
			
			
		}
		
				
		/*Assign a room type*/
		if (i == 0){
		fprintf(fp, "Room TYPE: START_ROOM\n", title[i]);
		}
		else if(i == 5){
			fprintf(fp, "Room TYPE: END_ROOM\n", title[i]);
		}
		else{
			fprintf(fp, "Room TYPE: MID_ROOM\n\n", title[i]);
		}
		
		fclose(fp);
	}
	
	
exit(0);
	
}
