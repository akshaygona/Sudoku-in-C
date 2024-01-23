///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2021 Deb Deppeler
// Posting or sharing this file is prohibited, including any changes/additions.
//
// We have provided comments and structure for this program to help you get 
// started.  Later programs will not provide the same level of commenting,
// rather you will be expected to add same level of comments to your work.
// 09/20/2021 Revised to free memory allocated in get_board_size function.
// 01/24/2022 Revised to use pointers for CLAs
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        check_board.c
// This File:        check_board.c
// Other Files:      board0.txt, board1.txt, board2.txt, board3.txt, board4.txt, board5.txt, board6.txt, board10.txt,
//                   board01.txt, board1solution.txt, board2solution.txt
// Semester:         CS 354 Spring 2023
// Instructor:       Mark Mansi
//
// Author:           Akshay Gona 
// Email:            gona@wisc.edu 
// CS Login:         gona 
// GG#:              (your Canvas GG number)
//                   (See https://canvas.wisc.edu/groups for your GG number)
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   including family, friends, classmates, tutors,
//                   Peer Mentors, TAs, and Instructor.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   how to install valgrind,
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *DELIM = ",";  // commas ',' are a common delimiter character for data strings

/* COMPLETED (DO NOT EDIT):       
 * Read the first line of input file to get the size of that board.
 * 
 * PRE-CONDITION #1: file exists
 * PRE-CONDITION #2: first line of file contains valid non-zero integer value
 *
 * fptr: file pointer for the board's input file
 * size: a pointer to an int to store the size
 *
 * POST-CONDITION: the integer whos address is passed in as size (int *)
 * will now have the size (number of rows and cols) of the board being checked.
 */
void get_board_size(FILE *fptr, int *size) {      
	char *line1 = NULL;
	size_t len = 0;

	if ( getline(&line1, &len, fptr) == -1 ) {
		printf("Error reading the input file.\n");
		free(line1);
		exit(1);
	}

	char *size_chars = NULL;
	size_chars = strtok(line1, DELIM);
	*size = atoi(size_chars);

	// free memory allocated for reading first link of file
	free(line1);
	line1 = NULL;
}



/* TODO:
 * Returns 1 if and only if the board is in a valid Sudoku board state.
 * Otherwise returns 0.
 * 
 * A valid row or column contains only blanks or the digits 1-size, 
 * with no duplicate digits, where size is the value 1 to 9.
 * 
 * Note: p2A requires only that each row and each column are valid.
 * 
 * board: heap allocated 2D array of integers 
 * size:  number of rows and columns in the board
 */
//make sure there are no repeating numbers in the row or columns of the board
//use only pointers
int valid_board(int **board, int size) {
    int *row = malloc(sizeof(int) * size); //allocating memory for rows
    if(row == NULL){
        printf("Error allocating memory\n");
        exit(1);
    }
    int *col = malloc(sizeof(int) * size); //allocating memory for columns
    if(col == NULL){
        printf("Error allocating memory\n");
        exit(1);
    }
    for(int i = 0; i < size; i++){ //purpose of this loop is to check if there are any repeating numbers in the rows and columns
        for(int j = 0; j < size; j++){ //purpose of this loop is to store the values of the rows and columns in the arrays
            *(row + j) = *(*(board + i) + j); //storing the values of the rows
            *(col + j) = *(*(board + j) + i); //storing the values of the columns
        }
        for(int k = 0; k < size; k++){
            for(int l = k + 1; l < size; l++){
                if(*(row + k) == *(row + l) && *(row + k) != 0){ //if row and column are equal and not equal to 0, then return 0
                    free(row); //freeing rows
                    free(col); //freeing columns
                    return 0;
                }
                if(*(col + k) == *(col + l) && *(col + k) != 0){ //if row and column are equal and not equal to 0, then return 0
                    free(row); //freeing rows
                    free(col); //freeing columns
                    return 0;
                }
            }
        }
    }
    free(row);
    free(col);
    return 1;
}    



/* TODO: COMPLETE THE MAIN FUNCTION
 * This program prints "valid" (without quotes) if the input file contains
 * a valid state of a Sudoku puzzle board wrt to rows and columns only.
 *
 * A single CLA is required, which is the name of the file 
 * that contains board data is required.
 *
 * argc: the number of command line args (CLAs)
 * argv: the CLA strings, includes the program name
 *
 * Returns 0 if able to correctly output valid or invalid.
 * Only exit with a non-zero result if unable to open and read the file given.
 */
int main( int argc, char **argv ) {              

	if (argc != 2) {
		printf("Usage: ./check_board <input_filename>\n");
		exit(1);
	}

	// Open the file and check if it opened successfully.
	FILE *fp = fopen(*(argv + 1), "r");
	if (fp == NULL) {
		printf("Can't open file for reading.\n");
		exit(1);
	}

	// Declare local variables.
	int size;

	// TODO: Call get_board_size to read first line of file as the board size.
    get_board_size(fp, &size); //calling get_board_size function
	// TODO: Dynamically allocate a 2D array for given board size.
    int **board = malloc(sizeof(int *) * size); //board allocation, need to check for NULL, check notes and come back to it.
    if(board == NULL){
        printf("Error allocating memory\n");
        exit(1);
    }
    for(int i = 0; i < size; i++){
        *(board + i) = malloc(sizeof(int) * size);// size allocation once again
        if(*(board + i) == NULL){ //checking for null
            printf("Error allocating memory\n");
            exit(1);
        }
        for(int j = 0; j < size; j++){
            *(*(board + i) + j) = 0;
        }
    }
	// Read the rest of the file line by line.
	// Tokenize each line wrt the delimiter character
	// and store the values in your 2D array.
	char *line = NULL;
	size_t len = 0;
	char *token = NULL;
	for (int i = 0; i < size; i++) {

		if (getline(&line, &len, fp) == -1) { //warning here, but i didn't write it, check stdlib.h?
			printf("Error while reading line %i of the file.\n", i+2);
			exit(1);
		}

		token = strtok(line, DELIM);
		for (int j = 0; j < size; j++) {
			// TODO: Complete the line of code below
			// to initialize your 2D array.
            *(*(board + i) + j) = atoi(token); //atoi converts string to integer, need to check for null?
			token = strtok(NULL, DELIM);
		}
	}

	// TODO: Call the function valid_board and print the appropriate
	//       output depending on the function's return value.
    if(valid_board(board, size) == 1){ //if valid_board returns 1, then print valid
        printf("valid\n");
    }
    else{ //if valid_board returns 0, then print invalid
        printf("invalid\n");
    }
	// TODO: Free all dynamically allocated memory.
    for(int i = 0; i < size; i++){
        free(*(board + i)); //free each of the sub arrays,
    }
    free(board); //free the large array of arrays.
    // Close the file.
	if (fclose(fp) != 0) {
		printf("Error while closing the file.\n");
		exit(1);
	}
	return 0;       
}       
