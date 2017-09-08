#pragma once

int Initialize(char *szBuf, int size);

int InsertItem0(char *szStr);

int InsertItem(char *szStr, int iIndex);

int DeleteItemFromIndex(int iItemIndex);

int DeleteItemFromString(char *szStr);

int ModifyItemFormIndex(int iIndex, char *szStr);

int ModifyItemFromString(char *szDest, char *szSource);

int SearchItemFromIndex(char *szStr, int iIndex);

int SearchItemFromSubstr(char *szStr[10], int iIndex[10], int *iCount, char * substr);

int SearchNext(char *szStr[10], int iIndex[10], int *iCount, char * substr, int iStartIndex);

int CountCharacters(int aryLittleChar[26], int aryBigChar[26], int *iCount);

int Defragment();
