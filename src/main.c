#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>


/*
- need to read the downloads folder
- look for all the files that have Ronny_Toribio_Resume_*job*.pdf as there name
- for each file create a folder with the company name
- insert the file to its matching job
- Change the name of the File so it looks more human presentable -> Ronny Toribio Resume.pdf

- do the same with cover letters
*/

int main(void) {

  DIR *folder;

  struct dirent *entry;

  folder = opendir("/Users/ronnytoribio/Downloads");
  
  if (folder == NULL) {
    perror("Unable to read directory");
    return 1;
  }


  while ((entry = readdir(folder)) != NULL) {
    if (strstr(entry->d_name, "Ronny_Toribio_Resume") != NULL) {

      int length_of_filename = strlen(entry->d_name);

      for(int i = 0; i < length_of_filename; i++) {
        if ((length_of_filename - 5 ) >= i & i >= 21) {
          printf("%c", entry->d_name[i]);
        }
      }
      printf("\n");
      // printf("%s\n", entry->d_name);
    }
  }


  closedir(folder);
  
  return 0;
}

// int getAllFiles() {}

// int populateFolders() {}