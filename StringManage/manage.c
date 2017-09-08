#include "manage.h"

#include <stdlib.h>
#include <string.h>

//  ((int*)szBuf)[0] = iSize;    数组字节数

//  fill在前，empty在后
//  ((int*)szBuf)[1]    ->      fill数组（位置，大小）   pFillList
//  位置大小对数量 = pFillList[0]
//  位置 = pFillList[iIndex * 2 + 1]
//  大小 = pFillList[iIndex * 2 + 2]
//  ((int*)szBuf)[2]    ->      empty数组（位值，大小）  pEmptyList
//  位置大小对数量 = pEmptyList[0]
//  位置 = pEmptyList[iIndex * 2 + 1]
//  大小 = pEmptyList[iIndex * 2 + 2]

#define MAXSTRLEN 256
char *pStrBuf;
int *pSize;
int *pFillList;
int *pEmptyList;

// 初始化
int Initialize(char *szBuf, int size)
{
    pSize = (int*)szBuf;
    pStrBuf = szBuf;
    *pSize = size;
    *(int*)&szBuf[4] = (int)&szBuf[12];
    *(int*)&szBuf[8] = (int)&szBuf[16];
    pFillList = (int*)*(int*)&szBuf[4];
    pEmptyList = (int*)*(int*)&szBuf[8];
    pFillList[0] = 0;
    pEmptyList[0] = 0;
    return 0;
}

// 寻找足够大小的空空间
// 返回 空节点的下标
// -1表示没有足够的空间
int FindEmptyPlace(int iSize)
{
    int i = 0;
    for (i = 0; i < pEmptyList[0]; i++)
    {
        if (iSize < pEmptyList[2 * i + 2])
        {
            return i;
        }
    }
    return -1;
}

// 0找不到，1找到
int KMPSearch(char *szStr, char *szMatchStr)
{
    int iIndex = 0;
    int  i = 0;
    int j = 0;

    for (i = 0; i < (int)strnlen(szStr, MAXSTRLEN) - (int)strnlen(szMatchStr, MAXSTRLEN) + 1; i++)
    {
        iIndex = i;
        if (szStr[i] == szMatchStr[j])
        {
            do
            {
                i++;
                j++;
            } while (j != strnlen(szMatchStr, MAXSTRLEN) && szStr[i] == szMatchStr[j]);
            if (j == strnlen(szMatchStr, MAXSTRLEN))
            {
                return 1;
            }
            else
            {
                i = iIndex + 1;
                j = 0;
            }
        }
    }

    return 0;
}

// 返回 iPosition后的空节点的下标
int FindEmptyListInsertIndex(int iPosition)
{
    int i = 0;
    if (pEmptyList[0] == 0)
    {
        return 0;
    }
    for (i = 0; i < pEmptyList[0]; i++)
    {
        if (iPosition < pEmptyList[i * 2 + 1])
        {
            return i;
        }
    }
    return i;
}

// 合并空节点
int TryCombineEmptyList(int iIndex)
{
    if (iIndex < pEmptyList[0] - 1)
    {
        if (pEmptyList[iIndex * 2 + 1] + pEmptyList[iIndex * 2 + 2] == pEmptyList[iIndex * 2 + 3])
        {
            int iMoveOffset = 2 * sizeof(int*);
            int iCopyOffset = (iIndex * 2 + 3) * sizeof(int);
            int *dest = (int*)((int)pEmptyList + iCopyOffset);
            int *src = (int*)((int)pEmptyList + iCopyOffset + iMoveOffset);
            int iCount = (pEmptyList[0] - iIndex - 1) * 2 * sizeof(int);
            pEmptyList[iIndex * 2 + 2] += pEmptyList[iIndex * 2 + 4];
            memmove_s(dest, iCount, src, iCount);
            pEmptyList[0]--;
            
        }
    }
    if (iIndex != 0)
    {
        if (pEmptyList[iIndex * 2 - 1] + pEmptyList[iIndex * 2] == pEmptyList[iIndex * 2 + 1])
        {
            int iMoveOffset = 2 * sizeof(int*);
            int iCopyOffset = (iIndex * 2 + 1) * sizeof(int);
            int *dest = (int*)((int)pEmptyList + iCopyOffset);
            int *src = (int*)((int)pEmptyList + iCopyOffset + iMoveOffset);
            int iCount = (pEmptyList[0] - iIndex - 1) * 2 * sizeof(int);
            pEmptyList[iIndex * 2] += pEmptyList[iIndex * 2 + 2];
            memmove_s(dest, iCount, src, iCount);
            pEmptyList[0]--;

        }
    }
    return 0;
}

