#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    struct stat s;

   if (argc != 2) {
        fprintf(stderr, "Path: %s \n", argv[0]);
        exit(EXIT_FAILURE);
    }

   if (stat(argv[1], &s) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

   printf("File type:                ");

   switch (s.st_mode & S_IFMT) {
    case S_IFBLK:  printf("Block device\n");            break;
    case S_IFCHR:  printf("Character device\n");        break;
    case S_IFDIR:  printf("Directory\n");               break;
    case S_IFIFO:  printf("FIFO/pipe\n");               break;
    case S_IFLNK:  printf("Symlink\n");                 break;
    case S_IFREG:  printf("Regular file\n");            break;
    case S_IFSOCK: printf("Socket\n");                  break;
    default:       printf("Unknown?\n");                break;
    }

    printf("Reference count:               %ld\n", (long) s.st_nlink);
    printf("Ownership:                UID=%ld   GID=%ld\n",
            (long) s.st_uid, (long) s.st_gid);

    printf("File size:                %lld Bytes\n",
            (long long) s.st_size);
    printf("Blocks allocated:         %lld\n",
            (long long) s.st_blocks);
    printf("Last file modification:   %s", ctime(&s.st_mtime));

   exit(EXIT_SUCCESS);
}