#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


#define MAX_NUM_OF_STUDENTS 10
#define ID_LENGTH 10
#define TIMEOUT 5000
#define COMMAND_LINE_LEN 70
#define MAX_RELATIVE_PATH_LEN 100 //input(5) + space(1) + id(9)
#define MAX_OUTPUT_FILE_LEN 100
#define STUDENT_FILE "//student_ids.txt"
#define GOVER_STUDENT_FILE "//studentIds.txt"
#define OUTPUT_GRADE_FILE "//final_grades.txt"
#define TEST_GRADE_PROG "TestGrade.exe "
#define GRADES_DIR "//grades_"


typedef struct _STUDENT_INFO {
	char id[ID_LENGTH];
	int *grade;
} STUDENT_INFO;

int CheckWaitCodes(int waitcode);
BOOL CreateProcessSimple(LPTSTR CommandLine, PROCESS_INFORMATION* ProcessInfoPtr);
int WriteFinalGrades(STUDENT_INFO *StudArray, int NumOfStudents, char* OutputFile, char* GradesDir);