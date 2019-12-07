#pragma once

// Includes --------------------------------------------------------------------

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Constants -------------------------------------------------------------------

#define MAX_FILE_NAME_SIZE 12
#define AVERAGE_SIZE 4
#define FINAL_FILE_SIZE 46
#define ID_LENGTH 10
#define PATH_TO_THREAD 36

// Function Declarations -------------------------------------------------------

/*	WriteFinalGrade

	Description:	Writes the final computed average grade of the student to a new output file called "final_{id}.txt"
	Parameters:		int average: The computed average that will be written to the file
					char id[]:	 The ID of the student as a string, that will be concatenated to the new file name
					char path[]: The path of the output file as a string, to which the id will be concatenated
	Returns:		error code - 0 upon success

*/
int WriteFinalGrade(int average, char id[], char path[]);

/*	GetIdFromPath

	Description:	TestGrade gets a relative path from TestManager that looks like : "{input_folder}//grades_{id}".
					This function will extract just the ID from the path
	Parameters:		char path[]:	The relative path of the student directory, as a string.
					char id[]:		The ID string, to which we will write the extracted ID from the path.
	Returns:		none	

*/
void GetIdFromPath(char path[], char id[]);

/*	CreatePath

	Description:	Concatenate paths to create a single full path variable
	Parameters:		char path_from_CL[]:	the {input_folder} as received from the command line arguments
					char file_name[]:		The current file name (can be ex01.txt to ex10.txt, midterm.txt, moedA.txt, moedB.txt)
					char path_in_struct[]:	The output argument - the function will concatenate the last to arguments and the result to this one.
	Returns:		none

*/
void CreatePath(char path_from_CL[], char file_name[], char path_in_struct[]);
