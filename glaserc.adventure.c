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


int main(){
	int i, j, k, q;
	char myname[33] = "glaserc.rooms.";
	char dirname[66];
	const char *title[10];
	int n = 10;
	int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,};
	randArr(arr, n);
	
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
	
	
	char fullNames[7][200];
	
	for (i = 0; i <= 6; i++){
		
		char file[80];
		
		sprintf(file, "./%s/%s", dirname, title[i]);
				strcpy(fullNames[i], file);
		FILE *fp;
		fp = fopen(file, "a");
		printf("file%d: %s\n",i, file);
		
		if (fp == 0){
			fprintf(stderr, "Could not open %s\n", file);
			exit(1);
		}
			
		/*Putting the room name inside the text*/
		fprintf(fp, "\nROOM NAME: %s\n", title[i]);
		printf("\nROOM NAME: %s\n", title[i]);
		/*Assinging Connectionsrand */
			q = 0;
			q = rand() % 4;
			q = q+3;
			printf("This room will get %d connections\n", q);
			k = 1;
		
			if(i == 0){
				for (k =1; k <= q; k++){
					fprintf(fp, "CONNECTION %d: %s\n",k, title[i+k]);
					printf("CONNECTION %d: %s\n",k, title[i+k]);
				}	
			}
			
			else if( i == 6){
				for (k =1; k <= q; k++){
					
					fprintf(fp, "CONNECTION %d: %s\n",k, title[i-k]);
					printf("CONNECTION %d: %s\n",k, title[i-k]);
				}
			}
			
			else {
				if (i <= 3){
					k = 1;
					fprintf(fp, "CONNECTION %d: %s\n",k, title[i-k]);
					fprintf(fp, "CONNECTION %d: %s\n",(k+1), title[i+k]);
					
					printf("CONNECTION %d: %s\n",k, title[i-k]);
					printf("CONNECTION %d: %s\n",(k+1), title[i+k]);
						for (k =3; k <= q; k++){
							
							fprintf(fp, "CONNECTION %d: %s\n",k, title[i+k]);
							printf("CONNECTION %d: %s\n",k, title[i+k]);
						}
				}
				
				if(i >= 4){
					k = 1;
					fprintf(fp, "CONNECTION %d: %s\n",k, title[i-k]);
					fprintf(fp, "CONNECTION %d: %s\n",(k+1), title[i+k]);
					
					printf("CONNECTION %d: %s\n",k, title[i-k]);
					printf("CONNECTION %d: %s\n",(k+1), title[i+k]);
					
					
					for (k =3; k <= q; k++){
						if(i - k <= 0){
							printf("CONNECTION %d: %s\n",k, title[k - i]);
						}
						else{
							fprintf(fp, "CONNECTION %d: %s\n",k, title[i-k]);
							printf("CONNECTION %d: %s\n",k, title[i-k]);
						}
						
					}
				}	
			}
					
		/*Assign a room type */
		if (i == 0){
		fprintf(fp, "Room TYPE: START_ROOM\n", title[i]);
		printf("Room TYPE: START_ROOM\n", title[i]);
		
		}
		else if(i == 6){
			fprintf(fp, "Room TYPE: END_ROOM\n", title[i]);
			printf("Room TYPE: END_ROOM\n", title[i]);
		}
		else{
			fprintf(fp, "Room TYPE: MID_ROOM\n\n", title[i]);
			printf("Room TYPE: MID_ROOM\n\n", title[i]);
		}
		
		fclose(fp);
	}
	
	/*fullNames[7][200];*/
	printf("-----------------BUFFER-----------------\n");
	printf("full name: %s\n\n", fullNames[5]);
	
	FILE *newFile;
	int numCount;
		newFile = fopen(fullNames[5], "r");
	if (newFile){
			while((numCount = getc(newFile))!=EOF)
			putchar(numCount);
		}
		
		
	fclose (newFile);
	
		
		
exit(0);
	
}
