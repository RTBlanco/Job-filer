#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>


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

  
  char path[] = "/Users/ronnytoribio/Desktop/resumes/";
  folder = opendir("/Users/ronnytoribio/Downloads");
  
  if (folder == NULL) {
    perror("Unable to read directory");
    return 1;
  }


  while ((entry = readdir(folder)) != NULL) {
    if (strstr(entry->d_name, "Ronny_Toribio_Resume") != NULL) {

      int length_of_filename = strlen(entry->d_name);

      char folder_name[length_of_filename + 1];
      int j = 0;

      for(int i = 0; i < length_of_filename; i++) {
        if ((length_of_filename - 5 ) >= i && i >= 21) {
          // printf("%c", entry->d_name[i]);

          folder_name[j++] = entry->d_name[i];
        }
      }

      folder_name[j] = '\0';
      char path_to_folder[(sizeof(folder_name) + sizeof(path))];

      snprintf(path_to_folder, sizeof(path_to_folder), "%s%s", path, folder_name);

      printf("%s\n", path_to_folder);
      // printf("\n");
      // printf("%s\n", entry->d_name);
    }
  }


  closedir(folder);
  
  return 0;
}

// int getAllFiles() {}

// int populateFolders() {}