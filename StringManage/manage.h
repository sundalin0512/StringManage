#pragma once

int Initialize(char *szBuf, int size);

int InsertItem0(char *szStr);

int InsertItem(char *szStr, int iIndex);

int DeleteItemFromIndex(int iItemIndex);

int DeleteItemFromString(char *szStr);

int ModifyItemFormIndex(int iIndex, char *szStr);

int ModifyItemFromString(char *szDest, char *szSource);

int SearchItemFromIndex(char *szStr, int iIndex);

int SearchItemFromSubstr(char *szStr, int *iIndex, int *iCount,char *substr);

int CountCharacters(int aryLittleChar[26], int aryBigChar[26], int *iCount);


