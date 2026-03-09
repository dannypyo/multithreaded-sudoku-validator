/**
 *<Program header>
 */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int sudokuPuzzle[9][9];

int colArray[9];
int rowArray[9];
int subgridArray[9];
char buffer[81];

void* colChecker(void* param);
void* rowChecker(void* param);
void* subgridChecker(void* param);

//
typedef struct {
  int topRow;
  int bottomRow;
  int leftColumn;
  int rightColumn;
} parameters;

int main() {
  FILE* fptr;
  int row = 0;

  fptr = fopen("SudokuPuzzle.txt", "r");

  while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
    sscanf(buffer, "%d %d %d %d %d %d %d %d %d", &sudokuPuzzle[row][0],
           &sudokuPuzzle[row][1], &sudokuPuzzle[row][2], &sudokuPuzzle[row][3],
           &sudokuPuzzle[row][4], &sudokuPuzzle[row][5], &sudokuPuzzle[row][6],
           &sudokuPuzzle[row][7], &sudokuPuzzle[row][8]);
    row++;
  }
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      printf("%d ", sudokuPuzzle[i][j]);  // print each number
    }
    printf("\n");  // new line after each row
  }
  // initialize all entries in Boolean arrays to false
  for (int i = 0; i < 9; i++) {
    colArray[i] = FALSE;
  }
  for (int i = 0; i < 9; i++) {
    rowArray[i] = FALSE;
  }
  for (int i = 0; i < 9; i++) {
    subgridArray[i] = FALSE;
  }
  // subgrid data
  parameters subgridData[9];
  int index = 0;

  for (int row = 0; row < 9; row += 3) {
    for (int col = 0; col < 9; col += 3) {
      subgridData[index].topRow = row;
      subgridData[index].bottomRow = row + 2;
      subgridData[index].leftColumn = col;
      subgridData[index].rightColumn = col + 2;
      index++;
    }
  }
  //column thread data 
  parameters columnData[9];
  for (int i = 0; i < 9; i++) {
	columnData[i].topRow = 0;
	columnData[i].bottomRow = 8;
	columnData[i].leftColumn = i;
	columnData[i].rightColumn = i;
  }
  // row thread data 
  parameters rowData[9];
  for (int i = 0; i < 9; i++) {
	rowData[i].topRow = i;	
	rowData[i].bottomRow = i;
	rowData[i].leftColumn = 0;
	rowData[i].rightColumn = 8;
  }

  //  thread IDs
  pthread_t tid_colThreads[9];
  pthread_t tid_rowThreads[9];
  pthread_t tid_subgridThreads[9];

  //column worker threads
  for (int i = 0; i < 9; i++) {
    pthread_create(&tid_colThreads[i], NULL, colChecker, &columnData[i]);
  }
  // row worker threads
  for (int i = 0; i < 9; i++) {
    pthread_create(&tid_rowThreads[i], NULL, rowChecker, &rowData[i]);
  }
  // subgrid worker threads 
  for (int i = 0; i < 9; i++) {
    pthread_create(&tid_subgridThreads[i], NULL, subgridChecker, &subgridData[i]);
  }


}

void* colChecker(void* param) {}

void* rowChecker(void* param) {}

void* subgridChecker(void* param) {}
