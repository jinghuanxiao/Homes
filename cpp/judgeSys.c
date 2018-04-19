#include <stdio.h>
int main(int argc,char **argv)
{
    #ifdef __unix
        printf("unix\n");
    #endif
    #ifdef __linux
        printf("Linux\n");
    #endif
    #ifdef __sun
        #ifdef __sparc
                printf("Sun SPARC\n");
        #else
             printf("Sun X86\n");
        #endif
    #endif
    #ifdef _AIX
                printf("AIX\n");
    #endif

    #else

    #ifdef WINVER
        printf("Windows\n");
    #endif

    #endif
    return 0;
}
