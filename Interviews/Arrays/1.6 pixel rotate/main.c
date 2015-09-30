#include <stdio.h>
#include <stdlib.h>

int** rotate90(int** image);
void printImg(int** img);
/*
Given an image represented by an NxN matrix, where each pixel in the image is 4
bytes, write a method to rotate the image by 90 degrees. Can you do this in place?
*/
#define IMG_SIZE 5

int main(){
	int** image = malloc(IMG_SIZE*sizeof(int*));
	int i,j;
	for(i = 0; i < IMG_SIZE;i++){
		image[i] = calloc(IMG_SIZE,sizeof(int));
		for(j=0;j<IMG_SIZE;j++){
			image[i][j] = i;
		}
	}
	printImg(image);
	image = rotate90(image);
	printImg(image);
	image = rotate90(image);
	printImg(image);
	image = rotate90(image);
	printImg(image);
	image = rotate90(image);
	printImg(image);
	return 0;
}

//0,0->9,0
//1,0->9,1
//0,1->8,0
//1,1->8,1
//s = IMG_SIZE-1 = 9
//0,0->s,0
//i,0->s,i
//0,j->s-j,0
int** rotate90(int** image){
	int temp,i,j,s=IMG_SIZE-1;
	int end = IMG_SIZE/2;
	for(i=0;i<end;i++){
		for(j=0;j<end;j++){
			// printf("swap t <= (%d, %d)\n", i,j);
			// printf("swap (%d, %d) <= (%d, %d)\n", i,j,s-i,j);
			// printf("swap (%d, %d) <= (%d, %d)\n", s-i,j,s-i,s-j);
			// printf("swap (%d, %d) <= (%d, %d)\n", s-i,s-j,i,s-j);
			// printf("swap (%d, %d) <= t\n", i,s-j);
			
			temp = image[i][j];				//t = 2
			image[i][j] = image[s-j][i]; 	//2 = 3
			image[s-j][i] = image[s-i][s-j];//3 = 4
			image[s-i][s-j] = image[j][s-i];//4 = 1
			image[j][s-i] = temp;			//1 = t
		}
	}
	if(IMG_SIZE%2){// screw it
		int mid = IMG_SIZE/2 + IMG_SIZE%2;
		int i;
		for(i = 0;i < mid; i++){
			temp = image[mid][i];				//t = 2
			image[mid][i] = image[i][mid]; 	//2 = 3
			image[i][mid] = image[mid][s-i];//3 = 4
			image[mid][s-i] = image[s-i][mid];//4 = 1
			image[s-i][mid] = temp;			//1 = t

		}
	}
	return image;
}

void printImg(int** img){
	int i, j;
	for(i = 0;i<IMG_SIZE;i++){
		for(j=0;j<IMG_SIZE;j++){
			printf("%d ", img[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}