#include <dirent.h> 
#include <stdio.h> 
#include <string.h>

void show_dir_content(char * path)
{
  DIR * d = opendir(path);
  if(d==NULL) return; 
  struct dirent * dir;
  while ((dir = readdir(d)) != NULL)
    {
      if(dir-> d_type != DT_DIR)  // if the type is not directory just print it
        printf("%s\n", dir->d_name);
      else
      if(dir -> d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 )   // if it is a directory
      {
        printf("%s\n",dir->d_name); 
        char d_path[255];   // here I am using sprintf which is safer than strcat
        sprintf(d_path, "%s/%s", path, dir->d_name);
        show_dir_content(d_path);   // recursively call with the new path
      }
    }
    closedir(d);
}

int main(int argc, char **argv)
{
    if(argc == 1){
        show_dir_content(".");
        return 0;
    }
    else if (argc == 2)
    {
        show_dir_content(argv[1]);
        return(0);
    }
    
    
}