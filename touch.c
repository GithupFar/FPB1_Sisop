#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
    int i, ret;
    if (argc <= 1) printf(1, "Usage: touch <FILENAME>...\n");
    else {
        for(i = 1; i < argc; i++){
            ret = mknod(argv[i], 0664, 0);
            if (ret != 0){
                printf(1, "Error %d: Failed to touch file %s\n", ret, argv[i]);
                exit();
            }
        }
    }
    exit();
}
