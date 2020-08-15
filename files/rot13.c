//  gcc rot13.c -o rot13 -no-pie -fcf-protection=none
#include <stdio.h>
#include <unistd.h>

void setup()
{
    alarm(60);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

int main()
{
    char buf[0x100] = "";
    int i = 0;

    setup();

    fgets(buf, sizeof buf, stdin);

    for (i=0; i<0x100; i++) {
        int d = 0;
        if ('A'<=buf[i] && buf[i]<='M' ||
            'a'<=buf[i] && buf[i]<='m')
            d = +13;
        if ('N'<=buf[i] && buf[i]<='Z' ||
            'n'<=buf[i] && buf[i]<='z')
            d = -13;
        buf[i] += d;
    }

    printf(buf);
    printf("https://en.wikipedia.org/wiki/ROT13\n");
}
