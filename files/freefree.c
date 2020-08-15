//  gcc freefree.c -o freefree -fpie -fcf-protection=none
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void setup()
{
    alarm(60);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

int variable(char vc)
{
    int vi = vc-'A';
    if (vi<0 || 26<=vi) {
        printf("invalid variable\n");
        exit(0);
    }
    return vi;
}

int main()
{
    char *v[26] = {};
    char buf[16];

    setup();

    printf(
        "free()-free since free() is a dangerous function.\n"
        "usage:\n"
        "X=malloc(123)\n"
        "gets(X)\n"
        "puts(X)\n"
        "exit(0)\n"
    );

    for (;;) {
        printf("> ");
        fgets(buf, sizeof buf, stdin);

        if (strncmp(buf+1, "=malloc(", 8)==0) {
            int size = atoi(buf+9);
            if (size<=0 || 4096<size) {
                printf("invalid size\n");
                exit(0);
            }
            v[variable(buf[0])] = malloc(size);
        } else if (strncmp(buf, "gets(", 5)==0) {
            gets(v[variable(buf[5])]);
        } else if (strncmp(buf, "puts(", 5)==0) {
            puts(v[variable(buf[5])]);
        } else if (strncmp(buf, "exit(", 5)==0) {
            exit(0);
        } else {
           printf("invalid command\n");
        }
    }
}
