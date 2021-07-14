#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFSIZE 4096

int
main(int argc, char **argv)
{
    size_t size = BUFSIZE;
    char buf[BUFSIZE + 3];
    char *ptr = &buf[0];
    int plen = 0, p = 0;

    if (argc == 2) {
        size_t len = strlen(argv[1]);

        if (len && size > len) {
            memcpy(ptr, argv[1], len);
            ptr += len;
            plen = (int)len;
        }
    }
    memcpy(&buf[BUFSIZE], "...", 3);

    while (1) {
        int r = read(0, ptr + p, BUFSIZE - p);

        if (r == -1) {
            switch (errno) {
            case EINTR:
            case EAGAIN:
                continue;
            default:
                break;
            }
        }
        if (!r) // skip garbage
            break;
        for (int i = p; i < p + r; i++) {
            if (ptr[i] != '\n')
                continue;

            if (i > p)
                (void)!write(1, buf, plen + i);

            for (; i < p + r && ptr[i] == '\n'; i++)
                ;

            memmove(ptr, ptr + i, p + r - i);
            r -= i - p; i = 0; p = 0;
        }
        p += r;

        if (p == BUFSIZE) {
            (void)!write(1, buf, plen + BUFSIZE);
            p = 0;
        }
    }
}
