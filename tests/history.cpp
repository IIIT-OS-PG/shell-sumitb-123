#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char *argv[])
{
    int fd;
    int len, slen;
	//if(!strcmp())

    fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    do {
        len = tee(STDIN_FILENO, STDOUT_FILENO,
                  INT_MAX, SPLICE_F_NONBLOCK);

        if (len < 0) {
            exit(1);
        } else
            if (len == 0)
                break;

        while (len > 0) {
            slen = splice(STDIN_FILENO, NULL, fd, NULL,
                          len, SPLICE_F_MOVE);
            if (slen < 0) {
                break;
            }
            len -= slen;
        }
    } while (1);

    close(fd);
    exit(0);
}
