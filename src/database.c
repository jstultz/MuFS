#include <database.h>

int dbinit(mufscontext *ctx)
{
  int status;
  if (status = mysql_library_init(0, NULL, NULL))
    return status;
  ctx->db = mysql_init(NULL);
  if (ctx->db == NULL)
    return -1;
  ctx->db = mysql_real_connect(ctx->db,   // MYSQL struct pointer
                               NULL,      // hostname (local machine)
                               NULL,      // user (current user)
                               NULL,      // password
                               "mufs",    // database name
                               0,         // port number
                               NULL,      // unix socket
                               0);        // client_flag options
  return 0;
}

int dbdestroy(mufscontext *ctx)
{
  mysql_close(ctx->db);
  ctx->db = NULL;
  mysql_library_end();
  return 0;
}
