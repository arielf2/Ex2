#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <direct.h>

#define MAX_NUM_OF_STUDENTS 10
#define ID_LENGTH 10
#define COMMAND_LINE_LEN 30

BOOL CreateProcessSimple(LPTSTR CommandLine, PROCESS_INFORMATION* ProcessInfoPtr);
void CreateCommandLine(char* output_command, char* id);