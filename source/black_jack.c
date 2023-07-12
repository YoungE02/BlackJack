#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

void save(char* filename);
void load(char* filename);

void init(int* Card);
int game_start(int* Dealer_Card, int* Player_Card);
void game_end(int game_set);
void set_card(int* Dealer_Card, int* Player_Card, int* Card);
int print_card(int* Card, int* i, int* A_p);

int Score = 300;
int batting_gold = 0;
char name[20];

int main()
{
    system("cls");
    int Card[52];
    int Dealer_Card[10], Player_Card[10];
    int game_set = 0;
    char i;

    char filename[20];
    char txt[5];


    // Player name/number check
    printf("#띄어쓰기 없이 입력#\n");
    printf("학번 이름 입력 (ex:30111안홍헌) :: ");
    scanf("%s", filename);
    strcpy(name, filename);

    strcpy(txt, ".txt");
    strcat(filename, txt);

    load(filename);

    

    while(1)
    {
        if (Score <= 0)
        {
            printf("남은 금액이 없어 진행 할 수 없습니다.");
            exit(1);
        }
        // 베팅

        batting_gold = 0;
        while (batting_gold < 1 || batting_gold > Score)
        {
            printf("베팅 금액 (1 ~ %d) :: ", Score);
            scanf("%d", &batting_gold);
        }


        printf("사용자 %s\n", name);
        printf("현재 금액  %d\n\n", Score);

        init(Card);
        set_card(Dealer_Card, Player_Card, Card);
        game_set = game_start(Dealer_Card, Player_Card);
        Sleep(1000);
        game_end(game_set);
        save(filename);

        printf("\n\nOne More 1 / Game Exit 2 :: ");
        scanf("%s", &i);
        while(i != '1')
        {
            if (i == '2')
            {
                printf("Thanks.\n");
                save(filename);
                exit(0);
            }
            else if (i != '1')
            {
                printf("reTry.\n");
                printf("\n\nOne More 1 / Game Exit 2 :: ");
                scanf("%s", &i);
            }
        }

        if (Score <= 0)
        {
            printf("남은 금액이 없어 진행 할 수 없습니다.");
            exit(1);
        }
        
        system("cls");
    }
}

void save(char* filename)
{
    FILE* file;
    file = fopen(filename, "w");

    if(file == NULL)
    {
        printf("file write fail\n");
        Sleep(1000);
        exit(1);
    }

    fprintf(file, "%d %s\n", Score, name);
    fclose(file);
}

void load(char* filename)
{
    int flag = 0;
    FILE* file;

    file = fopen(filename, "r");
    if(file == NULL)
    {
        printf("저장되어있는 정보 없음\n");
        Sleep(1000);
        printf("새로 시작 (1) | 종료 (2) :: ");
        scanf("%d", &flag);

        if(flag == 1)
        {
            file = fopen(filename, "w");
            fprintf(file, "%d %s\n", Score, name);
        }
        else exit(1);
    }

    fscanf(file, "%d %s\n", &Score, name);
    fclose(file);
    system("cls");
}

void init(int* Card)
{
    int w = 0, r = 0;
    int swit[52];

    for(int i = 0; i < 52; i++)
    {
        swit[i] = 0;
    }

    srand(time(NULL));
    while(w < 52)
    {
        r = rand() % 52;
        if (swit[r] == 0)
        {
            swit[r] = 1;
            Card[w] = r + 1;
            w++;
        }
    }
}

void set_card(int* Dealer_Card, int* Player_Card, int* Card)
{
    for(int i = 0; i < 10; i++)
    {
        Dealer_Card[i] = Card[i];
        Player_Card[i] = Card[i + 10];
    }
}

