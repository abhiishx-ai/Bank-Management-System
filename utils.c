#include <stdlib.h>
#include "utils.h"

Account** toArray(int* n) {
    *n = 0;
    Account* t = head;

    while (t) { (*n)++; t = t->next; }

    Account** arr = malloc((*n) * sizeof(Account*));

    t = head;
    for (int i = 0; i < *n; i++) {
        arr[i] = t;
        t = t->next;
    }

    return arr;
}

void sortByAccNo(Account** arr, int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j]->accNo > arr[j+1]->accNo) {
                Account* t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
            }
}

Account* binarySearch(Account** arr, int n, long long key) {
    int l = 0, r = n-1;

    while (l <= r) {
        int mid = (l + r) / 2;
        if (arr[mid]->accNo == key) return arr[mid];
        else if (arr[mid]->accNo < key) l = mid + 1;
        else r = mid - 1;
    }
    return NULL;
}

void sortByBalance(Account** arr, int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j]->balance < arr[j+1]->balance) {
                Account* t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
            }
}