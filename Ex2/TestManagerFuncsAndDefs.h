#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <direct.h>

#define MAX_NUM_OF_STUDENTS 10
#define ID_LENGTH 10
#define COMMAND_LINE_LEN 30


typedef struct _STUDENT_INFO {
	char id[ID_LENGTH];
	int *grade;
} STUDENT_INFO;

BOOL CreateProcessSimple(LPTSTR CommandLine, PROCESS_INFORMATION* ProcessInfoPtr);
void CreateCommandLine(char* output_command, char* id);
int WriteFinalGrades(STUDENT_INFO *stud_array, int num_of_students);