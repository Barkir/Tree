#include <string.h>
#include <stdio.h>

#include "compare.h"
#include "tree.h"

int CompareNum(int num1, int num2)
{
    if (num1 == num2) return 0;
    if (num1 > num2) return 1;
    if (num1 < num2) return -1;
    return 0;
}

int CompareString(const char * field)
{
    char answer[100] = "";
    printf("%s\n", field);
    scanf("%99s", answer);
    if (strcmp(answer, "yes") == 0) return TREE_YES;
    if (strcmp(answer, "no") == 0)  return TREE_NO;
    if (!strlen(answer)) return TREE_END;
    return printf("[answer yes/no]\n");
}
