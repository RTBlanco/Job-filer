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
  char downloads[] = "/Users/ronnytoribio/Downloads";
  char resume_name[] = "Ronny Toribio Resume.pdf";
  char cover_letter_name[] = "Ronny Toribio CoverLetter.pdf";
  
  folder = opendir(downloads);
  
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

          folder_name[j++] = entry->d_name[i];
        }
      }

      folder_name[j] = '\0';
      
      char path_to_folder[(sizeof(folder_name) + sizeof(path))];
      snprintf(path_to_folder, sizeof(path_to_folder), "%s%s", path, folder_name);


      char src[(sizeof(downloads) + sizeof(entry->d_name))];
      snprintf(src, sizeof(src), "%s/%s", downloads, entry->d_name);

      char dest[(sizeof(path) + sizeof(resume_name) + sizeof(folder_name))];
      snprintf(dest, sizeof(dest),"%s/%s/%s",path , folder_name , resume_name);



      if (mkdir(path_to_folder, 0777) == 0) {
        printf("Folder created successfully.\n");

        if (rename(src, dest) != 0) {
          perror("Failed to move file");
        } else {
          printf("Done.\n");
        }

      } else {
        printf("Failed to create folder.\n");
      }
    }
  }


  closedir(folder);
  
  return 0;
}
