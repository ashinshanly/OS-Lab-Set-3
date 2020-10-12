#define _FILE_OFFSET_BITS 64
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>
#include<string.h>

#define BUFF_SIZE 4096

void printLine(FILE *file, off_t startline)
{
    int fd;
    fd= fileno(file);
    int nread;
    char buffer[BUFF_SIZE];
    lseek(fd,(startline + 1),SEEK_SET);
    while((nread= read(fd,buffer,BUFF_SIZE)) > 0)
    {
        write(STDOUT_FILENO, buffer, nread);
    }
}

void walkFile(FILE *file, long nlines)
{
    off_t fposition;
    fseek(file,0,SEEK_END);
    fposition= ftell(file);
    off_t index= fposition;
    off_t end= fposition;
    long countlines= 0;
    char cbyte;

    for(index; index >= 0; index --)
    {
        cbyte= fgetc(file);
        if (cbyte == '\n' && (end - index) > 1)
        {
            countlines ++;
            if(countlines == nlines)
            {
                break;
            }
        }
        fposition--;
        fseek(file,fposition,SEEK_SET);
    }
    printLine(file, fposition);
    fclose(file);
}

int main(int argc, char *argv[])
{
    FILE *file;
    file= fopen(argv[2], "r");
    if(file == NULL)
    {
        fprintf(stderr,"Error opening file: %s\n",argv[2]);
        exit(errno);
    }
    char c[2] = "";
    strcpy(c,argv[1]);
    printf("%c", c[1]);
    walkFile(file, atol(argv[1])); ///// Note: Considers only input of format "mytail n file"
    return 0;
}