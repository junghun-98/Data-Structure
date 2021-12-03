#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE np

//����ü ����
struct point {
    long x;
    long y;
};


void x_asc(struct point* p, int np); //x-�� ������ ��������
int swap(struct point* p, int i); //swap
int print(struct point* p, int np); //printf


int main(void)
{
    int i, np;
    struct point* p;

    printf("��ǥ�� ���� : ");
    scanf_s("%d", &np);
    getchar(); //�ٹٲ� ���� ����

    p = (struct point*)malloc((np + 1) * sizeof(struct point));
    if (p == NULL)
    {
        printf("�޸� �Ҵ� ����\n");
        exit(1);
    }

    //x,y-�� ��ǥ�� �����Լ��� ���
    srand((unsigned)time(NULL));
    for (i = 0; i < SIZE; i++)
    {
        p[i].x = 1 + rand() % 32767;
        p[i].y = 1 + rand() % 32767;
    }


    //�Լ� ȣ��
    printf("x�� �������� ����\n");
    x_asc(p, np); //x�� �������� �Լ� ȣ��
    print(p, np); //����Լ� ȣ��
    printf("\n");

    printf("��ǥ �� �Է� : ");

    scanf_s("(%ld %ld)", &p[np].x, &p[np].y);

    x_asc(p, np + 1);
    print(p, np + 1);

    free(p);
    return 0;
}

//������ ���� ȣ���� �̿��� x�� �������� ����
void x_asc(struct point* p, int np)
{
    int j, k;

    //x�� �������� ����
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