#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int r;
int end_num;

void start();
void end();
int ran();

void main()
{
    start();
    printf("%d", r);
}

void start()
{
    ran();
}

int ran()
{
    srand(time(NULL));
    r = rand() % 13; // 1~13������ ������ r�� �Է�

    return r;
}

void end()
{
    switch(end_num)
    {
        case 1:
            printf("�¸�");
            break;
        case 2:
            printf("����Ʈ!");
            break;
        case 3:
            printf("�й�");
            break;
    }
}