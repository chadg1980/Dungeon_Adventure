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
	char connection[10][80];	//Connection 1 to 6
	int conCount;
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
	
	
	for (j = n-1; j > 0; j--){
		k = rand() % (j+1);
		swap(&arr[j], &arr[k]);
	}
}

void AssignRoom(int arr[], int n){
	int j, k;
	
	
	for (j = n-1; j > 0; j--){
		k = rand() % (j+1);
		swap(&arr[j], &arr[k]);
	}
}


/*double check the numbers are random*/
void printArr( int arr[], int n){
	int i;
	for (i = 0; i < n; i++)
		printf("num: %d, ", arr[i]);
		printf("\n");
}

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
		srand( time(NULL)); 
		int myPid = getpid();
		char buffer[33];
		int perm;
		int i;
		char myname[33] = "glaserc.rooms.";
		char dirname[66];
		int n = 10;
		int arr[] = {10, 1, 2, 3, 4, 5, 6, 7, 8, 9,};
		randArr(arr, n);
		int start = 0;
		int mid = 0;
		int	end = 0;
		
		char curRoomFile[255];
		char playBuffer[255];
		char conCons[255];
		char nextCity[255];
		
		char conString[255];
		int lob;
		int counter;
		int x, len;
		int checker;
		char inFileCon[10][255];
		int steps = 0;
		char path[255][255];
		
		
		
		
		/*start the struct of 10 rooms*/
		struct thisRoom room[10];
			for(i = 1; i <=10; i++){
				struct thisRoom room[i];
			}
		
		
		/* to check, must uncomment the function also
		printArr(arr, n);*/
		
		/*get permissions (octal)*/
		perm = permissions();
		
		/*------------get PID as int then int to string-----------*/
		
		snprintf(buffer, 33, "%d", myPid);
		/*printf("buffer is: %s\n", buffer);*/
		
		/*---------------append pid to dirname--------------------*/
		/*strcat(dirname, buffer);*/
		snprintf(dirname, sizeof(myname)+sizeof(buffer)+1,  "%s%s",myname, buffer);
		mkdir(dirname, perm);
		
		
		/*Print for error checking Delete before handing in
		printf("dirname: %s\n", dirname);
		printf("PID: %d\n", myPid);
		*/
		
		/*-----------Starting with file creation----------*/
		
		/*room names, the array numbers are random each run of the program*/
		/*Names based on Seahawks schedule*/
		snprintf(room[arr[0]].roomName, 10, "Green Bay");
		snprintf(room[arr[1]].roomName, 10, "San Diego");
		snprintf(room[arr[2]].roomName, 7,  "Denver");
		snprintf(room[arr[3]].roomName, 11, "Washington");
		snprintf(room[arr[4]].roomName, 7,  "Dallas");
		snprintf(room[arr[5]].roomName, 9,  "Carolina");
		snprintf(room[arr[6]].roomName, 8,  "Arizona");
		snprintf(room[arr[7]].roomName, 9,  "St Louis");
		snprintf(room[arr[8]].roomName, 8,  "Oakland");
		snprintf(room[arr[9]].roomName, 9,  "New York");
	
		/*start the connection count at 0*/
		for (i = 1; i <= 10; i++){
			
			room[i].conCount = 0;
			/*printf("This roomname: %s\n", room[i].roomName);*/
		}
		
		/*assign the room connections*/
		for(i = 1; i <=7; i++){
			
			int AssignRoom[] = {1, 2, 3, 4, 5, 6, 7};
			int c= 7;
			randArr(AssignRoom, c);
			
			int kk;
			int num;
			int k, l, q, connections, ret, REVconnections, Rret;
			
			/* q is the number of connections 3 to 6*/	
			q = rand() %4 + 3;
			
			/*inner loop*/
			for(k = 0; k <= q; k++){
				
				ret = 99;
				num = AssignRoom[k];
				
				/*check to see if there is already a connection*/
				connections = room[i].conCount;
				for(l = 1; l <= connections; l++){
					ret = strcmp(room[i].connection[l], room[num].roomName);
					if(ret == 0){
						/*printf("already connected\n");*/
						break;
					}		
				}
				
				/*check the connection count, if the room already has 6 connections, skip*/
				if(room[i].conCount >=6){
					/*printf("connections maxed\n");*/
					k = q;
				}
				/*If there is already a connection*/
				else if(ret == 0){
					/*printf("do nothing\n");*/
					}
				/*if the connection is trying to connect to itself*/
				else if (strcmp(room[num].roomName, room[i].roomName) == 0){
					/*Check if the room is going to assign itself as a connection*/
					}
				/*Good to make a connection*/
				else{
					/*add the connection to the list of connections*/
					room[i].conCount++;
					snprintf(room[i].connection[room[i].conCount], sizeof(room[num].roomName),
											room[num].roomName); 
					/*
					printf("%s, connects with ----->",room[i].roomName);
					printf("CONNECTION %d: %s\n", room[i].conCount, room[num].roomName);
					*/
					
					/*reverse link*/
					kk = room[num].conCount;
				
					/*check to see if there is already a connection*/
					REVconnections = room[num].conCount;
					for(l = 1; l <= REVconnections; l++){
						ret = strcmp(room[num].connection[l], room[i].roomName);
						if(Rret == 0){
							/*printf("RETURN..already connected\n");*/
							break;
						}		
					}
					
					if ((kk >= 6) || Rret == 0){
						/*printf("connections maxed out\n");*/
						break;
					}
					else{
					
					kk++;
					room[num].conCount++;
					snprintf(room[num].connection[kk], sizeof(room[i].roomName), room[i].roomName); 
					/*
					printf("REVERSE: %s  ------>", room[num].roomName);
					printf("CONNECTION %d: %s\n", room[num].conCount, room[i].roomName);
					*/
					
					}
				}
			}
		}
		
		/*make the files*/
		for( i = 1; i <= 7; i++){
		
			int w;
			int j, cons;
			/*file is recreated each iteration*/
			FILE *fpoint;
					
			snprintf(room[i].fullName, sizeof(dirname) 
										+ sizeof(room[i].roomName) +1, "./%s/%s", dirname, room[i].roomName);
				
			
			fpoint = fopen(room[i].fullName, "a");
				
			if (fpoint == 0){
				fprintf(stderr, "Could not open %s\n", room[i].fullName);
				exit(1);
			}
			
			
			/*write the room name to a file*/
			fprintf(fpoint, "ROOM NAME:%s\n", room[i].roomName); 
			
			
			/*Assign Connections*/
			cons = room[i].conCount;
			for(j = 1; j <= cons; j++)
				fprintf(fpoint, "CONNECTION %d:%s\n", j, room[i].connection[j]);
			
			
				/*assigning room type(pseudo random)*/
				w = rand() % 3 + 1;
				if( w == 1){
					if(start == 0){
						fprintf(fpoint, "ROOM TYPE:START_ROOM\n");
						/*printf("ROOM TYPE: START_ROOM\n");*/
						room[i].type = 1;
						start++;
					}
					else
						w++;
				}
				if( w ==3){
					if(end == 0){
						fprintf(fpoint, "ROOM TYPE:END_ROOM\n");
						/*printf("ROOM TYPE: END_ROOM\n");*/
						room[i].type = 3;
						end++;
					}
					else
						w--;
				}
				if (w == 2){
					if (mid <= 5){
						fprintf(fpoint, "ROOM TYPE:MID_ROOM\n");
						/*printf("ROOM TYPE: MID_ROOM\n");*/
						room[i].type = 2;
						mid++;
					}
					else if(start == 0){
						fprintf(fpoint, "ROOM TYPE:START_ROOM\n");
						/*printf("ROOM TYPE: START_ROOM\n");*/
						room[i].type = 1;
						start++;
					}
					else{
						fprintf(fpoint, "ROOM TYPE:END_ROOM\n");
						/*printf("ROOM TYPE: END_ROOM\n");*/
						room[i].type = 3;
						end++;
					}
				}
				
			
			fclose(fpoint);
			
		}
		
			/*---------------Begin user interface--------------*/
						
			/*Check for the start room*/
			for(i=1; i <= 7; i++){
				
				if(room[i].type == 1){
					snprintf(curRoomFile, sizeof(room[i].fullName), room[i].fullName);
					steps+=1;
					snprintf(path[steps], sizeof(room[i].roomName), room[i].roomName);
					break;
				}
			}
			
		do{
			
			
			
			FILE *fplay;
			fplay=fopen (curRoomFile, "r");
			fseek(fplay, 10, SEEK_CUR);
			
			/*Current Location*/
			
			fgets(playBuffer, 13, fplay); 
			
			
			/*Possible connections*/
			
			lob = room[i].conCount;
			
			
			//snprintf(conString , 22,"%s,", "POSSIBLE CONNECTIONS:" ); 
			
			
			for(counter = 1; counter <= lob; counter++){
				fseek(fplay, 13, SEEK_CUR);
				fgets(conCons, 13, fplay);
				
				snprintf(inFileCon[counter], sizeof(conCons), "%s", conCons);
				strtok(conCons, "\n");
				if(counter == 1){
				snprintf(conString, sizeof(conCons),"%s, ", conCons );
				}
				else if(counter != lob){
					snprintf(conString + strlen(conString), sizeof(conCons),"%s, ", conCons ); 
				}
				else{
					snprintf(conString + strlen(conString) , sizeof(conCons),"%s", conCons );
										
				}
			}
			
			
			do{
				printf("CURRENT LOCATION: %s", playBuffer);
				printf("POSSIBLE CONNECTIONS: %s.\n", conString);
				printf("WHERE TO? >");
				fgets(nextCity, 255, stdin);
				printf("\n");
				checker = 99;
				for(x = 1; x <= lob; x++){
					checker = strcmp(nextCity, inFileCon[x]);
					if (checker == 0){
						break;
					}
					if(x == lob){
						printf("HUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
					}
				}
				
				
			}while(checker !=0);
			/*compare nextCity with connections so make sure it is valid*/
			
					fclose(fplay);
					
					checker = 99;
					strtok(nextCity, "\n");
					for(i = 1; i <= 7; i++){
					 checker = strcmp(nextCity, room[i].roomName);
					 
					 if(checker == 0){
						snprintf(curRoomFile, sizeof(room[i].fullName), room[i].fullName);
						break;
						}
					
					}
					/*
					printf("start next city\n");
					printf("%s\n", curRoomFile);
					*/
					
					steps+=1;
					snprintf(path[steps], sizeof(room[i].roomName), room[i].roomName);
			}while(room[i].type != 3);
			
						
			printf("YOU HAVE FOUND THE END CITY. CONGRATULATIONS!\n");
			printf("YOU ARE GOING TO DISNEY WORLD!\n");
			printf("YOU TOOK %d FLIGHTS. YOUR PATH TO VICTORY WAS:\n", steps);
			
			for(x = 1; x <=steps; x++){
				printf("%s\n", path[x]);
			}
	exit(0);
	
	}


























