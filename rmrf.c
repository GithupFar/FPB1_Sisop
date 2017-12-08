#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int remove_directory(const char *path) {
   DIR *d = opendir(path);
   size_t path_len = strlen(path);
   int r = -1;
   if (d) {
      struct dirent *p;
      r = 0;
      while (!r && (p=readdir(d))) {
          int r2 = -1;
          char *buf;
          size_t len;
          if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
             continue;

          len = path_len + strlen(p->d_name) + 2; 
          buf = malloc(len);

          if (buf) {
             struct stat statbuf;
             snprintf(buf, len, "%s/%s", path, p->d_name);
             if (!stat(buf, &statbuf)) {
                if (S_ISDIR(statbuf.st_mode)) {
                   r2 = remove_directory(buf);
                }
                else {
                   r2 = unlink(buf);
                }
             }
             free(buf);
          }
          r = r2;
      }
      closedir(d);
   }
   if (!r) {
      r = rmdir(path);
   }
   return r;
}

int main(int argc, char *argv[]){
    int r = 0;
    struct stat st;
    if(argc < 2){
        fprintf(stderr, "rmrf: Remove a directory\nUsage: rmrf <DIR NAME>\n");
        return 0;
    }
    for(int i = 1; i < argc; i++){
        r = stat(argv[i], &st);
        if(r < 0){
            fprintf(stderr, "rmrf: Unable to remove %s\n", argv[i]);
            return r;
        }
        if(!S_ISDIR(st.st_mode)){
            //fprintf(stderr, "rmrf: %s not a directory\n", argv[i]);
            r = unlink(argv[i]);
            return r;
        }
        r = remove_directory(argv[i]);
        if(r < 0){
            fprintf(stderr, "rmrf: Error occured while removing %s\n", argv[i]);
            return r;
        }
    }
    return 0;
}
