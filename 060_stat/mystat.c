#include "mystats.h"

int main(int argc, char ** argv) {
  if (argc < 2) {
    // There should be at least one argument
    printf("Usage: mystat <filepath>");
    exit(EXIT_FAILURE);
  }

  for (int i = 1; i < argc; i++) {  // Loop over arguments
    stat_t filestats;
    // struct stat is typedefed to stat_t

    if (lstat(argv[i], &filestats) != 0) {
      // If lstat returns 0 it succeeds
      perror("mystat: cannot mystat");
      exit(EXIT_FAILURE);
    }

    // string containing file access info, always 10 chars
    char accString[10] = "----------";
    getAccess(&filestats, accString);

    char * fileType = NULL;
    // variable to store the file type which is obtained using the following switch case
    // refer man lstat for information
    switch (filestats.st_mode & S_IFMT) {
      case S_IFBLK:
        fileType = strdup("block special file");
        accString[0] = 'b';
        break;

      case S_IFCHR:
        fileType = strdup("character special file");
        accString[0] = 'c';
        break;

      case S_IFDIR:
        fileType = strdup("directory");
        accString[0] = 'd';
        break;

      case S_IFIFO:
        fileType = strdup("fifo");
        accString[0] = 'p';
        break;

      case S_IFLNK:
        fileType = strdup("symbolic link");
        accString[0] = 'l';
        break;

      case S_IFREG:
        fileType = strdup("regular file");
        accString[0] = '-';
        break;

      case S_IFSOCK:
        fileType = strdup("socket");
        accString[0] = 's';
        break;

      default:
        strdup("unknown");
    }

    // call printBasic to print basic info like name, size, owner etc
    printBasic(&filestats, fileType, argv[i]);
    // call printDevice to print device information
    printDevice(&filestats);
    // call printAccess to print access strings
    printAccess(&filestats, accString);
    // call printTime to print access,modify and change time info
    printTime(&filestats);

    free(fileType);
  }
}
