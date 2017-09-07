#include <stdlib.h>
#include <stdio.h>
#include "manage.h"

int main()
{ 
    char szBuf[0x100];
    Initialize(szBuf, 0x100);
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


    ModifyItemFromString("cccccccccc", "11111");
    ModifyItemFromString("bbbbb", "22222222222222222222");


    return 0;
}