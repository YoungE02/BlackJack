#include <stdio.h>
#include <windows.h>
#include <ctype.h>


int main()
{
    int i = 0;
    system("cls");
    scanf("%d", &i);

    while(isdigit(i) != 0)
    {
        printf("reTry");

        scanf("%d", &i);
    }
    printf("\n\n%s", i);
}