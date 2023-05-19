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
    r = rand() % 13; // 1~13까지의 랜덤수 r에 입력

    return r;
}

void end()
{
    switch(end_num)
    {
        case 1:
            printf("승리");
            break;
        case 2:
            printf("버스트!");
            break;
        case 3:
            printf("패배");
            break;
    }
}