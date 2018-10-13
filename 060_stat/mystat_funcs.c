#include "mystats.h"

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

char * getPath(stat_t * st, char * path) {
  //get the path pointed by a link
  char * buff;
  ssize_t nBytes, buffSize;
  buffSize = st->st_size + 1;

  // Sometimes some links may show size = 0
  // So we use PATH_MAX
  // Refer to the example at the bottom of
  // man -s2 readlink
  if (st->st_size == 0) {
    buffSize = PATH_MAX;
  }

  // Allocate space for the path string
  buff = malloc(buffSize);
  if (buff == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  // use readlink to get info on the linked path
  nBytes = readlink(path, buff, buffSize);
  if (nBytes == -1) {
    perror("readlink");
    exit(EXIT_FAILURE);
  }
  // return string
  return buff;
}
void printBasic(stat_t * st, char * type, char * name) {
  // take the obtained stat struct from lstat, file type,
  // and name to print the basic info
  if (S_ISLNK(st->st_mode)) {
    // if the object is a link, get the name pointed by it
    char * link = getPath(st, name);
    printf("  File: %s -> %s\n", name, link);
    free(link);
  }
  else {
    printf("  File: %s\n", name);
  }
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
         st->st_size,
         st->st_blocks,
         st->st_blksize,
         type);
}

void printDevice(stat_t * st) {
  // prints device info obtained from the stat struct
  if (S_ISCHR(st->st_mode) || S_ISBLK(st->st_mode)) {
    // check is it is a special file and if yes, print the type identifier
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %x,%x\n",
           st->st_dev,
           st->st_dev,
           st->st_ino,
           st->st_nlink,
           major(st->st_rdev),
           minor(st->st_rdev));
  }
  else {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
           st->st_dev,
           st->st_dev,
           st->st_ino,
           st->st_nlink);
  }
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
  // print time info as obtained from the stat struct using the time2str provided
  // also refer to the man page for time to know ehat is inside the timespec struct
  // in stat struct
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
  // refer man pages for information
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
