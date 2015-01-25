/*
*Chad H Glaser
*CS 344
*Winter 2015
*Dungeon Adventure Game
* Random name creator
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <string.h>
#include <time.h>
struct textFile{
	char roomName[80];
	char fileName[80];
};

void swap (int *a, int *b){

	int temp = *a;
	*a = *b;
	*b = temp;
}

void randArr(int arr[], int n){
	int i, j, k;
	
	srand( time(NULL));
	for (j = n-1; j > 0; j--){
		k = rand() % (j+1);
		swap(&arr[j], &arr[k]);
	}
	
	
}






void printArr( int arr[], int n){
	int i;
	for (i = 0; i < n; i++)
		printf("num: %d, ", arr[i]);
	printf("\n");

}

int main(){

	const char *title[10];
	int n = 10;
	int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,};
	int ray[10];
	int i;
	randArr(arr, n);
	printArr(arr, n);

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
	
		
	for (i = 0; i < n; i++){

	printf("room[%d]: %s\n", i, title[i]);

	}

return 0;
}



























