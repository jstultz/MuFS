#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define FUSE_USE_VERSION 26
#include <fuse.h>

static int mufs_getattr(const char *file, struct stat *attr);

static int mufs_readlink(const char *file, char *tpath, size_t sz);

static int mufs_open(const char *file, struct fuse_file_info *finfo);

static int mufs_read(const char *file, char *data, size_t sz, off_t off,
                     struct fuse_file_info *finfo);

static int mufs_release(const char *file, struct fuse_file_info *finfo);

static int mufs_opendir(const char *file, struct fuse_file_info *finfo);

static int mufs_readdir(const char *file, void *buf, fuse_fill_dir_t filler,
                        off_t off, struct fuse_file_info *finfo);

static void * mufs_init(struct fuse_conn_info *conn);

static void mufs_destroy(void *pdata);

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

static int mufs_getattr(const char *file, struct stat *attr)
{
  /* TODO Is this a real media file, or one of our crazy bullshit made up VFS
     folders? For now, do something really really stupid */
  int fnamelen = strlen(file);
  if (strncmp(".mp3", file + fnamelen - 4, 4))
  {
    // Probably not an MP3
    attr->st_mode = 0666;
  }
  else
  {
    // Supposedly an MP3, find the real shit off the real filesystem.
    //XXX for now though just to see if the code works, set some other mode
    attr->st_mode = 0644;
  }

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

