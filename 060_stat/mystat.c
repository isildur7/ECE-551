#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

typedef struct stat stat_t;

void printBasic(stat_t * st, char * type, char * name) {
  // take the obtained stat struct from lstat, file type,
  // and name to print the basic info
  printf("  File: %s\n", name);
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
         st->st_size,
         st->st_blocks,
         st->st_blksize,
         type);
  printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
         st->st_dev,
         st->st_dev,
         st->st_ino,
         st->st_nlink);
}

void printAccess(stat_t * st, char access[]) {
  // print access info using acess string and ids from stat struct
  // getpwuid returns a struct, from which the username has to be the fourth conversion
  // getpwuid(st->st_uid)->pw_name gives that
  // Similarly for 6th conversion with getgrgid
  printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
         (st->st_mode & ~S_IFMT),
         access,
         st->st_uid,
         getpwuid(st->st_uid)->pw_name,
         st->st_gid,
         getgrgid(st->st_gid)->gr_name);
}

void printTime(stat_t * st) {
  char *accesstime, *modifytime, *changetime;
  accesstime = time2str(&st->st_atim.tv_sec, st->st_atim.tv_nsec);
  modifytime = time2str(&st->st_mtim.tv_sec, st->st_mtim.tv_nsec);
  changetime = time2str(&st->st_ctim.tv_sec, st->st_ctim.tv_nsec);
  printf("Access: %s\n", accesstime);
  printf("Modify: %s\n", modifytime);
  printf("Change: %s\n", changetime);
  printf(" Birth: -\n");
  free(accesstime);
  free(modifytime);
  free(changetime);
}

void getAccess(stat_t * st, char * acc) {
  // fill access string according to description of permissions
  if (st->st_mode & S_IRUSR) {
    acc[1] = 'r';
  }
  if (st->st_mode & S_IWUSR) {
    acc[2] = 'w';
  }
  if (st->st_mode & S_IXUSR) {
    acc[3] = 'x';
  }
  if (st->st_mode & S_IRGRP) {
    acc[4] = 'r';
  }
  if (st->st_mode & S_IWGRP) {
    acc[5] = 'w';
  }
  if (st->st_mode & S_IXGRP) {
    acc[6] = 'x';
  }
  if (st->st_mode & S_IROTH) {
    acc[7] = 'r';
  }
  if (st->st_mode & S_IWOTH) {
    acc[8] = 'w';
  }
  if (st->st_mode & S_IXOTH) {
    acc[9] = 'x';
  }
}

int main(int argc, char ** argv) {
  stat_t filestats;

  if (argc != 2) {
    // There should be only one argument
    printf("Usage: mystat <filepath>");
    exit(EXIT_FAILURE);
  }

  if (lstat(argv[1], &filestats) != 0) {
    // If lstat returns 0 it succeeds
    perror("mystat: cannot mystat:");
    exit(EXIT_FAILURE);
  }

  char accString[10] = "----------";
  getAccess(&filestats, accString);
  // string containing file access info, always 10 chars
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
      accString[0] = '\0';
  }

  // call printBasic to print basic info like name, size, owner etc
  printBasic(&filestats, fileType, argv[1]);
  // call printAccess to print access strings
  printAccess(&filestats, accString);
  // call printTime to print access,modify and change time info
  printTime(&filestats);
  free(fileType);
}
