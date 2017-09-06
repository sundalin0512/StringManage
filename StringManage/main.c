#include <stdlib.h>
#include <stdio.h>
#include "manage.h"

int main(int argc, char* argv[])
{ 
    char szBuf[0x10000];
    Initialize(szBuf, 0x10000);
    InsertItem0("aaa");
    InsertItem0("bbbbb");
    InsertItem0("cccccccccc");
    InsertItem0("ddddddddddddd");
    InsertItem0("eeeeeeeeeeeeeeeeeee");
    InsertItem0("fffffffffffffffffffffffffffffffff");
    InsertItem0("gggggggggggggggggggggggggggggggggggggggggggggg");
    InsertItem0("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh");

    DeleteItemFromString("eeeeeeeeeeeeeeeeeee");
    DeleteItemFromString("fffffffffffffffffffffffffffffffff");
    DeleteItemFromString("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh");


    InsertItem0("ZZZZZZZZZZ");
    InsertItem0("gggggggggggggggggggggggggggggggggggggggggggggg");

    return 0;
}