// 增加空节点
int InsertEmptyList(int iPosition, int iSize)
{
    int iIndex = FindEmptyListInsertIndex(iPosition);
    int iMoveOffset = 2 * sizeof(int*);
    int iEmptyListTail = (int)pEmptyList + (2 * pEmptyList[0] + 1) * sizeof(int) + iMoveOffset;
    int iAryTail = (int)pSize + *pSize;
    if (iEmptyListTail <= iAryTail)
    {
        int iCopyOffset = (iIndex * 2 + 1) * sizeof(int);
        int *dest = (int*)((int)pEmptyList + iCopyOffset + iMoveOffset);
        int *src = (int*)((int)pEmptyList + iCopyOffset);
        int iCount = (pEmptyList[0] - iIndex) * 2 * sizeof(int);
        int iEmptySize = (iSize + sizeof(int) - 1) / sizeof(int) * sizeof(int);
        memmove_s(dest, iCount, src, iCount);
        pEmptyList[0]++;
        pEmptyList[iIndex * 2 + 1] = iPosition;
        pEmptyList[iIndex * 2 + 2] = iEmptySize;
        *(int*)&pStrBuf[8] = (int)pEmptyList;
        TryCombineEmptyList(iIndex);
    }
    else
    {
        return -1;
    }
    return 0;
}

int ModifyEmptyList(int iIndex, int iPosition, int iSize)
{
    pEmptyList[iIndex * 2 + 1] = iPosition;
    pEmptyList[iIndex * 2 + 2] = iSize;
    return 0;
}

int FindItem(char *szStr)
{
    int i = 0;
    for (i = 0; i < pFillList[0]; i++)
    {
        if (strcmp(szStr, &pStrBuf[pFillList[i * 2 + 1]]) == 0)
        {
            return i;
        }
    }
    return -1;
}

int InsertFillList(int iIndex, int iPosition, int iSize)
{
    int iMoveOffset = 2 * sizeof(int*);
    int iEmptyListTail = (int)pEmptyList + (2 * pEmptyList[0] + 1) * sizeof(int) + iMoveOffset;
    int iAryTail = (int)pSize + *pSize;
    if (iEmptyListTail <= iAryTail)
    {
        //int iIndex = FindInsertIndex(iPosition);
        int iCopyOffset = (iIndex * 2 + 1) * sizeof(int);
        int *dest = (int*)((int)pFillList + iCopyOffset + iMoveOffset);
        int *src = (int*)((int)pFillList + iCopyOffset);
        int iCount = ((pFillList[0] - iIndex) * 2 + 1 + pEmptyList[0] * 2 + 1) * sizeof(int);
        memmove_s(dest, iCount, src, iCount);
        pFillList[0]++;
        pFillList[iIndex * 2 + 1] = iPosition;
        pFillList[iIndex * 2 + 2] = iSize;
        pEmptyList += iMoveOffset / sizeof(int);
        *(int*)&pStrBuf[8] = (int)pEmptyList;
    }
    else
    {
        return -1;
    }
    return 0;
}

