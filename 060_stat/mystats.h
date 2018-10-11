#ifndef __MYSTAT_H__
#define __MYSTAT_H__
#include <ctype.h>
#include <grp.h>
#include <limits.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

char * time2str(const time_t * when, long ns);
typedef struct stat stat_t;
char * getPath(stat_t * st, char * path);
void printBasic(stat_t * st, char * type, char * name);
void printDevice(stat_t * st);
void printAccess(stat_t * st, char access[]);
void printTime(stat_t * st);
void getAccess(stat_t * st, char * acc);

#endif
