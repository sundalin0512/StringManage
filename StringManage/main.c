#include <stdlib.h>
#include <stdio.h>

#include "manage.h"

int main()
{
    char szBuf[0x10000];
    char *szTmp[10] = { 0 };
    int iIndex[10] = { 0 };
    int aryLittleChar[26];
    int aryBigChar[26];
    int iCount = 0;
    int iSearchIndex = 0;
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
    DeleteItemFromIndex(0);
    InsertItem0("kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk");
    Defragment();

    ModifyItemFromString("cccccccccc", "11111");
    ModifyItemFromString("bbbbb", "22222222222222222222");
    InsertItem0("aassxxzz99887766wwqq");
    InsertItem0("aasdasdzz99887766wwqq");
    InsertItem0("adasd99887766asdddaa");
    InsertItem0("adasd99887766asdddaa");
    InsertItem0("adasd99887766asdddaa");
    InsertItem0("adasd99887766asdddaa");
    InsertItem0("adasd99887766asdddaa");
    InsertItem0("adasd99887766asdddaa");
    InsertItem0("adasd99887766asdddaa");
    InsertItem0("adasd99887766asdddaa");
    InsertItem0("adasd99887766asdddaa");
    InsertItem0("adasd99887766asdddaa");
    InsertItem0("adasd99887766asdddaa");
    InsertItem0("adasd99887766asdddaa");
    InsertItem0("adasd99887766asdddaa");
    InsertItem0("adasd99887766asdddaa");
    InsertItem0("adasd99887766asdddaa");
    InsertItem0("adasd99887766asdddaa");
    InsertItem0("adasd99887766asdddaa");
    InsertItem0("adasd99887766asdddaa");
    InsertItem0("adasd99887766asdddaa");

    iSearchIndex =  SearchItemFromSubstr(&szTmp, &iIndex, &iCount, "99887766");
    SearchNext(&szTmp, &iIndex, &iCount, "99887766", iSearchIndex);

    CountCharacters(aryLittleChar, aryBigChar, &iCount);

    return 0;
}