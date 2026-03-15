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

  fptr = fopen("project-01-team-flames/sudokuPuzzle.txt", "r");

  // Read each row from the file into the Sudoku matrix
  while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
    sscanf(buffer, "%d %d %d %d %d %d %d %d %d", &sudokuPuzzle[row][0],
           &sudokuPuzzle[row][1], &sudokuPuzzle[row][2], &sudokuPuzzle[row][3],
           &sudokuPuzzle[row][4], &sudokuPuzzle[row][5], &sudokuPuzzle[row][6],
           &sudokuPuzzle[row][7], &sudokuPuzzle[row][8]);
    row++;
  }
  fclose(fptr);

  //Print the Sudoku Puzzle
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      printf("%d ", sudokuPuzzle[i][j]);
    }
    printf("\n");
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
  // column thread data
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

  // column worker threads
  for (int i = 0; i < 9; i++) {
    pthread_create(&tid_colThreads[i], NULL, colChecker, &columnData[i]);
  }
  // row worker threads
  for (int i = 0; i < 9; i++) {
    pthread_create(&tid_rowThreads[i], NULL, rowChecker, &rowData[i]);
  }
  // subgrid worker threads
  for (int i = 0; i < 9; i++) {
    pthread_create(&tid_subgridThreads[i], NULL, subgridChecker,
                   &subgridData[i]);
  }

  // join threads
  for (int i = 0; i < 9; i++) pthread_join(tid_colThreads[i], NULL);
  for (int i = 0; i < 9; i++) pthread_join(tid_rowThreads[i], NULL);
  for (int i = 0; i < 9; i++) pthread_join(tid_subgridThreads[i], NULL);
  // Print Column Validation Results
  printf("\nColumn Results\n");
  for(int i=0;i<9;i++)
    printf("Column: %lx %s\n", tid_colThreads[i], colArray[i] ? "valid" : "invalid");

  // Print Row Validation Results
  printf("\nRow Results\n");
  for(int i=0;i<9;i++)
    printf("Row: %lx %s\n", tid_rowThreads[i], rowArray[i] ? "valid" : "invalid");


  // print results

  // column results
  for (int i = 0; i < 9; i++) {
    printf("Column %d (Thread %lu): %s\n", i + 1,
           (unsigned long)tid_colThreads[i],
           colArray[i] == TRUE ? "valid" : "invalid");
  }
  // row results
  for (int i = 0; i < 9; i++) {
    printf("Row %d (Thread %lu): %s\n", i + 1, (unsigned long)tid_rowThreads[i],
           rowArray[i] == TRUE ? "valid" : "invalid");
  }
  // subgrid results
  for (int i = 0; i < 9; i++) {
    printf("Subgrid %d (Thread %lu): %s\n", i + 1,
           (unsigned long)tid_subgridThreads[i],
           subgridArray[i] == TRUE ? "valid" : "invalid");
  }
  // final check
  int allValid = TRUE;
  for (int i = 0; i < 9; i++) {
    if (colArray[i] == FALSE || rowArray[i] == FALSE ||
        subgridArray[i] == FALSE) {
      allValid = FALSE;
      break;
    }
  }
  printf("Sudoku Puzzle: %s\n", allValid == TRUE ? "valid" : "invalid");

  return 0;
}

void* colChecker(void* param) {
    parameters* data = (parameters*)param;

    int col = data->leftColumn;

    int seen[10] = {0};   // track numbers 1-9

    for(int row = data->topRow; row <= data->bottomRow; row++){

        int num = sudokuPuzzle[row][col];

        // Check if number is invalid or duplicated
        if(num < 1 || num > 9 || seen[num]){

            colArray[col] = FALSE;

            printf("%lx TRow:%d, BRow:%d, LCol:%d, RCol:%d invalid!\n",
                   pthread_self(),
                   data->topRow,data->bottomRow,
                   data->leftColumn,data->rightColumn);

            pthread_exit(NULL);
        }

        seen[num] = 1;
    }

    colArray[col] = TRUE;

    printf("%lx TRow:%d, BRow:%d, LCol:%d, RCol:%d valid!\n",
           pthread_self(),
           data->topRow,data->bottomRow,
           data->leftColumn,data->rightColumn);

    pthread_exit(NULL);
}


void* rowChecker(void* param) {

    parameters* data = (parameters*)param;

    int row = data->topRow;

    int seen[10] = {0};

    for(int col = data->leftColumn; col <= data->rightColumn; col++){

        int num = sudokuPuzzle[row][col];

        if(num < 1 || num > 9 || seen[num]){

            rowArray[row] = FALSE;

            printf("%lx TRow:%d, BRow:%d, LCol:%d, RCol:%d invalid!\n",
                   pthread_self(),
                   data->topRow,data->bottomRow,
                   data->leftColumn,data->rightColumn);

            pthread_exit(NULL);
        }

        seen[num] = 1;
    }

    rowArray[row] = TRUE;

    printf("%lx TRow:%d, BRow:%d, LCol:%d, RCol:%d valid!\n",
           pthread_self(),
           data->topRow,data->bottomRow,
           data->leftColumn,data->rightColumn);

    pthread_exit(NULL);
}

void* subgridChecker(void* param) {
  parameters* data = (parameters*)param;

  int index = (data->topRow / 3) * 3 + (data->leftColumn / 3);

  bool seen[10] = {false};

  for (int row = data->topRow; row <= data->bottomRow; row++) {
    for (int col = data->leftColumn; col <= data->rightColumn; col++) {
      int val = sudokuPuzzle[row][col];
      if (val < 1 || val > 9 || seen[val]) {
        subgridArray[index] = FALSE;
        pthread_exit(0);
      }
      seen[val] = true;
    }
  }

  subgridArray[index] = TRUE;
  pthread_exit(0);
}