int DeleteFillList(int iIndex)
{
    int iMoveOffset = 2 * (int)sizeof(int*);
    int iCopyOffset = (iIndex * 2 + 1) * sizeof(int);
    int *dest = (int*)((int)pFillList + iCopyOffset);
    int *src = (int*)((int)pFillList + iCopyOffset + iMoveOffset);
    int iCount = ((pFillList[0] - iIndex) * 2 + 1 + pEmptyList[0] * 2 + 1) * sizeof(int);
    memmove_s(dest, iCount, src, iCount);
    pFillList[0]--;
    pEmptyList -= iMoveOffset / (int)sizeof(int);
    *(int*)&pStrBuf[8] = (int)pEmptyList;
    return 0;
}

int AdjustArrayTail(int iSize)
{
    int iMoveOffset = (iSize + sizeof(int) - 1) / sizeof(int) * sizeof(int);
    int iEmptyListTail = (int)pEmptyList + (2 * pEmptyList[0] + 1) * sizeof(int) + iMoveOffset;
    int iAryTail = (int)pSize + *pSize;
    if (iEmptyListTail <= iAryTail)
    {
        int *dest = (int*)((int)pFillList + iMoveOffset);
        int *src = pFillList;
        int iCount = (pFillList[0] * 2 + 1 + pEmptyList[0] * 2 + 1) * sizeof(int);
        memmove_s(dest, iCount, src, iCount);
        pFillList += iMoveOffset / sizeof(int);
        pEmptyList += iMoveOffset / sizeof(int);
        *(int*)&pStrBuf[4] = (int)pFillList;
        *(int*)&pStrBuf[8] = (int)pEmptyList;
    }
    else
    {
        return -1;
    }
    return 0;
}

int InsertEmptyPlace(int iEmptyPlaceIndex, char *szStr, int iSize, int iIndex)
{
    int iPosition = pEmptyList[iEmptyPlaceIndex * 2 + 1];
    int iUsedSize = (iSize + sizeof(int) - 1) / sizeof(int) * sizeof(int);
    int iRemainSize = pEmptyList[iEmptyPlaceIndex * 2 + 2] - iUsedSize;
    int iRemainPosition = iPosition + iUsedSize;
    int iRet = 0;
    memcpy_s(&pStrBuf[iPosition], iSize, szStr, iSize);
    ModifyEmptyList(iEmptyPlaceIndex, iRemainPosition, iRemainSize);
    iRet = InsertFillList(iIndex, iPosition, iSize);

    return iRet;
}

int AttachToTail(int iIndex, char *szStr, int iSize)
{
    int iPosition = 0;
    int iRet = 0;
    iPosition = (int)pFillList - (int)pSize;
    iRet = AdjustArrayTail(iSize);
    if (iRet != 0)
    {
        return iRet;
    }
    iRet = InsertFillList(iIndex, iPosition, iSize);
    if (iRet != 0)
    {
        return iRet;
    }
    memcpy_s(pStrBuf + iPosition, iSize, szStr, iSize);
    return 0;
}

int InsertItem0(char *szStr)
{
    return InsertItem(szStr, -1);
}

int InsertItem(char *szStr, int iIndex)
{
    int iEmptyPlaceIndex = 0;
    int iSize = strnlen(szStr, MAXSTRLEN) + 1;
    if (iIndex == -1)
    {
        iIndex = pFillList[0];
    }
    iEmptyPlaceIndex = FindEmptyPlace(iSize);
    if (iEmptyPlaceIndex == -1)
    {

        return AttachToTail(iIndex, szStr, iSize);
    }
    else
    {
        return InsertEmptyPlace(iEmptyPlaceIndex, szStr, iSize, iIndex);
    }

    return 0;
}

int DeleteItemFromIndex(int iItemIndex)
{
    int iRet = 0;
    if (iItemIndex < pFillList[0])
    {
        int iPosition = pFillList[2 * iItemIndex + 1];
        int iSize = pFillList[2 * iItemIndex + 2];
        iRet = InsertEmptyList(iPosition, iSize);
        if (iRet != 0)
        {
            return iRet;
        }
        return DeleteFillList(iItemIndex);
    }
    return -1;
}

int DeleteItemFromString(char *szStr)
{
    int iItemIndex = FindItem(szStr);
    if (iItemIndex == -1)
    {
        return -1;
    }
    return DeleteItemFromIndex(iItemIndex);
}

