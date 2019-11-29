#include <stdio.h>
#include <stdlib.h> 


int main(int argc, char *argv[])
{
	printf("child process print %s\n", argv[1]);
	getchar();
	return 0;
}