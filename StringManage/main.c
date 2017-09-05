#include <stdlib.h>
#include <stdio.h>
#include "manage.h"

int main(int argc, char* argv[])
{ 
    char szBuf[0x10000];
    Initialize(szBuf, 0x10000);
    InsertItem("abcde");
    return 0;
}