int game_start(int* Dealer_Card, int* Player_Card)
{
    int i = 0, d = 0;
    int A_p = 0, A_d = 0, gg = 0; // A있으면 1 없으면 0
    char HS;
    int Cnt = 2, D_sum = 0, P_sum = 0;
    int game_set = -1;

    printf("\n\tBlack Jack!\n\n");

    // Player Trun

    printf("\n\nPlayer Card Open!\n\n");
    P_sum += print_card(Player_Card, &i, &A_p);
    P_sum += print_card(Player_Card, &i, &A_p);
    
    if(A_p == 0 || P_sum <= 21) printf("\n\nPlayer Card Sum : %d", P_sum);
    else if(P_sum > 21) printf("\n\nPlayer Card Sum : %d", P_sum - 10);


    if(P_sum == 21)
    {
        printf("\n\n///////////////////////\n/Player Black Jack!!!!/\n///////////////////////");
        game_set = 3;
        return game_set;
    }

    while(game_set != 1) // 21되면 선택없이 딜러턴
    {
        printf("\n\nHit(1) | Stay(2) :: ");
        scanf("%s", &HS);
        printf("\n");

        if(HS == '1') // hit
        {
            for(int j=0; j < Cnt; ) print_card(Player_Card, &j, &gg);

            P_sum += print_card(Player_Card, &i, &A_p);
            Cnt++;

            if(A_p > 0 && P_sum > 21)
            {
                P_sum -= 10;
                A_p -= 1;
            }
            if(P_sum == 21) game_set = 1;
            if(P_sum > 21)
            {
                printf("\n\nPlayer Card Sum : %d", P_sum);
                game_set = -2;
                return game_set;
            }
            printf("\n\nPlayer Card Sum : %d", P_sum);
        }
        else break; // stay
    }

    Sleep(1000);

    // Dealer Turn

    printf("\n\nDealer Card Open!\n\n");

    Sleep(1000);

    D_sum += print_card(Dealer_Card, &d, &A_d);
    D_sum += print_card(Dealer_Card, &d, &A_d);

    Sleep(1000);

    if(D_sum == 21)
    {
        printf("\n\n///////////////////////\n/Dealer Black Jack!!!!/\n///////////////////////");
        game_set = -1;
        return game_set;
    }

    if (A_d == 2)
    {
        D_sum -= 10;
        A_d -=1;
    }
    
    while(D_sum < 17)
    {
        D_sum += print_card(Dealer_Card, &d, &A_d);
        Sleep(1000);
        if(D_sum > 21)
        {
            if(A_d > 0)
            {
                D_sum -= 10;
                A_d -= 1;
            }
            else 
            {
                game_set = 2;
                printf("\n\nDealer Card Sum : %d", D_sum);
                return game_set;
            }
        }
    }

    printf("\n\nDealer Card Sum : %d", D_sum);

    if(P_sum < D_sum) game_set = -1;
    if(P_sum == D_sum) game_set = 0;
    if(P_sum > D_sum) game_set = 1;

    return game_set;
}

int print_card(int* Card, int* i, int* A_p)
{
    int pattern, num, Snum;

    pattern = (Card[*i] - 1) / 13;

    // ─	━	│	┃	?	?	?	?	?	?	?	?	┌	┍	┎	┏
	// ┐	┑	┒	┓	└	┕	┖	┗	┘	┙	┚	┛	├	┝	┞	┟
	// ┠	┡	┢	┣	┤	┥	┦	┧	┨	┩	┪	┫	┬	┭	┮	┯
	// ┰	┱	┲	┳	┴	┵	┶	┷	┸	┹	┺	┻	┼	┽	")
    printf("\n");
    printf("┌───────┐\n");
    printf("│       │\n");
    printf("│       │\n");



    switch (pattern)
    {
        case 0:
            printf("│ ♠ ");
            break;
        case 1:
            printf("│ ◆ ");
            break;
        case 2:
            printf("│ ♥ ");
            break;
        case 3:
            printf("│ ♣ ");
            break;
    }

    num = (Card[*i] - 1) % 13;

    switch (num)
    {
        case 0:
            printf(" A │\t");
            Snum = 11;
            *A_p += 1;
            break;
        case 10:
            printf(" J │\t");
            Snum = 10;
            break;
        case 11:
            printf(" Q │\t");
            Snum = 10;
            break;
        case 12:
            printf(" K │\t");
            Snum = 10;
            break;
        default:
            printf("%2d │\t", num + 1);
            Snum = num + 1;
    }

    printf("\n");
    printf("│       │\n");
    printf("│       │\n");
    printf("└───────┘\n");



    *i += 1;

    return Snum;
}

void game_end(int game_set)
{
    switch(game_set)
    {
        case -2:
        {
            printf("\n\n\t|Player Bust!|\n\n");
            printf("\t|Player Lose!|\n\n");
            Score -= batting_gold;
            break;
        }
        case -1:
        {
            printf("\n\n\t|Player Lose!|\n\n");
            Score -= batting_gold;
            break;
        }
        case 0:
        {
            printf("\n\n\t|Draw!|\n\n");
            break;
        }
        case 1:
        {
            printf("\n\n\t|Player Win!|\n\n");
            Score += batting_gold;
            break;
        }
        case 2:
        {
            printf("\n\n\t|Dealer Bust!|\n\n");
            printf("\n\n\t|Player Win!|\n\n");
            Score += batting_gold;
            break;
        }
        case 3:
        {
            printf("\n\n\t|Player Black Jack Win!|\n\n");
            Score += batting_gold*1.5;
            break;
        }
    }
}
