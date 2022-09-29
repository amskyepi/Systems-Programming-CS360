#include <stdio.h>

int lineNum(char *dictionaryName, char *word, int length);

int main() {
    printf("\nDictionary: webster_16\n\n");
    printf("Word: acid\t\t Expected: 167\t\t Found: %d\n", lineNum("webster_16", "acid", 16));
    printf("Word: mellow\t\t Expected: 11609\t Found: %d\n", lineNum("webster_16", "mellow", 16));
    printf("Word: youth\t\t Expected: 20413\t Found: %d\n", lineNum("webster_16", "youth", 16));
    printf("Word: acknowledgeable\t Expected: 173\t\t Found: %d\n", lineNum("webster_16", "acknowledgeable", 16));
    printf("Word: acknowledgeables\t Expected: 173\t\t Found: %d\n", lineNum("webster_16", "acknowledgeables", 16));
    printf("Word: zoo\t\t Expected: 20422\t Found: %d\n", lineNum("webster_16", "zoo", 16));
    printf("Word: abc\t\t Expected: 16\t\t Found: %d\n", lineNum("webster_16", "abc", 16));
    printf("Word: fi sh\t\t Expected: -7048\t Found: %d\n", lineNum("webster_16", "fi sh", 16));
    printf("Word: 000\t\t Expected: -1\t\t Found: %d\n", lineNum("webster_16", "000", 16));
    printf("Word: a b c\t\t Expected: 1\t\t Found: %d\n", lineNum("webster_16", "a b c ", 16));

    printf("\nDictionary: tiny_9\n\n");
    printf("Word: acid\t\t Expected: -1\t\t Found: %d\n", lineNum("tiny_9", "acid", 9));
    printf("Word: mellow\t\t Expected: 10\t\t Found: %d\n", lineNum("tiny_9", "mellow", 9));
    printf("Word: youth\t\t Expected: -10\t\t Found: %d\n", lineNum("tiny_9", "youth", 9));
    printf("Word: acknowledgeables\t Expected: -1\t\t Found: %d\n", lineNum("tiny_9", "acknowledgeables", 9));
    printf("Word: zoo\t\t Expected: -10\t\t Found: %d\n", lineNum("tiny_9", "zoo", 9));
    printf("Word: abc\t\t Expected: -1\t\t Found: %d\n", lineNum("tiny_9", "abc", 9));
    printf("Word: fi sh\t\t Expected: 7\t\t Found: %d\n", lineNum("tiny_9", "fi sh", 9));
    printf("Word: 000\t\t Expected: -1\t\t Found: %d\n", lineNum("tiny_9", "000", 9));
    printf("Word: a b c\t\t Expected: -1\t\t Found: %d\n", lineNum("tiny_9", "a b c", 9));
    return 0;
}
