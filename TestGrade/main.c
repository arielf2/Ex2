/* Authors: Rotem Hecht 311143044
			Ariel Felberg 308425974
   Project: ISP Exercise 2
   Description: The TestGrade program goes over the different exercises/exam files, each in a different thread,
				then computes the average grade of the student
*/

//#include "TestGradeFuncsAndDefs.h"
#include "Computations.h"
#include "ThreadFuncs.h"
#include "StringAndFileFuncs.h"

int main(int argc, char *argv[]) {


	char files[][MAX_FILE_NAME_SIZE] = { "ex01.txt", "ex02.txt", "ex03.txt", "ex04.txt", "ex05.txt", "ex06.txt", "ex07.txt", "ex08.txt", "ex09.txt", "ex10.txt", "midterm.txt", "moedA.txt", "moedB.txt" };
	char directory = "";
	DWORD array_thread_ids[NUM_OF_FILES];
	HANDLE thread_handles[NUM_OF_FILES];
	DWORD  exitcode_array[NUM_OF_FILES];
	float returned_grades[NUM_OF_FILES];
	READ_FILE_ARG* thread_params[NUM_OF_FILES];
	DWORD wait_code;
	int average = 0;
	int retval;
	int final_grade_return = -1;
	char id[ID_LENGTH] = "";
	DWORD process_exit_code = 0;

	GetIdFromPath(argv[1], id);
		
	for (int i = 0; i < NUM_OF_FILES; i++) {

		//create parameters for threads
		thread_params[i] = (READ_FILE_ARG *)malloc(sizeof(READ_FILE_ARG));
		if (NULL == thread_params[i])
		{
			printf("Error when allocating memory");
			process_exit_code = -1;
		}
		if (process_exit_code == 0) {
			CreatePath(argv[1], files[i], thread_params[i]->file_name);
			thread_params[i]->grade = &(returned_grades[i]);
			strcpy_s(thread_params[i]->id, ID_LENGTH, id);
		
			//create threads for each file in grades
			//initialize handle to NULL
			thread_handles[i] = NULL;
			thread_handles[i] = CreateThreadSimple(ReadFileThread, (thread_params[i]), &(array_thread_ids[i]));
			if (thread_handles[i] == NULL)//FIX//
			{
				printf("Couldn't create thread, error code %d\n", GetLastError());
				process_exit_code = -1;
			}
		}
	}

	//wait for threads to finish
	wait_code = WaitForMultipleObjects(NUM_OF_FILES, thread_handles, TRUE, INFINITE);
	process_exit_code = CheckWaitCodes(wait_code);
	if (process_exit_code == 0) {
		//Verify exit codes of all threads are fine
		LPDWORD lpExitCode;
		for (int j = 0; j < NUM_OF_FILES; j++) {
			GetExitCodeThread(thread_handles[j], &lpExitCode);
			if (lpExitCode != 0) {
				process_exit_code = -1;
			}
		}
		if (process_exit_code == 0) {
			//calc average and write it in file
			average = calc_average(returned_grades);
			final_grade_return = WriteFinalGrade(average, id, argv[1]);
			if (final_grade_return != 0) {
				printf("Error in function open file for final writing");
				process_exit_code = -1;
			}
		}
	}	

	process_exit_code = CloseHandles(thread_handles);
	CloseMallocs(thread_params);
	
	if (process_exit_code == 0) {
		process_exit_code = average;
	}
	exit(process_exit_code);
}