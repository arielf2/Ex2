#pragma once

// Includes --------------------------------------------------------------------

#include <stdio.h>
#include <windows.h>

// Constants -------------------------------------------------------------------

#define ERROR_CODE ((int)(-1))
#define NUM_OF_FILES 13
#define LINE_IN_FILE_LENGTH 10
#define ID_LENGTH 10
#define PATH_TO_THREAD 36 //FIX//

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

	Description:	Open a file with a grade in it (can be exercise, midterm, or exam) and get the grade
	Parameters:		struct_arg: The struct with its filename, id, and grade pointer fields. It will be updated with the grade from the file we read
	Returns:		integer error code - -1 upon failure

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


/*	CloseHandles

	Description:	Closes the handles to the different threads that were created
	Parameters:		HANDLE thread_handles[]: The array of handles to the threads, that will be passed as a parameter to CloseHandle
	Returns:		error code: -1 upon failure

*/
int CloseHandles(HANDLE thread_handles[]);

/*	CheckWaitCodes

	Description:	This function handles the different possible waitcodes that indicate an error in WaitForMultipleObjects
	Parameters:		int waitcode: An integer that is returned by WaitForMultipleObjects and indicates the state of the wait
	Returns:		int error:	  A binary flag that states whether we received a bad waitcode (error = 1) or didn't (error = 0)

*/
int CheckWaitCodes(int waitcode);


/*	CloseMallocs

	Description:	Frees the dynamically allocated memory
	Parameters:		READ_FILE_ARG* thread_params[]: pointer to the array of file structs, where the memory was allocated
	Returns:		none

*/

void CloseMallocs(READ_FILE_ARG* thread_params[]);