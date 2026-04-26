#include <stdio.h>
#include "account.h"

void save();
void load();

int main() {
    int ch;

    load();

    while (1) {
        printf("\n1.Add 2.Display 3.Deposit 4.Withdraw\n");
        printf("5.Delete 6.Analytics 7.History\n");
        printf("8.Save 9.Search 10.Admin 11.Exit\n");

        scanf("%d", &ch);

        switch (ch) {
            case 1: addAccount(); break;
            case 2: display(); break;
            case 3: deposit(); break;
            case 4: withdraw(); break;
            case 5: deleteAcc(); break;
            case 6: analytics(); break;
            case 7: showHistory(); break;
            case 8: save(); break;
            case 9: fastSearch(); break;
            case 10: adminPanel(); break;
            case 11: return 0;
        }
    }
}