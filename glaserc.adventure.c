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

struct thisRoom{
	char roomName[20];		//just the name of the room
	char fullName[80];		//full path and file name of each room file
	
	int type;				//type string in file, but int for game. (1 start, 3 finish, 2 mid)
	char connection[6][80];	//Connection 1 to 6
	
};



/*Helper function to randomize*/
void swap (int *a, int *b){

	int temp = *a;
	*a = *b;
	*b = temp;
}
/*function to randomize the rooms*/
void randArr(int arr[], int n){
	int j, k;
	
	srand( time(NULL)); 
	for (j = n-1; j > 0; j--){
		k = rand() % (j+1);
		swap(&arr[j], &arr[k]);
	}
}
/*double check the numbers are random
void printArr( int arr[], int n){
	int i;
	for (i = 0; i < n; i++)
		printf("num: %d, ", arr[i]);
	printf("\n");
}
*/
int permissions(){
	/*I got a hint about file permission being octal
	http://bytes.com/topic/c/answers/459585-string-octal */
	
	/*folder permissions 770, in octal*/
	char chMod[] = "0770";
	int octal = strtol(chMod, 0, 8);

	return octal;
}

/*-------------------MAIN STARTS HERE-------------------------*/
int main(){
	int i;
	char myname[33] = "glaserc.rooms.";
	char dirname[66];
	int n = 10;
	int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,};
	randArr(arr, n);
	int start = 0;
	int mid = 0;
	int	end = 0;
	/*start the struct of 10 rooms*/
	struct thisRoom room[10];
		for(i = 0; i <10; i++){
	struct thisRoom room[i];
	}
	
	
	/* to check, must uncomment the function also
	printArr(arr, n);*/
	
	/*get permissions (octal)*/
	int perm = permissions();
	
	/*------------get PID as int then int to string-----------*/
	int myPid = getpid();
	char buffer[33];
	snprintf(buffer, 33, "%d", myPid);
	printf("buffer is: %s\n", buffer);
	
	/*---------------append pid to dirname--------------------*/
	/*strcat(dirname, buffer);*/
	sprintf(dirname, "%s%s",myname, buffer);
	mkdir(dirname, perm);
	
	
	/*Print for error checking Delete before handing in*/
	printf("dirname: %s\n", dirname);
	printf("PID: %d\n", myPid);
	
	/*-----------Starting with file creation----------*/
	
	/*room names, the array numbers are random each run of the program*/
	/*Names based on Seahawks schedule*/
	sprintf(room[arr[0]].roomName, "Green Bay");
	sprintf(room[arr[1]].roomName, "San Diego");
	sprintf(room[arr[2]].roomName, "Denver");
	sprintf(room[arr[3]].roomName, "Washington");
	sprintf(room[arr[4]].roomName, "Dallas");
	sprintf(room[arr[5]].roomName, "Carolina");
	sprintf(room[arr[6]].roomName, "Arizona");
	sprintf(room[arr[7]].roomName, "St Louis");
	sprintf(room[arr[8]].roomName, "Oakland");
	sprintf(room[arr[9]].roomName, "New York");
	
	/*print out the rooms, so I know the order, comment out for final product*/
	for (i = 0; i < 10; i++){
	
	printf("Thisroom: %s\n", room[i].roomName);
	}
	
	/*make the files*/
	for( i = 0; i < 7; i++){
		/*file is recreated each iteration*/
		char localFile[80];
		FILE *fpoint;
		int k, q;
		
		sprintf(room[i].fullName, "./%s/%s", dirname, room[i].roomName);
			//strcpy(localFile, room[i].fullName);
		
		fpoint = fopen(room[i].fullName, "a");
		if (fpoint == 0){
			fprintf(stderr, "Could not open %s\n", room[i].fullName);
			exit(1);
		}
		printf("file: %s, open \n", room[i].fullName);
		
		/*write the room name to a file*/
		fprintf(fpoint, "ROOM NAME: %s\n", room[i].roomName); 
		
		/*Assign Connections*/
			/*room i, connection k*/
		q = rand() %4 + 3;
		for(k = 1; k <= q; k++){	
			if( (i + k) < 6){
					sprintf(room[i].connection[k], room[i+k].roomName); 
					fprintf(fpoint, "CONNECTION %d: %s\n", k, room[i+k].roomName);
					printf("CONNECTION %d: %s\n", k, room[i+k].roomName);
				}
			else if ((i - k) >= 0){
					sprintf(room[i].connection[k], room[i-k].roomName); 
					fprintf(fpoint, "CONNECTION %d: %s\n", k, room[i-k].roomName);
					printf("CONNECTION %d: %s\n", k, room[i-k].roomName);
			}
			else{
					sprintf(room[i].connection[k], room[k-i].roomName); 
					fprintf(fpoint, "CONNECTION %d: %s\n", k, room[k-i].roomName);
					printf("CONNECTION %d: %s\n", k, room[k-i].roomName);
			}
		
		}
		/*assigning room type(pseudo random)*/
			int w = 0;
			w = rand() % 3 + 1;
			if( w == 1){
				if(start == 0){
					fprintf(fpoint, "ROOM TYPE: START_ROOM\n");
					printf("ROOM TYPE: START_ROOM\n");
					room[i].type = 1;
					start++;
				}
				else
					w++;
			}
			if( w ==3){
				if(end == 0){
					fprintf(fpoint, "ROOM TYPE: END_ROOM\n");
					printf("ROOM TYPE: END_ROOM\n");
					room[i].type = 3;
					end++;
				}
				else
					w--;
			}
			if (w == 2){
				if (mid <= 5){
					fprintf(fpoint, "ROOM TYPE: MID_ROOM\n");
					printf("ROOM TYPE: MID_ROOM\n");
					room[i].type = 2;
					mid++;
				}
				else if(start == 0){
					fprintf(fpoint, "ROOM TYPE: START_ROOM\n");
					printf("ROOM TYPE: START_ROOM\n");
					room[i].type = 1;
					start++;
				}
				else{
					fprintf(fpoint, "ROOM TYPE: END_ROOM\n");
					printf("ROOM TYPE: END_ROOM\n");
					room[i].type = 3;
					end++;
				}
			}
			
		
		fclose(fpoint);
	}
	
	
		
exit(0);
	
}
