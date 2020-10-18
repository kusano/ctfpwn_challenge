//  gcc shellsort.c -o shellsort -z execstack -fpie -fcf-protection=none
#include <stdio.h>
#include <unistd.h>

void setup()
{
    alarm(60);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

unsigned char shell[256];

void shellsort()
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
    setup();

    printf("Your shell code: ");
    scanf("%255s", shell);
    shellsort();
    ((void (*)(void))shell)();
}
