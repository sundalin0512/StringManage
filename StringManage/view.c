#include "view.h"
#include "manage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAXSTRLEN
#define MAXSTRLEN 256
#endif // !MAXSTRLEN

int InsertFunction();
int DeleteFunction();
int ModifyFunction();
int SearchFunction();
int CharacterCountFunction();
int StorageInfoFunction();
int DefragmentFunction();

void FormatString(char *szString)
{
    int iSize = strnlen(szString, MAXSTRLEN);
    if (iSize == 0)
        return;
    if (szString[iSize] == '\0')
        return;
    szString[iSize - 1] = '\0';
}


void ShowWelcome()
{
    printf_s("欢迎使用动态存储系统！\r\n\n\n");
    return 0;
}

void MainFunction()
{
    int iSelect = 0;
MAINSTART:
    printf_s("请输入要使用的功能的编号：\r\n\
            \r\t1:增加字符串\r\n\
            \r\t2:删除字符串\r\n\
            \r\t3:修改字符串\r\n\
            \r\t4:查询字符串\r\n\
            \r\t5:显示统计信息\r\n\
            \r\t6:显示存储信息\r\n\
            \r\t7:碎片整理\r\n\
            \r\t0:退出系统\r\n");
    scanf_s("%d", &iSelect);
    setvbuf(stdin, NULL, _IONBF, 0);
    switch (iSelect)
    {
    case 1:
        InsertFunction();
        break;
    case 2:
        DeleteFunction();
        break;
    case 3:
        ModifyFunction();
        break;
    case 4:
        SearchFunction();
        break;
    case 5:
        CharacterCountFunction();
        break;
    case 6:
        StorageInfoFunction();
        break;
    case 7:
        DefragmentFunction();
        break;
    case 0:
        return;
    default:
        printf_s("无效输入，请重试！\r\n");
        goto MAINSTART;
    }
    goto MAINSTART;
}

int ShowInsertResult(int iResult, char* szInsertItem)
{
    if (iResult == 0)
    {
        printf_s("插入成功\r\n");
        printf_s("%s\r\n", szInsertItem);
    }
    else if (iResult == -1)
    {
        printf_s("插入失败,没有足够的空间\r\n\
                    \r请进行碎片整理后重试\r\n");
    }
    else if (iResult == -2)
    {
        printf_s("非法ID\r\n");
    }
    return 0;
}

int InsertFunction()
{
    int iSelect = 0;
    int iInsertPosition = 0;
    char szInsertString[MAXSTRLEN] = "";
    int iRet = 0;

INSERTFUNCBEGIN:
    printf_s("\t1:在指定位置插入字符串\r\n\
            \r\t2:在末尾增加字符串\r\n\
            \r\t0:返回上一级\r\n");
    scanf_s("%d", &iSelect);
    setvbuf(stdin, NULL, _IONBF, 0);

    if (iSelect == 1)
    {
        printf_s("要插入的位置:");
        scanf_s("%d", &iInsertPosition);
        printf_s("输入字符串:\r\n");
        setvbuf(stdin, NULL, _IONBF, 0);
        fgets(szInsertString, MAXSTRLEN, stdin);
        FormatString(szInsertString);
        iRet = InsertItem(szInsertString, iInsertPosition);
        ShowInsertResult(iRet, szInsertString);
    }
    else if (iSelect == 2)
    {
        printf_s("输入字符串:\r\n");
        setvbuf(stdin, NULL, _IONBF, 0);
        fgets(szInsertString, MAXSTRLEN, stdin);
        FormatString(szInsertString);
        iRet = InsertItem0(szInsertString);
        ShowInsertResult(iRet, szInsertString);
    }
    else if (iSelect == 0)
    {
        return -1;
    }
    else
    {
        printf_s("输入有误,请重新输入\r\n");
        goto INSERTFUNCBEGIN;
    }

    return 0;
}

int ShowDeleteResult(int iResult, char *szDeleteItem)
{
    if (iResult == 0)
    {
        printf_s("删除成功\r\n");
        printf_s("%s\r\n", szDeleteItem);
    }
    else
    {
        printf_s("删除失败,请检查输入\r\n");
    }
    return 0;
}

int DeleteFunction()
{
    int iSelect = 0;
    int iDeleteIndex = 0;
    char szDeleteString[MAXSTRLEN] = "";
    int iRet = 0;

DELETEFUNCBEGIN:
    printf_s("1:删除指定位置的字符串\r\n\
            \r2:删除指定字符串\r\n\
            \r0:返回上一级\r\n");
    scanf_s("%d", &iSelect);
    setvbuf(stdin, NULL, _IONBF, 0);
    if (iSelect == 1)
    {
        printf_s("要删除的字符串的位置:");
        scanf_s("%d", &iDeleteIndex);
        setvbuf(stdin, NULL, _IONBF, 0);
        iRet = DeleteItemFromIndex(iDeleteIndex - 1, szDeleteString);
        ShowDeleteResult(iRet, szDeleteString);
    }
    else if (iSelect == 2)
    {
        printf_s("要删除的字符串:\r\n");
        scanf_s("%s", szDeleteString, MAXSTRLEN);
        setvbuf(stdin, NULL, _IONBF, 0);
        iRet = DeleteItemFromString(szDeleteString);
        ShowDeleteResult(iRet, szDeleteString);
    }
    else if (iSelect == 0)
    {
        return -1;
    }
    else
    {
        printf_s("输入有误,请重新输入\r\n");
        goto DELETEFUNCBEGIN;
    }
    return 0;
}

