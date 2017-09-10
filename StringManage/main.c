#include <stdlib.h>
#include <stdio.h>

#include "manage.h"
#include  "view.h"

int main(void)
{
    char szBuf[0x10000];

    Initialize(szBuf, 0x10000);
    ShowWelcome();
    MainFunction();
    
    return 0;
}