#include <stdio.h>
#include "ui.h"

#define RESET "\033[0m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define RED "\033[31m"

void uiHeader(char title[]) {
    printf(CYAN "\n============================\n%s\n============================\n" RESET, title);
}

void uiSuccess(char msg[]) {
    printf(GREEN "%s\n" RESET, msg);
}

void uiError(char msg[]) {
    printf(RED "%s\n" RESET, msg);
}