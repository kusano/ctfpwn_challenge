//  gcc writefree.c -o writefree -fpie -fcf-protection=none
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void readline(char *buf, int size)
{
    for (int i=0; i<size-1; i++)
    {
        if (read(0, buf+i, 1)!=1)
            _exit(0);
        if (buf[i]=='\n')
        {
            buf[i] = '\0';
            return;
        }
    }
    buf[size-1] = '\0';
}

int variable(char vc)
{
    int vi = vc-'A';
    if (vi<0 || 26<=vi)
        _exit(0);
    return vi;
}

int main()
{
    char *v[26] = {};
    char buf[32];

    alarm(60);

    for (;;) {
        readline(buf, sizeof buf);
        if (strncmp(buf+1, "=malloc(", 8)==0) {
            int size = atoi(buf+9);
            if (size<=0 || 65536<size)
                break;
            v[variable(buf[0])] = malloc(size);
        } else if (strncmp(buf, "free(", 5)==0) {
            int t = variable(buf[5]);
            free(v[t]);
            v[t] = NULL;
        } else if (strncmp(buf+1, "=read(", 6)==0) {
            int size = atoi(buf+7);
            if (size<=0 || 65536<size)
                break;
            if (v[variable(buf[0])]==NULL)
                break;
            read(0, v[variable(buf[0])], size);
        } else if (strncmp(buf, "exit(", 5)==0) {
            break;
        }
    }
    _exit(0);
}
