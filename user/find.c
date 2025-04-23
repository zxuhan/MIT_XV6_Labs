#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fs.h"

void find(char *path, char *filename) {
    int fd;
    struct stat st;
    struct dirent de;
    char buf[512];

    if ((fd = open(path, O_RDONLY)) < 0) {
        fprintf(2, "find: can't open %s\n", path);
        return;
    }

    if (fstat(fd, &st) < 0) {
        fprintf(2, "find: can't fstat %s\n", path);
        close(fd);
        return;
    }

    switch(st.type) {
    case T_DEVICE:
    case T_FILE:
        fprintf(2, "Usage: find directory file\n");
        break;
    case T_DIR:
        if (strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)) {
            printf("find: path too long\n");
            break;
        }

        strcpy(buf, path);
        char *p = buf + strlen(path);
        *p++ = '/';

        while (read(fd, &de, sizeof(de)) == sizeof(de)) {
            if (de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) {
                continue;
            }
            // de.name isn't null-terminated.
            int len = strlen(de.name);
            memmove(p, de.name, len);
            p[len] = 0;

            if (stat(buf, &st) < 0) {
                fprintf(2, "find: can't stat %s\n", buf);
                continue;
            }

            if (st.type == T_FILE && strcmp(de.name, filename) == 0) {
                printf("%s\n", buf);
            } else if (st.type == T_DIR) {
                find(buf, filename);
            }
        }
    }
    close(fd);
}

int main(int argc, char *argv[]) {
    
    if (argc != 3) {
        fprintf(2, "Usage: find directory file\n");
        exit(1);
    }

    find(argv[1], argv[2]);

    exit(0);
}