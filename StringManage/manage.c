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
Item **UsedItems;
Item **UnusedItems;
Item *sortedUsedItemList;
Item *sortedUnusedItemList;
int iUsedNum;
int iUnusedNum;
int iMaxUsedNum;
int iMaxUnusedNum;

int InitItem(Item *item, int iStrIndex, int size)
{
    item->iStrIndex = iStrIndex;
    item->iSize = size;
    item->next = NULL;
    item->pre = NULL;

    return 0;
}

int Initialize()
{
    szBuf = (char*)malloc(0x10 * sizeof(char));
    iTotalSpace = 0x10;
    iUsedSpace = 0;
    iMaxUnusedNum = 0;
    iMaxUsedNum = 0x10;
    UnusedItems = (Item**)malloc(0x10 * sizeof(Item*));
    UnusedItems[0] = (Item*)malloc(sizeof(Item));
    InitItem(UnusedItems[0], 0, 10);
    UnusedItems[0]->iStrIndex = 0;
    UnusedItems[0]->iSize = 10;
    UnusedItems[0]->next = NULL;
    UnusedItems[0]->pre = NULL;
    sortedUnusedItemList = UnusedItems[0];
    sortedUsedItemList = NULL;
    UsedItems = NULL;
    iUsedNum = 0;
    iUnusedNum = 1;

    return 0;
}

//返回足够空间的空条目下标，-1表示找不到, -2表示空间不足
int SearchEnoughSpace(int iSize)
{
    int i = 0;

    if (iSize < (iTotalSpace - iUsedSpace))
    {
        return -2;
    }

    for (i = 0; i < iUnusedNum; i++)
    {
        if (UnusedItems[i]->iSize >= iSize)
            return i;
    }

    return -1;
}

int ExpandSpace(int size)
{
    // TODO
    size = (size / iTotalSpace + 1) * iTotalSpace;
    Item *lastUnusedItem = NULL;
    if (iUnusedNum > 0)
    {
        lastUnusedItem = UnusedItems[iUnusedNum - 1];
        if(lastUnusedItem->iStrIndex+lastUnusedItem->iSize == iTotalSpace)
        {
            lastUnusedItem->iSize += size;
        }
        else
        {

        }
    }
    else
    {
        lastUnusedItem = (Item*)malloc(sizeof(Item));

    }

    return 0;
}

Item *SearchNextUesdItem(Item *item)
{
    return NULL;
}

Item *SearchPreUsedItem(Item *item)
{
    return NULL;
}

Item *SearchNextEmptyItem(Item *item)
{
    return NULL;
}

Item *SearchPreEmptyItem(Item *item)
{
    return NULL;
}

int DecUnusedItem(int index)
{
    iUnusedNum--;
    return 0;
}

int IncUnusedItem(Item *item)
{
    iUnusedNum++;
    return 0;
}

int ModifyUnusedItem(Item *item, int index)
{

    return 0;
}

int DecUsedItem(int index)
{
    iUsedNum--;
    return 0;
}

int IncUsedItem(Item *item)
{
    iUsedNum++;
    return 0;
}

int ModifyUsedItem(Item *item, int index)
{

    return 0;
}

//不检查越界
int FillEmptyItem(char *szStr, int size, int itemIndex)
{
    Item *thisFillItem = UnusedItems[itemIndex];
    int savedSize = thisFillItem->iSize;
    thisFillItem->iSize = size;
    memcpy(&szBuf[thisFillItem->iStrIndex], szStr, size);
    iUsedSpace += size;
    if (size == thisFillItem->iSize)
    {
        thisFillItem->pre = thisFillItem->next;
        if (thisFillItem->next != NULL)
        {
            thisFillItem->next->pre = thisFillItem->pre;
        }
        DecUnusedItem(itemIndex);
        IncUnusedItem(thisFillItem);
    }
    else
    {
        Item *nextFillItem = SearchNextUesdItem(thisFillItem);
        Item *preFillItem = SearchPreUsedItem(thisFillItem);
        Item *thisEmptyItem = (Item*)malloc(sizeof(Item));
        thisEmptyItem->iSize = savedSize - size;
        thisEmptyItem->iStrIndex = thisFillItem->iSize + size;

        //修改前后未用节点
        thisEmptyItem->next = thisFillItem->next;
        if (thisFillItem->next != NULL)
        {
            thisFillItem->next->pre = thisEmptyItem;
        }

        thisEmptyItem->pre = thisFillItem->pre;
        if (thisFillItem->pre != NULL)
        {
            thisFillItem->pre->next = thisEmptyItem;
        }
        else
        {
            sortedUnusedItemList = thisEmptyItem;
        }

        //修改前后已使用节点
        thisFillItem->next = nextFillItem;
        if (nextFillItem != NULL)
        {
            nextFillItem->pre = thisFillItem->pre;
        }

        thisFillItem->pre = preFillItem;
        if (preFillItem != NULL)
        {
            preFillItem->next = thisFillItem;
        }
        else
        {
            sortedUsedItemList = thisFillItem;
        }

        ModifyUnusedItem(thisEmptyItem, itemIndex);
        IncUsedItem(thisFillItem);
    }

    return 0;
}

int InsertItem(char * szStr)
{
    //FillEmptyItem(szStr, strlen(szStr) + 1, 0);
    return 0;
}
