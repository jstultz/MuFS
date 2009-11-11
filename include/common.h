#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <mysql/mysql.h>

typedef char boolean;
#define TRUE (1)
#define FALSE (0)
#define MAXLEN (256)

static char *metatypestrings[] = {
  "artists",
  "albums",
  "genres",
  "years"
};

typedef enum
{
  ARTIST,
  ALBUM,
  GENRE,
  YEAR,
  NUM_METATYPES
} metatype;

typedef struct songdata {
  char title[MAXLEN];
  char metadata[NUM_METATYPES][MAXLEN];
  metatype trailingmeta;
  int tracknum;
} songdata;

typedef struct mufscontext {
  FILE *logfile;
  MYSQL *db;
} mufscontext;

#endif
