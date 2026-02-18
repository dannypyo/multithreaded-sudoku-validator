/**
*<Program header>
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef int bool;
#define TRUE 1
#define FALSE 0

int sudokuPuzzle[9][9];

int colArray[9];
int rowArray[9];
int subgridArray[9];

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
	
	
}

void *colChecker(void *param){
	


}	

void *rowChecker(void *param){


}

void *subgridChecker(void *param){


}