int ShowModifyResult(int iRet, char *szModifyItem)
{
    if (iRet == 0)
    {
        printf_s("修改成功\r\n");
        printf_s("%s\r\n", szModifyItem);
    }
    else
    {
        printf_s("修改失败,未进行修改\r\n");
    }
    return 0;
}

int ModifyFunction()
{
    int iSelect = 0;
    int iModifyIndex = 0;
    char szPreString[MAXSTRLEN] = "";
    char szModifyString[MAXSTRLEN] = "";
    int iRet = 0;

MODIFYFUNCBEGIN:
    printf_s("1:修改指定位置的字符串\r\n\
            \r2:修改制定字符串\r\n\
            \r0:返回上一级\r\n");
    scanf_s("%d", &iSelect);
    setvbuf(stdin, NULL, _IONBF, 0);
    if (iSelect == 1)
    {
        printf_s("要修改的字符串的位置:");
        scanf_s("%d", &iModifyIndex);
        setvbuf(stdin, NULL, _IONBF, 0);
        printf_s("新的字符串:\r\n");
        setvbuf(stdin, NULL, _IONBF, 0);
        fgets(szModifyString, MAXSTRLEN, stdin);
        FormatString(szModifyString);
        iRet = ModifyItemFormIndex(iModifyIndex, szModifyString);
        ShowModifyResult(iRet, szModifyString);
    }
    else if (iSelect == 2)
    {
        printf_s("要修改的字符串:\r\n");
        setvbuf(stdin, NULL, _IONBF, 0);
        fgets(szPreString, MAXSTRLEN, stdin);
        FormatString(szPreString);
        printf_s("新的字符串:\r\n");
        setvbuf(stdin, NULL, _IONBF, 0);
        fgets(szModifyString, MAXSTRLEN, stdin);
        FormatString(szModifyString);
        iRet = ModifyItemFromString(szPreString, szModifyString);
        ShowModifyResult(iRet, szModifyString);
    }
    else if (iSelect == 0)
    {
        return -1;
    }
    else
    {
        printf_s("非法输入\r\n");
        goto MODIFYFUNCBEGIN;
    }
    return 0;
}

int SearchFunction()
{
    int iSelect = 0;
    int iSearchIndex = 0;
    char szSubstr[MAXSTRLEN] = "";
    int iRet = 0;
    //int SearchItemFromIndex(char *szStr, int iIndex);

    //int SearchItemFromSubstr(char *szStr[10], int iIndex[10], int *iCount, char * substr);
MODIFYFUNCBEGIN:
    printf_s("1:根据ID查询\r\n\
            \r2:模糊查找\r\n\
            \r0:返回上一级\r\n");
    scanf_s("%d", &iSelect);
    setvbuf(stdin, NULL, _IONBF, 0);
    if (iSelect == 1)
    {
        char szSearchString[MAXSTRLEN] = "";
        printf_s("要查找的字符串的位置:");
        scanf_s("%d", &iSearchIndex);
        setvbuf(stdin, NULL, _IONBF, 0);
        iRet = SearchItemFromIndex(szSearchString, iSearchIndex);
        if (iRet == 0)
        {
            printf_s("%s\r\n", szSearchString);
        }
        else
        {
            printf_s("未找到\r\n");
        }
    }
    else if (iSelect == 2)
    {
        char *szTmp[10] = { 0 };
        int iIndex[10] = { 0 };
        int iCount = 0;
        printf_s("要查找的子字符串:\r\n");
        setvbuf(stdin, NULL, _IONBF, 0);
        fgets(szSubstr, MAXSTRLEN, stdin);
        FormatString(szSubstr);
        iSearchIndex = SearchItemFromSubstr(szTmp, iIndex, &iCount, szSubstr);
        if (iSearchIndex == -1)
        {
            printf_s("未找到\r\n");
        }
        else
        {
            int i = 0;
        SEARCHPRINT:
            for (i = 0; i < iCount; i++)
            {
                printf_s("%d\t:\t%s\r\n", iIndex[i], szTmp[i]);
            }
            iSearchIndex = SearchNext(szTmp, iIndex, &iCount, szSubstr, iSearchIndex);
            if (iSearchIndex != -1)
            {
                goto SEARCHPRINT;
            }
        }
    }
    else if (iSelect == 0)
    {
        return -1;
    }
    else
    {
        printf_s("非法输入\r\n");
        goto MODIFYFUNCBEGIN;
    }
    return 0;
}

int CharacterCountFunction()
{
    //int CountCharacters(int aryLittleChar[26], int aryBigChar[26], int *iCount);
    int aryLittleChar[26];
    int aryBigChar[26];
    int iCount;
    int i = 0;
    CountCharacters(aryLittleChar, aryBigChar, &iCount);
    printf_s("字母\t\t次数\t\t频率\r\n");
    for (i = 'a'; i <= 'z'; i++)
    {
        printf_s("%c\t%d\t%.2f%%\r\n", (char)i, aryLittleChar[i - 'a'], aryLittleChar[i - 'a'] * 1. / iCount*100);
    }
    for (i = 'A'; i <= 'Z'; i++)
    {
        printf_s("%c\t%d\t%.2f%%\r\n", (char)i, aryLittleChar[i - 'A'], aryLittleChar[i - 'A'] * 1. / iCount*100);
    }
    return 0;
}

int StorageInfoFunction()
{
    //int GetStorageInfo(char *szMemoryInfo[], int *iCount);
    char *szMemoryInfo = NULL;
    int iMemoryUse = 0;
    GetStorageInfo(&szMemoryInfo, &iMemoryUse);
    printf_s("共使用%d字节\r\n");
    printf_s("%s\r\n", szMemoryInfo);
    return 0;
}

int DefragmentFunction()
{
    Defragment();
    printf_s("整理完成\r\n");
}