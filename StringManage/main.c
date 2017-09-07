#include <stdlib.h>
#include <stdio.h>

#include "manage.h"

int main()
{ 
    char szBuf[0x10000];
    char szTmp[256];
    int iIndex = 0;
    int aryLittleChar[26];
    int aryBigChar[26];
    int iCount = 0;
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


    ModifyItemFromString("cccccccccc", "11111");
    ModifyItemFromString("bbbbb", "22222222222222222222");
    InsertItem0("aassxxzz99887766wwqq");

    SearchItemFromSubstr(szTmp, &iIndex, "99887766");

    CountCharacters(aryLittleChar, aryBigChar, &iCount);

    return 0;
}