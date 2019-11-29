#include <stdio.h>
#include <windows.h>

typedef struct _READ_FILE_ARG {
	char id;
	int* grade;
	char file_name;
} READ_FILE_ARG;

int main() {

#define MAX_FILE_SIZE 12
#define NUM_OF_FILES 13
	char files[NUM_OF_FILES][MAX_FILE_SIZE] = { ex01.txt, ex02.txt, ex03.txt, ex04.txt, ex05.txt, ex06.txt, ex07.txt, ex08.txt, ex09.txt, ex10.txt, midterm.txt, moedA.txt, moedB.txt };
	char directory = "";
	LPWORD array_thread_ids[NUM_OF_FILES];
	int retval;

	for (int i = 0, i < NUM_OF_FILES, i++) {
		retval = CreateThreadSimple();
		if (ret_val == 0)//FIX//
		{
			printf("Couldn't create process, error code %d\n", GetLastError());
			return;
		}
	}

	return 0;
}

HANDLE CreateThreadSimple(LPTHREAD_START_ROUTINE p_start_routine, LPDWORD p_thread_id)
{

	return CreateThread(
		NULL,
		0,
		p_start_routine,
		NULL,
		0,
		p_thread_id);
}

void read_from_file(char id, char file_name, int* grade) {
	char full_file_name =
		FILE * fp = fopen(file_name);
}