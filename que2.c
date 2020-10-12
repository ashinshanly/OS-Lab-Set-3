#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    DIR *d;
    struct dirent *dir;

    struct stat s;
    int a, c=0;

    if(argc > 3){
        printf("Number of arguments exceeded!\n");
    }
    if(argc == 3){
        d = opendir(argv[2]);
    }
    else if (argc == 2 && strcmp(argv[1],"-l")==0)
    {
        d = opendir(".");
    }
    else if ( argc == 2 && strcmp(argv[1],"-l")!=0 )
    {
        d = opendir(argv[1]);
        if(d){
            while ((dir = readdir(d)) != NULL){
                printf("%s\n", dir->d_name);
            }
            closedir(d);
        }
        exit(EXIT_SUCCESS);
    }
    else if (argc ==1)
    {
        d = opendir(".");
        if(d){
            while ((dir = readdir(d)) != NULL){
                printf("%s\n", dir->d_name);
            }
            closedir(d);
        }
        exit(EXIT_SUCCESS);
    }  
    

    if(d){
            while ((dir = readdir(d)) != NULL){
                if (c>1)
                {
                    a = stat(dir->d_name, &s);
                    if (a==0){
                        printf("File : %s\n", dir->d_name);
                        printf("Reference count: %ld\n", (long) s.st_nlink);
                        printf("Ownership: UID=%ld   GID=%ld\n",(long) s.st_uid, (long) s.st_gid);
                        printf("File size: %lld Bytes\n",(long long) s.st_size);
                        printf("Blocks allocated: %lld\n", (long long) s.st_blocks);
                        printf("Last file modification:   %s", ctime(&s.st_mtime));
                    }
                    else{
                        printf("Error reading file properties!\n");
                    }
                }
                c++;
                
            }
            closedir(d);
        }
    
    exit(EXIT_SUCCESS);
}