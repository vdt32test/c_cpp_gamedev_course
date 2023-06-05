#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "windows.h"


const char *fileName = "Hamlet.txt";


long getFileSize1(const FILE *pFile)
{
    struct stat tmp_stat;
    if(fstat(fileno(pFile), &tmp_stat))
    {
        puts("fstat error");
        exit(EXIT_FAILURE);
    }

    long size = tmp_stat.st_size;
    return size;
}


DWORD getFileSize2(const FILE *pFile)
{
	int fileno1 = _fileno(pFile);
	if (!fileno1 || fileno1 == -1 || errno)
	{
		puts("_fileno error");
		exit(EXIT_FAILURE);
	}

	HANDLE hFile = (HANDLE)_get_osfhandle(fileno1);
	if (hFile == INVALID_HANDLE_VALUE || errno)
	{
		puts("_get_osfhandle error");
		exit(EXIT_FAILURE);
	}
	 
	DWORD fileSize = GetFileSize(hFile, NULL);
	if (fileSize == INVALID_FILE_SIZE)
	{
		puts("GetFileSize error");
		exit(EXIT_FAILURE);
	}

    return fileSize;
}


int main()
{
    FILE *pFile = fopen(fileName, "r");
    if(!pFile)
    {
        puts("fopen error");
        return EXIT_FAILURE;
    }

    DWORD size = getFileSize2(pFile);
    printf("size = %lu\n", size);

    char *text = (char *)malloc(sizeof(char)*size+1);

    size_t readCounter = fread((void *)text, size, 1, pFile);
    if(readCounter != 1)
    {
        puts("fread error");
        printf("readCounter %u\n", readCounter);
        return EXIT_FAILURE;
    }
    
    text[size] = '\0';

    printf("%s\n", text);

    free(text);
    fclose(pFile);

    printf("EXIT_SUCCESS\n");
    return EXIT_SUCCESS;
}