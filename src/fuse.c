#include <common.h>
#define FUSE_USE_VERSION 26
#include <fuse.h>

/* Populates struct with info from filepath. */
static int parsepath(const char *file, songdata *info)
{
  char path[4096];
  int numtoks = 0;
  char *pathtok;
  char *lasttok;
  int i;

  strncpy(path, file, sizeof(path) - 1);
  pathtok = strtok(path, "/");

  while (pathtok != NULL)
  {
    numtoks++;
    if (numtoks % 2 == 0)
    {
      /* This is the name of the artist or genre or whatever. Find out which it
         is, then add it to the struct */
      for (i = 0; i < NUM_METATYPES; i++)
      {
        if (!strcmp(lasttok, metatypestrings[i]))
        {
          strncpy(info->metadata[i], pathtok, MAXLEN-1);
          break;
        }
      }
    }
    lasttok = pathtok;
    pathtok = strtok(NULL, "/");
  }
  
  if (numtoks % 2)
  {
    for (i = 0; i < NUM_METATYPES; i++)
    {
      if (!strcmp(lasttok, metatypestrings[i]))
        break;
    }
    if (i == NUM_METATYPES)
    {
      /* This is not a directory, probably a song */
      strncpy(info->title, lasttok, MAXLEN-1);
    }
  }

  return 0;
}

static int mufs_getattr(const char *file, struct stat *attr)
{
  songdata info;
  memset(attr, 0, sizeof(*attr));
  memset(&info, 0, sizeof(info));

  parsepath(file, &info);

  if (info.title[0])
  {
    attr->st_mode = S_IFLNK | 0444;
    attr->st_nlink = 1;
  }
  else
  {
    attr->st_mode = S_IFDIR | 0555;
    attr->st_nlink = 1; // TODO useful to set this to number of songs inside
  }
  /* TODO setting the timestamps would be potentially useful.
     For files, set to the time the file was added to the database.
     For folders, set to the most recent time a file inside was added. */
  return 0;
}

static int mufs_readlink(const char *file, char *tpath, size_t sz)
{
  return 0;
}

static int mufs_open(const char *file, struct fuse_file_info *finfo)
{
  return 0;
}

static int mufs_read(const char *file, char *data, size_t sz, off_t off,
                     struct fuse_file_info *finfo)
{
  return 0;
}

static int mufs_release(const char *file, struct fuse_file_info *finfo)
{
  return 0;
}

static int mufs_opendir(const char *file, struct fuse_file_info *finfo)
{
  return 0;
}

static int mufs_readdir(const char *file, void *buf, fuse_fill_dir_t filler,
                        off_t off, struct fuse_file_info *finfo)
{
  return 0;
}

static void * mufs_init(struct fuse_conn_info *conn)
{
  return NULL;
}

static void mufs_destroy(void *pdata)
{
}


struct fuse_operations mufs_oper = {
  .getattr = mufs_getattr,
  .readlink = mufs_readlink,
  // mknod = mufs_mknod, MuFS is read-only
  // mkdir = mufs_mkdir,
  // symlink = mufs_symlink,
  // unlink = mufs_unlink,
  // rmdir = mufs_rmdir,
  // rename = mufs_rename,
  // link = mufs_link,
  // chmod = mufs_chmod,
  // chown = mufs_chown,
  // truncate = mufs_truncate,
  .open = mufs_open,
  .read = mufs_read,
  // write = mufs_write,
  // statfs = mufs_statfs,
  .release = mufs_release,
  // fsync = mufs_fsync,
  // flush = mufs_flush,
  .opendir = mufs_opendir,
  .readdir = mufs_readdir,
  // releasedir = mufs_releasedir,
  // fsyncdir = mufs_fsyncdir,
  .init = mufs_init,
  .destroy = mufs_destroy,
  // access = mufs_access,
  // create = mufs_create,
  // ftruncate = mufs_truncate,
  // fgetattr = mufs_fgetattr,
  // lock = mufs_lock,
  // utimens = mufs_utimens,
  // bmap = mufs_bmap
};

int main (int argc, char **argv)
{
  printf("Success!\n");
  return fuse_main(argc, argv, &mufs_oper, NULL); 
}


