#pragma once

// Includes --------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Constants -------------------------------------------------------------------

#define MAX_NUM_OF_STUDENTS 10
#define ID_LENGTH 10
#define TIMEOUT 5000
#define COMMAND_LINE_LEN 70
#define MAX_RELATIVE_PATH_LEN 100 //input(5) + space(1) + id(9)
#define MAX_OUTPUT_FILE_LEN 100
#define STUDENT_FILE "//student_ids.txt"
/* Remove in the end and change in main */
#define GOVER_STUDENT_FILE "//studentIds.txt" 
/* Remove in the end and change in main*/
#define OUTPUT_GRADE_FILE "//final_grades.txt"
#define TEST_GRADE_PROG "TestGrade.exe "
#define GRADES_DIR "//grades_"

// Structs ---------------------------------------------------------------------

typedef struct _STUDENT_INFO {
	char id[ID_LENGTH];
	int *grade;
} STUDENT_INFO;

// Function Declarations -------------------------------------------------------

/*	CheckWaitCodes

	Description:	This function handles the different possible waitcodes that indicate an error in WaitForMultipleObjects
	Parameters:		int waitcode: An integer that is returned by WaitForMultipleObjects and indicates the state of the wait	
	Returns:		int error:	  A binary flag that states whether we received a bad waitcode (error = 1) or didn't (error = 0) 

*/
int CheckWaitCodes(int waitcode);

/*	CreateProcessSimple

	Description:	Sends the correct arguments to CreateProcess, with the input command line and Process pointer
	Parameters:		LPTSTR CommandLine: Command line to send to the child process, with the path to the child executable and math argument for calculation
					PROCESS_INFORMATION* ProcessInfoPtr: Pointer to the process information struct
	Returns:		BOOL value indicating the success or failure of the process creation */

BOOL CreateProcessSimple(LPTSTR CommandLine, PROCESS_INFORMATION* ProcessInfoPtr);

/*  WriteFinalGrades

	Description:	This function summarizes the thread results - takes the average grade for each student and writes it 
					to an output file "final_grades.txt"
	Parameters:		int waitcode: An integer that is returned by WaitForMultipleObjects and indicates the state of the wait
					STUDENT_INFO *StudArray: A pointer to an array of structs 'STUDENT_INFO' (has grade and id for each element). 
											 The function will use the elements of this array to write to the output file.
					int NumOfStudents:		 The actual number of students in the exercise. The function will use a for loop
											 that is limited by the actual number of students (= num of elements in the array)
					char* OutputFile:		 The string containing part of the output file path. The function will later concatenate
											 the rest of the path.

	Returns:		int error:				 A binary flag that states whether the function succeeded 
	
*/
int WriteFinalGrades(STUDENT_INFO *StudArray, int NumOfStudents, char* OutputFile);
