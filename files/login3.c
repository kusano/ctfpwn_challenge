//  gcc login3.c -o login3 -fno-stack-protector -no-pie -fcf-protection=none
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char *gets(char *s);

void setup()
{
    alarm(60);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

int main()
{
    char id[0x20] = "";

    setup();

    printf("ID: ");
    gets(id);

    if (strcmp(id, "admin") == 0)
        printf("Login Succeeded\n");
    else
        printf("Invalid ID\n");
}
