#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define n 10

void rotate_cc(int p[n], int count)
{
    count %= n;

    int i = 0, j = 0;
    int temp = p[0], next;

    for (int k = 0; k < n; k++)
    {
        j = (i + count) % n;

        if (j == 0 || (j < i && k < n - 1))
        {
            p[i] = temp;
            i = j + 1;
            temp = p[i];
        }
        else
        {
            next = p[j];
            p[j] = temp;
            temp = next;
            i = j;
        }
    }
}
int main()
{
    int a[n], step;

    for (int i = 0; i < n; i++)
        a[i] = 3 * i + 3;

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");

    while (1)
    {
        printf("Enter steps (0 to stop): ");
        scanf("%d", &step);

        if (step == 0)
            break;

        rotate_cc(a, step);

        for (int i = 0; i < n; i++)
            printf("%d ", a[i]);

        printf("\n");
    }

    return 0;
}