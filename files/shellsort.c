//  gcc shellsort.c -o shellsort -z execstack -fpie -fcf-protection=none
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

void setup()
{
    alarm(60);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void shellsort(unsigned char *shell)
{
    int i, j;
    for (i=2; i<256; i+=2)
        for (j=i; j>=2 && shell[j-2]<shell[j]; j-=2)
        {
            //  swap shell[j-2] and shell[j]
            shell[j-2] ^= shell[j];
            shell[j] ^= shell[j-2];
            shell[j-2] ^= shell[j];
        }
}

int main()
{
    unsigned char *shell;

    setup();

    shell = mmap(NULL, 256, PROT_READ|PROT_WRITE|PROT_EXEC,
        MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    printf("Your shell code: ");
    scanf("%255s", shell);
    shellsort(shell);
    ((void (*)(void))shell)();
}
