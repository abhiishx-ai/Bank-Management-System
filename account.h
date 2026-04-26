#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef struct Transaction {
    char type[10];
    float amount;
    struct Transaction* next;
} Transaction;

typedef struct Account {
    long long accNo;
    char name[50];
    int pin;
    float balance;
    Transaction* history;
    struct Account* next;
} Account;

extern Account* head;

// core
Account* createNode(long long acc, char name[], int pin, float bal);
Account* find(long long accNo);

// features
void addAccount();
void display();
void deposit();
void withdraw();
void deleteAcc();
void analytics();
void showHistory();

// advanced
void fastSearch();
void leaderboard();
void adminPanel();

// helpers
int authenticate(Account* a);
void addTransaction(Account* a, char type[], float amt);

#endif