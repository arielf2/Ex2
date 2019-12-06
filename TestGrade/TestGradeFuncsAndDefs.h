#pragma once

// Includes --------------------------------------------------------------------

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Constants -------------------------------------------------------------------

#define MAX_FILE_NAME_SIZE 12
#define NUM_OF_FILES 13
#define LINE_IN_FILE_LENGTH 10
#define NUM_OF_EXERCISES 10
#define ERROR_CODE ((int)(-1))
#define SUCCESS_CODE ((int)(0))
#define ID_LENGTH 10
#define HIGHEST_EXERCISES_GRADE 8
#define MOED_A 11
#define MOED_B 12
#define MIDTERM	10
#define PATH_TO_THREAD 36 //FIX//
#define AVERAGE_SIZE 4
#define FINAL_FILE_SIZE 80///
#define ERROR_MESSAGE_SIZE 47
#define PATH_FROM_CL  24

// Structs ---------------------------------------------------------------------

typedef struct _READ_FILE_ARG {
	char id[ID_LENGTH];
	float* grade;
	char file_name[PATH_TO_THREAD];
} READ_FILE_ARG;

// Function Declarations -------------------------------------------------------

/*	CreateThreadSimple

	Description: A simplified API for creating threads.
	Parameters:	 p_start_routine: A pointer to the function to be executed by the thread.
				 p_thread_parameters: A (void *) to a variable to be passed to the thread.
				 p_thread_id: A pointer to a variable that receives the thread identifier.
	Returns:	 If the function succeeds, the return value is a handle to the new thread If the function fails, the return value is NULL.

*/
HANDLE CreateThreadSimple(LPTHREAD_START_ROUTINE p_start_routine, LPVOID p_thread_parameters, LPDWORD p_thread_id);


/*	read_from_file

	Description:	
	Parameters:		struct_arg
	Returns:		

*/
int read_from_file(READ_FILE_ARG* struct_arg);

/*	ReadFileThread

	Description:	The WINAPI thread function that casts the input parameter to the struct type and calls our created thread function
					It will read each grade file of the student
	Parameters:		lpParam: A (void *) that will be cast to READ_FILE_ARG struct - that has the parameters: id of the student,
					pointer to its computed average, and a string with the file name
	Returns:		DWORD - A binary flag that indicates the success or failure of the function

*/
DWORD WINAPI ReadFileThread(LPVOID lpParam);

/*	calc_average

	Description:	
	Parameters:		grades array
	Returns:		

*/
int calc_average(float grades[]);

/*	FindHighestGrades

	Description:	
	Parameters:		grades array
	Returns:		

*/
float FindHighestGrades(float grades[]);

/*	WriteFinalGrade

	Description:	
	Parameters:		int average:
					char id[]:
					char path[]:
	Returns:		

*/
int WriteFinalGrade(int average, char id[], char path[]);

/*	GetIdFromPath

	Description:	
	Parameters:		char path[]:
					char id[]:
	Returns:		none

*/
void GetIdFromPath(char path[], char id[]);

/*	CreatePath

	Description:	
	Parameters:		char path_from_CL[]:
					char file_name[]:
					char path_in_struct[]:
	Returns:		none

*/
CreatePath(char path_from_CL[], char file_name[], char path_in_struct[]);

/*	CloseMallocs

	Description:	Frees the dynamically allocated memory 
	Parameters:		READ_FILE_ARG* thread_params[]: pointer to the array of file structs, where the memory was allocated
	Returns:		none

*/

void CloseMallocs(READ_FILE_ARG* thread_params[]);

/*	CloseHandles

	Description:	Closes the handles to the different threads that were created
	Parameters:		HANDLE thread_handles[]: 
	Returns:		

*/
int CloseHandles(HANDLE thread_handles[]);

/*	CheckWaitCodes

	Description:	This function handles the different possible waitcodes that indicate an error in WaitForMultipleObjects
	Parameters:		int waitcode: An integer that is returned by WaitForMultipleObjects and indicates the state of the wait
	Returns:		int error:	  A binary flag that states whether we received a bad waitcode (error = 1) or didn't (error = 0)

*/
int CheckWaitCodes(int waitcode);
