/* Functions for string manipulation and file writes */

#include "StringAndFileFuncs.h"

int WriteFinalGrade(int average, char id[], char path[]) {
	char average_c[AVERAGE_SIZE];
	char final_file_name[FINAL_FILE_SIZE] = "";
	FILE *file_pointer;
	int return_value = -1;

	sprintf_s(average_c, AVERAGE_SIZE, "%d", average);
	strcat_s(final_file_name, sizeof(final_file_name), path);
	strcat_s(final_file_name, sizeof(final_file_name), "\\final_");
	strcat_s(final_file_name, sizeof(final_file_name), id);
	strcat_s(final_file_name, sizeof(final_file_name), ".txt");
	return_value = fopen_s(&file_pointer, final_file_name, "w");

	if (return_value != 0) {
		printf("Error in open file for final writing");
		return 1;
	}
	fputs(average_c, file_pointer);

	fclose(file_pointer);
	return 0;
}

void GetIdFromPath(char path[], char id[]) {
	int size = strlen(path);
	for (int i = 0; i < ID_LENGTH - 1; i++) {
		id[i] = path[size - ID_LENGTH + 1 + i];
	}
}

void CreatePath(char path_from_CL[], char file_name[], char path_in_struct[]) {
	char full_file_name[PATH_TO_THREAD] = "";
	strcat_s(full_file_name, sizeof(full_file_name), path_from_CL);//////FIX
	strcat_s(full_file_name, sizeof(full_file_name), "\\");
	strcat_s(full_file_name, sizeof(full_file_name), file_name);
	strcpy_s(path_in_struct, PATH_TO_THREAD, full_file_name);
}