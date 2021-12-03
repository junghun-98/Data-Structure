#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE np

//구조체 선언
struct point {
    long x;
    long y;
};


void x_asc(struct point* p, int np); //x-축 값으로 오름차순
int swap(struct point* p, int i); //swap
int print(struct point* p, int np); //printf


int main(void)
{
    int i, np;
    struct point* p;

    printf("좌표의 개수 : ");
    scanf_s("%d", &np);
    getchar(); //줄바꿈 문자 제거

    p = (struct point*)malloc((np + 1) * sizeof(struct point));
    if (p == NULL)
    {
        printf("메모리 할당 오류\n");
        exit(1);
    }

    //x,y-축 좌표값 랜덤함수로 출력
    srand((unsigned)time(NULL));
    for (i = 0; i < SIZE; i++)
    {
        p[i].x = 1 + rand() % 32767;
        p[i].y = 1 + rand() % 32767;
    }


    //함수 호출
    printf("x축 오름차순 정렬\n");
    x_asc(p, np); //x축 오름차순 함수 호출
    print(p, np); //출력함수 호출
    printf("\n");

    printf("좌표 값 입력 : ");

    scanf_s("(%ld %ld)", &p[np].x, &p[np].y);

    x_asc(p, np + 1);
    print(p, np + 1);

    free(p);
    return 0;
}

//참조에 의한 호출을 이용해 x축 오름차순 정렬
void x_asc(struct point* p, int np)
{
    int j, k;

    //x축 오름차순 정렬
    for (k = 0; k < SIZE; k++)
    {
        for (j = 0; j < SIZE - 1; j++)
        {
            if (p[j].x > p[j + 1].x)
            {
                swap(p, j);
            }
        }
    }
}

int swap(struct point* p, int i)
{
    struct point tmp;

    tmp = p[i];
    p[i] = p[i + 1];
    p[i + 1] = tmp;

    return 0;
}

int print(struct point* p, int np)
{
    for (int i = 0; i < SIZE; i++)
    {
        printf("(%d, %d) ", p[i].x, p[i].y);
    }
    printf("\n");

    return 0;
}