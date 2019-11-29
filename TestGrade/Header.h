#pragma once


#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_FILE_NAME_SIZE 12
#define NUM_OF_FILES 13
#define LINE_IN_FILE_LENGTH 10
#define NUM_OF_EXERCISES 10
#define ERROR_CODE ((int)(-1))
#define SUCCESS_CODE ((int)(0))
#define ID_LENGTH 10
/*
* A type for thread return codes
*/
typedef enum
{
	MATH_THREAD__CODE_SUCCESS,
	MATH_THREAD__CODE_NULL_PTR,
} MATH_THREAD__return_code_t;


typedef struct _READ_FILE_ARG {
	char id[ID_LENGTH];
	int grade;
	char file_name[MAX_FILE_NAME_SIZE];
} READ_FILE_ARG;


HANDLE CreateThreadSimple(LPTHREAD_START_ROUTINE p_start_routine, LPDWORD p_thread_id);
void read_from_file(char id, char file_name, int* grade);
DWORD WINAPI ReadFileThread(LPVOID lpParam);
