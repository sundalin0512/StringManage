#include "manage.h"

#include <stdlib.h>
#include <string.h>

typedef struct typeItem
{
    int iStrIndex;
    int iSize;
    //int isUsed;
    //int iLocation;
    struct typeItem *next;
    struct typeItem *pre;
}Item;

char *szBuf;
int iTotalSpace;
int iUsedSpace;
Item *UsedItems;
Item *UnusedItems;
int iUsedNum;
int iUnusedNum;

int Initialize()
{
    szBuf = (char*)malloc(10 * sizeof(char));
    iTotalSpace = 10;
    iUsedSpace = 0;
    UnusedItems = (Item*)malloc(sizeof(Item));
    UnusedItems[0].iStrIndex = 0;
    UnusedItems[0].iSize = 10;
    //UnusedItems[0].isUsed = 0;
    //UnusedItems[0].iLocation = 0;
    UnusedItems[0].next = NULL;
    UnusedItems[0].pre = NULL;
    UsedItems = NULL;
    iUsedNum = 0;
    iUnusedNum = 1;

    return 0;
}

//�����㹻�ռ�Ŀ���Ŀ�±꣬-1��ʾ�Ҳ���, -2��ʾ�ռ䲻��
int SearchEnoughSpace(int iSize)
{
    int i = 0;
    if (iSize < (iTotalSpace - iUsedSpace))
    {
        return -2;
    }
    for (i = 0; i < iUnusedNum; i++)
    {
        if (UnusedItems[i].iSize >= iSize)
            return i;
    }
    if (i == iUnusedNum)
    {
        return -1;
    }
}

Item *SearchNextUesdItem(Item *item)
{

}

Item *SearchPreUsedItem(Item *item)
{

}

Item *SearchNextEmptyItem(Item *item)
{

}

Item *SearchPreEmptyItem(Item *item)
{

}

int DecUnusedItem(int index)
{
    iUnusedNum--;
}

int IncUnusedItem(Item *item)
{
    iUnusedNum++;
}

int ModifyUnusedItem(Item *item, int index)
{

}

int DecUsedItem(int index)
{
    iUsedNum--;
}

int IncUsedItem(Item *item)
{
    iUsedNum++;
}

int ModifyUsedItem(Item *item, int index)
{

}

int FillEmptyItem(char *szStr, int size, int itemIndex)
{
    Item *thisFillItem = &UnusedItems[itemIndex];
    int savedSize = thisFillItem->iSize;
    thisFillItem->iSize = size;
    memcpy(&szBuf[thisFillItem->iStrIndex], szStr, size);
    iUsedSpace += size;
    if (size == thisFillItem->iSize)
    {
        thisFillItem->pre = thisFillItem->next;
        thisFillItem->next->pre = thisFillItem->pre;
        DecUnusedItem(itemIndex);
        IncUnusedItem(thisFillItem);
    }
    else
    {
        Item *nextFillItem = SearchNextUesdItem(thisFillItem);
        Item *preFillItem = SearchPreUsedItem(thisFillItem);
        Item *thisEmptyItem = (Item*)malloc(sizeof(Item));
        thisEmptyItem->iSize = savedSize - size;
        thisEmptyItem->iStrIndex = thisFillItem + size;

        //�޸�ǰ��δ�ýڵ�
        if (thisFillItem->next != NULL)
        {
            thisEmptyItem->next = thisFillItem->next;
            thisFillItem->next->pre = thisEmptyItem;
        }
        if (thisFillItem->pre != NULL)
        {
            thisFillItem->pre->next = thisEmptyItem;
            thisEmptyItem->pre = thisFillItem->pre;
        }

        //�޸�ǰ����ʹ�ýڵ�
        if (nextFillItem != NULL)
        {
            thisFillItem->next = nextFillItem;
            nextFillItem->pre = thisFillItem->pre;
        }
        if (preFillItem != NULL)
        {
            thisFillItem->pre = preFillItem;
            preFillItem->next = thisFillItem;
        }
        ModifyUnusedItem(thisEmptyItem, itemIndex);
        IncUsedItem(thisFillItem);
    }

    return 0;
}

int InsertItem(char * szStr)
{

    return 0;
}