int ModifyItemFormIndex(int iIndex, char *szStr)
{
    DeleteItemFromIndex(iIndex);
    return InsertItem(szStr, iIndex);
}

int ModifyItemFromString(char *szDest, char *szSource)
{
    int iItemIndex = FindItem(szDest);
    if (iItemIndex == -1)
    {
        return -1;
    }
    return ModifyItemFormIndex(iItemIndex, szSource);
}


int SearchItemFromIndex(char * szStr, int iIndex)
{
    if (iIndex >= pFillList[0])
    {
        return -1;
    }
    char *str = &pStrBuf[pFillList[iIndex * 2 + 1]];
    int iSize = pFillList[iIndex * 2 + 2];
    memcpy_s(szStr, iSize, str, iSize);

    return 0;
}


int SearchItemFromSubstr(char *szStr[10], int iIndex[10], int *iCount, char * substr)
{
    int i = 0;
    *iCount = 0;
    for (i = 0; i < pFillList[0]; i++)
    {
        if (KMPSearch(&pStrBuf[pFillList[i * 2 + 1]], substr))
        {
            char *str = &pStrBuf[pFillList[i * 2 + 1]];
            int iSize = pFillList[i * 2 + 2];
            szStr[*iCount] = str;
            iIndex[*iCount] = i;
            (*iCount)++;
            if (*iCount == 10)
            {
                break;
            }
        }
    }
    if (*iCount > 0)
    {
        return i;   //下次查找需要用到的index
    }
    return -1;
}

int SearchNext(char *szStr[10], int iIndex[10], int *iCount, char * substr, int iStartIndex)
{
    int i = 0;
    *iCount = 0;
    for (i = iStartIndex; i < pFillList[0]; i++)
    {
        if (KMPSearch(&pStrBuf[pFillList[i * 2 + 1]], substr))
        {
            char *str = &pStrBuf[pFillList[i * 2 + 1]];
            int iSize = pFillList[i * 2 + 2];
            szStr[*iCount] = str;
            iIndex[*iCount] = i;
            (*iCount)++;
            if (*iCount == 10)
            {
                break;
            }
        }
    }
    if (*iCount > 0)
    {
        return i;   //下次查找需要用到的index
    }
    return -1;
}

int CountCharacters(int aryLittleChar[26], int aryBigChar[26], int *iCount)
{
    int i = 0;
    int j = 0;
    *iCount = 0;
    memset(aryLittleChar, 0, 26 * sizeof(int));
    memset(aryBigChar, 0, 26 * sizeof(int));
    for (i = 0; i < pFillList[0]; i++)
    {
        char *szTmp = &pStrBuf[pFillList[i * 2 + 1]];
        for (j = 0; j < strnlen(szTmp, MAXSTRLEN); j++)
        {
            if (szTmp[j] >= 'a' && szTmp[j] <= 'z')
            {
                aryLittleChar[szTmp[j] - 'a']++;
            }
            else if (szTmp[j] >= 'A' && szTmp[j] <= 'Z')
            {
                aryBigChar[szTmp[j] - 'a']++;
            }
            (*iCount)++;
        }
    }

    return 0;
}

int Defragment()
{
    int iPosition = 0;
    int iOffset = 0;
    if (pEmptyList[0] > 0)
    {
        int i = 0;
        for (i = 0; i < pEmptyList[0]; i++)
        {
            iOffset += pEmptyList[i * 2 + 2];
        }
        do
        {
            int i = 0;
            iPosition = pEmptyList[1] + pEmptyList[2];
            for (i = 0; i < pFillList[0]; i++)
            {
                if (iPosition == pFillList[i * 2 + 1])
                {
                    DeleteItemFromIndex(i);
                    InsertItem(&pStrBuf[iPosition], i);
                    break;
                }
            }
            if (i == pFillList[0])
                break;
        } while (1);
        AdjustArrayTail(-iOffset);
    }
    return 0;
}

