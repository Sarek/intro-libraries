#include <stdio.h>
#include <unistd.h>

int main()
{
    uid_t euid = geteuid();
    printf("Effective user ID: %d\n", euid);
}
