/**
*<Program header>
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#define TRUE 1
#define FALSE 0

int sudokuPuzzle[9][9];

int colArray[9];
int rowArray[9];
int subgridArray[9];
char buffer[81];

void *colChecker(void *param);
void *rowChecker(void *param);
void *subgridChecker(void *param);

//
typedef struct{
	int topRow;
	int bottomRow;
	int leftColumn;
	int rightColumn;
} parameters;

int main(){
	FILE *fptr;
	int row = 0;
	fptr = fopen("SudokuPuzzle.txt", "r");
	while (fgets(buffer, sizeof(buffer), fptr) != NULL){
		sscanf(buffer, "%d %d %d %d %d %d %d %d %d", 
			&sudokuPuzzle[row][0], 
			&sudokuPuzzle[row][1], 
			&sudokuPuzzle[row][2], 
			&sudokuPuzzle[row][3], 
			&sudokuPuzzle[row][4], 
			&sudokuPuzzle[row][5], 
			&sudokuPuzzle[row][6], 
			&sudokuPuzzle[row][7],
			&sudokuPuzzle[row][8]);
		row++;
	}
	for (int i = 0; i < 9; i++) {
    	for (int j = 0; j < 9; j++) {
        printf("%d ", sudokuPuzzle[i][j]); // print each number
    	}
    printf("\n"); // new line after each row
	}
	
}

void *colChecker(void *param){
	


}	

void *rowChecker(void *param){


}

void *subgridChecker(void *param){


}
