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
            memmove_s(dest, iCount, src, iCount);
            pEmptyList[0]--;
            pEmptyList[iIndex * 2 + 2] += pEmptyList[iIndex * 2 + 4];
        }
    }
    else if (iIndex != 0)
    {
        if (pEmptyList[iIndex * 2 -1] + pEmptyList[iIndex * 2] == pEmptyList[iIndex * 2 + 1])
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
    memcpy_s(&pStrBuf[iPosition], iSize, szStr, iSize);
    ModifyEmptyList(iEmptyPlaceIndex, iRemainPosition, iRemainSize);
    InsertFillList(iIndex, iPosition, iSize);

    return 0;
}

int AttachToTail(int iIndex, char *szStr, int iSize)
{
    int iPosition = 0;
    iPosition = (int)pFillList - (int)pSize;
    AdjustArrayTail(iSize);
    InsertFillList(iIndex, iPosition, iSize);
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
    int iSize = strnlen(szStr, 256) + 1;
    if (iIndex == -1)
    {
        iIndex = pFillList[0];
    }
    iEmptyPlaceIndex = FindEmptyPlace(iSize);
    if (iEmptyPlaceIndex == -1)
    {

        AttachToTail(iIndex, szStr, iSize);
    }
    else
    {
        InsertEmptyPlace(iEmptyPlaceIndex, szStr, iSize, iIndex);
    }

}

int DeleteItemFromIndex(int iItemIndex)
{
    if (iItemIndex < pFillList[0])
    {
        int iPosition = pFillList[2 * iItemIndex + 1];
        int iSize = pFillList[2 * iItemIndex + 2];
        InsertEmptyList(iPosition, iSize);
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