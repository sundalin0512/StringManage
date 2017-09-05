#include <stdlib.h>
#include <stdio.h>
#include "manage.h"

int main(int argc, char* argv[])
{ 
    char szBuf[0x10000];
    Initialize(szBuf, 0x10000);
    InsertItem("aaa");
    InsertItem("bbbbb");
    InsertItem("cccccccccc");
    InsertItem("ddddddddddddd");
    InsertItem("eeeeeeeeeeeeeeeeeee");
    InsertItem("fffffffffffffffffffffffffffffffff");
    InsertItem("gggggggggggggggggggggggggggggggggggggggggggggg");
    InsertItem("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh");
    return 0;
}