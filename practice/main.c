#include <stdio.h>

int main()
{
    int a = 7;
    // scanf("%d", &a);
    printf("%d - младший бит\n", a & 1);
    printf("%d - старший бит\n", a & (1 << 31));
    if ((a & (1 << 31)) == 0)
    {
        printf("0");
    }
    else
    {
        printf("1");
    }
    printf(" - старший бит\n");
    for (int number = 0; number < 32; number = number + 1)
    {
        if ((a & (1 << number)) == 0)
        {
            printf("0");
        }
        else
        {
            printf("1");
        }
    }
    return 0;
}