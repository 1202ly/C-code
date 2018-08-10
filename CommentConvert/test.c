#define _CRT_SECURE_NO_WARNINGS 1
#include"commentconvert.h"

void test()
{
    FILE *pfIn = NULL;
    FILE *pfOut = NULL;
    pfIn = fopen("test.c1.txt", "r");
    if (pfIn == NULL)
    {
        perror("open file for read.");
        exit(EXIT_FAILURE);
    }
    pfOut = fopen("test.c2.txt", "w");
    if (pfOut == NULL)
    {
        perror("open file for write.");
        fclose(pfIn);
        exit(EXIT_FAILURE);
    }
    DoComment(pfIn, pfOut);
    fclose(pfIn);
    fclose(pfOut);
}

int main()
{
    test();
    system("pause");
    return 0;
}
