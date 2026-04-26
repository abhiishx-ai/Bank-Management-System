#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "ui.h"
#include "utils.h"

Account* head = NULL;

Account* createNode(long long acc, char name[], int pin, float bal) {
    Account* n = (Account*)malloc(sizeof(Account));
    n->accNo = acc;
    strcpy(n->name, name);
    n->pin = pin;
    n->balance = bal;
    n->history = NULL;
    n->next = NULL;
    return n;
}

Account* find(long long accNo) {
    Account* t = head;
    while (t) {
        if (t->accNo == accNo) return t;
        t = t->next;
    }
    return NULL;
}

int authenticate(Account* a) {
    int p;
    printf("Enter PIN: ");
    scanf("%d", &p);
    return (p == a->pin);
}

void addTransaction(Account* a, char type[], float amt) {
    Transaction* t = malloc(sizeof(Transaction));
    strcpy(t->type, type);
    t->amount = amt;
    t->next = a->history;
    a->history = t;
}

void addAccount() {
    long long acc;
    int pin;
    float bal;
    char name[50];

    uiHeader("Create Account");

    printf("Acc No: ");
    scanf("%lld", &acc);

    if (find(acc)) {
        uiError("Duplicate Account");
        return;
    }

    getchar();
    printf("Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("PIN: ");
    scanf("%d", &pin);

    printf("Balance: ");
    scanf("%f", &bal);

    Account* n = createNode(acc, name, pin, bal);
    n->next = head;
    head = n;

    uiSuccess("Account Created");
}

void display() {
    uiHeader("All Accounts");

    if (!head) {
        uiError("No Data Found");
        return;
    }

    printf("%-15s %-20s %-10s\n", "AccNo", "Name", "Balance");
    printf("-----------------------------------------------------\n");

    Account* t = head;
    while (t) {
        printf("%-15lld %-20s %-10.2f\n",
               t->accNo, t->name, t->balance);
        t = t->next;
    }
}

void deposit() {
    long long acc;
    float amt;

    printf("Acc No: ");
    scanf("%lld", &acc);

    Account* a = find(acc);
    if (!a || !authenticate(a)) {
        uiError("Invalid");
        return;
    }

    printf("Amount: ");
    scanf("%f", &amt);

    a->balance += amt;
    addTransaction(a, "DEP", amt);
    uiSuccess("Deposited");
}

void withdraw() {
    long long acc;
    float amt;

    printf("Acc No: ");
    scanf("%lld", &acc);

    Account* a = find(acc);
    if (!a || !authenticate(a)) {
        uiError("Invalid");
        return;
    }

    printf("Amount: ");
    scanf("%f", &amt);

    if (amt > a->balance) {
        uiError("Insufficient Balance");
        return;
    }

    a->balance -= amt;
    addTransaction(a, "WDR", amt);
    uiSuccess("Withdrawn");
}

void deleteAcc() {
    long long acc;
    printf("Acc No: ");
    scanf("%lld", &acc);

    Account *t = head, *prev = NULL;

    while (t && t->accNo != acc) {
        prev = t;
        t = t->next;
    }

    if (!t) {
        uiError("Not Found");
        return;
    }

    if (prev) prev->next = t->next;
    else head = t->next;

    free(t);
    uiSuccess("Deleted");
}

void analytics() {
    uiHeader("Analytics");

    float total = 0, max = 0;
    char name[50] = "";

    Account* t = head;

    while (t) {
        total += t->balance;
        if (t->balance > max) {
            max = t->balance;
            strcpy(name, t->name);
        }
        t = t->next;
    }

    printf("Total Balance: %.2f\n", total);
    printf("Top Account: %s (%.2f)\n", name, max);
}

void showHistory() {
    long long acc;
    printf("Acc No: ");
    scanf("%lld", &acc);

    Account* a = find(acc);
    if (!a) {
        uiError("Not Found");
        return;
    }

    Transaction* t = a->history;
    while (t) {
        printf("%s : %.2f\n", t->type, t->amount);
        t = t->next;
    }
}

void fastSearch() {
    long long key;
    printf("Enter Acc No: ");
    scanf("%lld", &key);

    int n;
    Account** arr = toArray(&n);
    sortByAccNo(arr, n);

    Account* res = binarySearch(arr, n, key);

    if (res)
        printf("Found: %s | %.2f\n", res->name, res->balance);
    else
        printf("Not Found\n");

    free(arr);
}

void leaderboard() {
    int n;
    Account** arr = toArray(&n);

    sortByBalance(arr, n);

    printf("\nTop Accounts:\n");
    for (int i = 0; i < n && i < 5; i++) {
        printf("%d. %s - %.2f\n", i+1, arr[i]->name, arr[i]->balance);
    }

    free(arr);
}

int adminAuth() {
    int pin;
    printf("Admin PIN: ");
    scanf("%d", &pin);
    return pin == 9999;
}

void adminPanel() {
    if (!adminAuth()) {
        printf("Access Denied\n");
        return;
    }

    int ch;
    printf("\n1.View All\n2.Leaderboard\n");
    scanf("%d", &ch);

    if (ch == 1) display();
    else if (ch == 2) leaderboard();
}