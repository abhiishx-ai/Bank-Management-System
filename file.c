#include <stdio.h>
#include "account.h"

void save() {
    FILE* fp = fopen("bank.dat", "wb");
    Account* t = head;

    while (t) {
        fwrite(&t->accNo, sizeof(long long), 1, fp);
        fwrite(t->name, sizeof(char), 50, fp);
        fwrite(&t->pin, sizeof(int), 1, fp);
        fwrite(&t->balance, sizeof(float), 1, fp);
        t = t->next;
    }

    fclose(fp);
}

void load() {
    FILE* fp = fopen("bank.dat", "rb");
    if (!fp) return;

    long long acc;
    char name[50];
    int pin;
    float bal;

    while (
        fread(&acc, sizeof(long long), 1, fp) &&
        fread(name, sizeof(char), 50, fp) &&
        fread(&pin, sizeof(int), 1, fp) &&
        fread(&bal, sizeof(float), 1, fp)
    ) {
        Account* n = createNode(acc, name, pin, bal);
        n->next = head;
        head = n;
    }

    fclose(fp);
}