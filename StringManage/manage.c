#include "manage.h"

#include <stdlib.h>
#include <string.h>

//  ((int*)szBuf)[0] = iSize;    �����ֽ���

//  fill��ǰ��empty�ں�
//  ((int*)szBuf)[1]    ->      fill���飨λ�ã���С��   pFillList
//  λ�ô�С������ = pFillList[0]
//  λ�� = pFillList[iIndex * 2 + 1]
//  ��С = pFillList[iIndex * 2 + 2]
//  ((int*)szBuf)[2]    ->      empty���飨λֵ����С��  pEmptyList
//  λ�ô�С������ = pEmptyList[0]
//  λ�� = pEmptyList[iIndex * 2 + 1]
//  ��С = pEmptyList[iIndex * 2 + 2]
int *pSize;
int *pFillList;
int *pEmptyList;

int Initialize(char *szBuf, int size)
{
    pSize = (int*)szBuf;
    *pSize = size;
    *(int*)&szBuf[4] = (int)&szBuf[12];
    *(int*)&szBuf[8] = (int)&szBuf[16];
    pFillList = (int*)*(int*)&szBuf[4];
    pEmptyList = (int*)*(int*)&szBuf[8];
    pFillList[0] = 0;
    pEmptyList[0] = 0;
    return 0;
}

int HasEmptyPlace(int iSize)
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

int InsertEmptyList(int iIndex, int iPosition, int iSize)
{
    
}

int FindInsertIndex(int iPosition)
{
    int i = 0;
    for (i = 0; i < pFillList[0]; i++)
    {
        if (iPosition < pFillList[i * 2 + 1])
        {
            return i;
        }
    }
    return i;
}

int InsertFillList(int iPosition, int iSize)
{
    int iMoveOffset = 2 * sizeof(int*);
    int iEmptyListTail = (int)pEmptyList + (2 * pEmptyList[0] + 1) * sizeof(int) + iMoveOffset;
    int iAryTail = (int)pSize + *pSize;
    if (iEmptyListTail <= iAryTail)
    {
        int iIndex = FindInsertIndex(iPosition);
        int iCopyOffset = (iIndex * 2 + 1) * sizeof(int);
        int *dest = (int*)((int)pFillList + iCopyOffset + iMoveOffset);
        int *src = (int*)((int)pFillList + iCopyOffset);
        int iCount = ((pFillList[0] - iIndex) * 2 + 1 + pEmptyList[0] * 2 + 1) * sizeof(int);
        memmove_s(dest, iCount, src, iCount);
    }
    else
    {
        return -1;
    }
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
    }
    else
    {
        return -1;
    }
    return 0;
}

int InsertEmptyPlace(int iIndex, char *szStr, int iSize)
{

}

int AttachToTail(char *szStr, int iSize)
{
    int iPosition = 0; 
    AdjustArrayTail(iSize);
    InsertFillList(iPosition, iSize);
    return 0;
}

int InsertItem(char *szStr)
{
    int iEmptyPlaceIndex = 0;
    int iSize = strnlen(szStr, 256) + 1;
    iEmptyPlaceIndex = HasEmptyPlace(iSize);
    if (iEmptyPlaceIndex == -1)
    {
        
        AttachToTail(szStr, iSize);
    }
    else
    {
        InsertEmptyPlace(iEmptyPlaceIndex, szStr, iSize);
    }

}