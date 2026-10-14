#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define n 10

void rotate_cc(int p[n], int count)
{
    for(int k = 0, i = -1, l=-1; k < n; k++){
        if (i=l)i=(++l + count) % n;
        int j = (i + count) % n;
        int temp = p[i];
        p[i]=p[j];
        p[j]=temp;
        i=j;
        
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
