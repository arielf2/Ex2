#pragma once


#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
	float* grade;
	char file_name[PATH_TO_THREAD];
} READ_FILE_ARG;


HANDLE CreateThreadSimple(LPTHREAD_START_ROUTINE p_start_routine, LPVOID p_thread_parameters, LPDWORD p_thread_id);
void read_from_file(READ_FILE_ARG* struct_arg);
DWORD WINAPI ReadFileThread(LPVOID lpParam);
int calc_average(float grades[]);
float FindHighestGrades(float grades[]);
int WriteFinalGrade(int average, char id[], char path[]);
void GetIdFromPath(char path[], char id[]);
CreatePath(char path_from_CL[], char file_name[], char path_in_struct[]);
void CloseMallocs(READ_FILE_ARG* thread_params[]);
int CloseHandles(HANDLE thread_handles[]);
