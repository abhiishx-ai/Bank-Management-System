#ifndef UTILS_H
#define UTILS_H

#include "account.h"

Account** toArray(int* n);
void sortByAccNo(Account** arr, int n);
Account* binarySearch(Account** arr, int n, long long key);
void sortByBalance(Account** arr, int n);

#endif