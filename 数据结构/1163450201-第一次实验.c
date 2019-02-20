#include <stdio.h>
#include <stdlib.h>
#include <math.h>

///ѧ�ţ�1163450201
///������
///ʵ��һ��һԪ����ʽ�Ĵ�������
///������Ա�Ķ�̬��ʽ�洢��ʵ������
///�ļ����������������ʽ
///����x0��ֵ��float��
///ʵ����������

/*�������ʽ�е���*/
typedef struct polynode
{
    double coef;    /*ϵ��*/
    int exp;        /*ָ��*/
    struct polynode * link; /*��һ��ָ��*/
}poly,*polypointer;

/*Ϊ����ʽ���������ڴ�*/
polypointer newPoly()
{
    polypointer x;
    x = (polypointer)malloc(sizeof(poly));
    if(x == NULL)
    {
        printf("�ڴ治�㣬�޷�����\n");
        exit(1);
    }
    x->coef = 0;
    x->exp = 0;
    x->link = NULL;
    return x;
}

/*����һ���½�㣬ϵ��c��ָ��e�����ӵ�x��*/
polypointer polyAttach(double c, int e, polypointer arg)
{
    polypointer x;
    x = newPoly();
    x->coef = c;
    x->exp = e;
    arg->link = x;
    return x;
}

/*��ͷ��β��ӡ����ʽ*/
void polyPrint(polypointer arg)
{
    if(arg->exp == 0)
    {
        printf("%.2lf", arg->coef);
    }
    else
    {
        printf("%.2lfX^%d", arg->coef, arg->exp);    
    }
    polypointer x = arg->link;
    while(x != NULL)
    {
        if(x->exp == 0)
        {
            if(x->coef > 0)
            {
                printf(" + %.2lf", x->coef);
            }
            else
            {
                printf(" - %.2lf", -x->coef);
            }
            x = x->link;
            continue;
        }
        if(x->coef > 0)
        {
            printf(" + %.2lfX^%d", x->coef, x->exp);
        }
        else
        {
            printf(" - %.2lfX^%d", -x->coef, x->exp);
        }
        x = x->link;
    }
    printf("\n");
}

/*����ʽ�ϲ�ͬ����*/
void polyCombine(polypointer * arg)
{
    polypointer p, q, c, d, tmp;
    double x = 0;
    p = (*arg);
    q = (*arg)->link;
    c = p;          /*cָ��q��ǰһ��*/
    d = newPoly();
    d->link = p;          /*dָ��p��ǰһ��*/
    if(q == NULL)   /*ֻ��һ��*/
    {
        if(p->coef == 0)     /*���⣺ֻ��һ���ڵ㲢��ϵ��Ϊ0*/
        {
            *arg = newPoly();   /*���ؿսڵ�*/
            return;
        }
        return;     /*ԭ������*/
    }
    while(p != NULL)
    {
        while(q != NULL)
        {
        if(q->exp == p->exp)        /*ͬ����*/
        {
            x = p->coef + q->coef;
            if(x != 0)              /*ϵ���Ͳ�����0*/
            {
                p->coef = x;
                c->link = q->link;  /*�ϲ���ɾ��q���*/
                tmp = q;
                q = q->link;
                free(tmp);
            }
            else                    /*ϵ����Ϊ0,ͬʱɾ�������ڵ�*/
            {
                if(p == *arg && (p->link != q))       /*�����һ���ڵ���ͷ�ڵ㲢��û������*/
                {
                    tmp = (*arg);
                    *arg = (*arg)->link;    /*�޸�ͷ�ڵ�*/
                    d->link = *arg;
                    free(tmp);              /*ɾ��ͷ�ڵ�*/
                    c->link = q->link;      /*ɾ��q���*/
                    tmp = q;
                    q = q->link;
                    free(tmp);
                }
                else if(p == *arg && (p->link == q))     /*�����һ���ڵ���ͷ�ڵ㲢������*/
                {
                    tmp = (*arg);
                    *arg = ((*arg)->link)->link;    /*�޸�ͷ�ڵ�*/
                    p = *arg;
                    d->link = *arg;
                    free(tmp);              /*ɾ��ͷ�ڵ�*/
                    c = *arg;
                    tmp = q;
                    q = (q->link)->link;
                    free(tmp);
                }
                else if(p != *arg && (p->link != q))              /*��һ���ڵ㲻��ͷ�ڵ㲢�Ҳ�����*/
                {
                    d->link = p->link;      /*ɾ��p�ڵ�*/
                    tmp = p;
                    p = p->link;
                    free(tmp);
                    c->link = q->link;      /*ɾ��q���*/
                    tmp = q;
                    q = q->link;
                    free(tmp);
                }
                else if(p != *arg && (p->link == q))        /*��һ���ڵ㲻��ͷ�ڵ㲢������*/
                {
                    d->link = (p->link)->link;      /*ɾ��p�ڵ�*/
                    tmp = p;
                    p = (p->link)->link;
                    free(tmp);
                    c = p;      /*ɾ��q���*/
                    tmp = q;
                    q = (q->link)->link;
                    free(tmp);
                }
                else
                {

                }
            }
        }
        else            /*����ͬ����*/
        {
            q = q->link;
            c = c->link;
        }
        }
        d = d->link;
        p = p->link;
        if(p != NULL)
        {
            q = p->link;
            c = p;
        }
    }
    p = *arg;
    d = newPoly();
    d->link = p;

    /*��ȥϵ��Ϊ0��*/
    if(p->coef == 0)  /*���ͷ�ڵ�ϵ��Ϊ0*/
    {
        tmp = p;
        *arg = p->link;
        p = p->link;
        d->link = p;
        free(tmp);
    }
    while(p != NULL)        /*��ȥϵ��Ϊ0��*/
    {
        if(p->coef == 0)
        {
            tmp = p;
            p = p->link;
            d->link = p;
            free(tmp);
            continue;
        }
        p = p->link;
        d = d->link;
    }
}

/*����ʽ��ָ���Ӵ�С�����Һϲ�ͬ����*/
void polyRank(polypointer * arg)
{
    polyCombine(arg);       /*�ϲ�ͬ����*/
    polypointer p, q, k;
    double c;
    int e;
    p = (*arg);
    q = (*arg)->link;
    k = (*arg);
    while(p->link != NULL)
    {
        while(q!= NULL)
        {
            if(q->exp > k->exp)
                k = q;  /*���ָ����p���λ��*/
            q = q->link;
        }
        if(k != p)      /*�����ȣ�����k pֵ*/
        {
            c = p->coef;
            e = p->exp;
            p->coef = k->coef;
            p->exp = k->exp;
            k->coef = c;
            k->exp = e;
        }
        p = p->link;
        q = p->link;
        k = p;
    }
}

/*�ֶ��������ʽ*/
void HandInput(polypointer * arg)
{
    double c = 0;
    int e = 0;
    char s;
    polypointer x;
    while(scanf(" %lf", &c) != EOF && scanf(" %d%c", &e, &s) != EOF)
    {
        if((*arg)->link == NULL)
            x = *arg;
        x = polyAttach(c, e, x);
        if(s == '\n')
            break;
    }
    x = *arg;
    *arg = (*arg)->link;
    free(x);
}

/*�ļ��������ʽ*/
int FileInput(polypointer * a, polypointer * b)
{
    polypointer x;
    double c = 0;
    int e = 0;
    char s;
    FILE *fp;
    if((fp = fopen("demo.txt","rt")) == NULL)
    {
        printf("�ļ�������\n");
        getchar();
        return 0;
    }
    while(fscanf(fp," %lf", &c) != EOF && fscanf(fp," %d%c", &e, &s) != EOF)
    {
        if((*a)->link == NULL)
            x = *a;
        x = polyAttach(c, e, x);
        if(s == '\n')
            break;
    }
    x = *a;
    *a = (*a)->link;
    while(fscanf(fp," %lf", &c) != EOF && fscanf(fp," %d%c", &e, &s) != EOF)
    {
        if((*b)->link == NULL)
            x = *b;
        x = polyAttach(c, e, x);
        if(s == '\n')
            break;
    }
    x = *b;
    *b = (*b)->link;
    free(x);
    fclose(fp);
    return 1;
}

/*�ļ�д��*/
int FileOutput(polypointer a, polypointer b)
{
    FILE *fp;
    polypointer x ;
    fp = fopen("demo.txt", "w");
    if(fp == NULL)
    {
        printf("�ļ�������\n");
        getchar();
        return 0;
    }
    x = a;
    while(x != NULL)
    {
        fprintf(fp, " %lf %d", x->coef, x->exp);
        x = x->link;
    }
    fprintf(fp, "\n");
    x = b;
    while(x != NULL)
    {
        fprintf(fp, " %lf %d", x->coef, x->exp);
        x = x->link;
    }
    fprintf(fp, "\n");
    fclose(fp);
    return 1;
}

/*�Ƚ�����ָ���Ĵ�С*/
char polyCompare(int a, int b)
{
    int sum = a-b;
    if(sum == 0)
        return '=';
    else if(sum > 0)
        return '>';
    else
        return '<';
}

polypointer polyAdd(polypointer a, polypointer b)
{
    polypointer p,q,c,d;
    double x;
    c = newPoly();
    p = a;q = b;
    d = c;          /*��ʼ��*/
    if(p->coef == 0 && p->link == NULL && q->coef == 0 && q->link == NULL)  /*���⣺pqֻ��һ���ڵ㲢��ϵ����Ϊ0*/
    {
        return c;
    }
    while((p!=NULL) && (q != NULL))
    {
        switch(polyCompare(p->exp , q->exp))
        {
            case '=' :
            {
                x = p->coef + q->coef;      /*ϵ�����*/
                if(x != 0)
                    d = polyAttach(x, p->exp, d);   /*����0����ȥ��һ��*/
                p = p->link;
                q = q->link;
                break;
            }
            case '>':
            {
                d = polyAttach(p->coef , p->exp, d);    /*ֱ�ӽ�p��㲢��d��*/
                p = p->link;
                break;
            }
            case '<':
            {
                d = polyAttach(q->coef, q->exp, d);     /*ֱ�ӽ�q��㲢��d��*/
                q = q->link;
                break;
            }
        }
    }
    while(p != NULL)
    {
        d = polyAttach(p->coef, p->exp, d);
        p = p->link;
    }
    while(q != NULL)
    {
        d = polyAttach(q->coef, q->exp, d);
        q = q->link;
    }
    d->link = NULL;
    p = c;
    c = c->link;
    free(p);
    polyRank(&c);
    return c;
}

polypointer polySub(polypointer a, polypointer b)
{
    polypointer p,q,c,d;
    double x;
    c = newPoly();
    p = a;q = b;
    d = c;          /*��ʼ��*/
    if(p->coef == 0 && p->link == NULL && q->coef == 0 && q->link == NULL)  /*���⣺pqֻ��һ���ڵ㲢��ϵ����Ϊ0*/
    {
        return c;
    }
    while((p!=NULL) && (q != NULL))
    {
        switch(polyCompare(p->exp , q->exp))
        {
            case '=' :
            {
                x = p->coef - q->coef;      /*ϵ�����*/
                if(x != 0)
                    d = polyAttach(x, p->exp, d);   /*����0����ȥ��һ��*/
                p = p->link;
                q = q->link;
                break;
            }
            case '>':
            {
                d = polyAttach(p->coef , p->exp, d);    /*ֱ�ӽ�p��㲢��d��*/
                p = p->link;
                break;
            }
            case '<':
            {
                d = polyAttach((-q->coef), q->exp, d);     /*ֱ�ӽ�q��㲢��d��,���ҽ�qϵ����Ϊ�෴��*/
                q = q->link;
                break;
            }
        }
    }
    while(p != NULL)
    {
        d = polyAttach(p->coef, p->exp, d);
        p = p->link;
    }
    while(q != NULL)
    {
        d = polyAttach((-q->coef), q->exp, d);
        q = q->link;
    }
    d->link = NULL;
    p = c;
    c = c->link;
    free(p);
    polyRank(&c);
    return c;
}

polypointer polyMul(polypointer a, polypointer b)
{
    polypointer p, q, c, h, t;
    c = newPoly();
    p = a;
    q = b;
    h = c;      /*������ͷ�ڵ�*/
    c->link = h;/*������������*/
    t = c;      /*����β�ڵ�*/
    double co = 0;
    int e = 0;
    while(p != NULL)
    {
        while(q != NULL)
        {
            co = p->coef * q->coef;
            e = p->exp + q->exp;
            while(c != NULL)      /*Ѱ��ƥ����*/
            {
                if(e == c->exp)
                {
                    c->coef = co + c->coef;
                    break;
                }
                c = c->link;
                if(c->link == h)
                {
                    c = polyAttach(co, e, c);
                    c->link = h;    /*βָ��ָ��ͷ�ڵ㣬ѭ������*/
                    t = c;
                    break;
                }
            }
            q = q->link;
        }
        p = p->link;
        q = b;  /*��λ*/
    }
    t->link = NULL;     /*�޸�β�ڵ�*/
    if(h->link != NULL && h->coef == 0) /*�Ƿ��һ���ڵ�*/
    {
        p = h;
        h = h->link;
        free(p);
    }
    polyRank(&h);   /*����ʽ����*/
    return h;
}

polypointer polyDiv(polypointer a, polypointer b)
{
    polypointer p, q, c, d, e, h;  /*c �����d ���*��ʽ��e ��ʽ���µı���ʽ��*/
    double co = 0;
    int ex = 0;
    p = a;
    q = b;
    e = p;
    c = newPoly();
    h = c;
    if(p->exp < q->exp)     /*����ʽ�����ָ��С�ڳ�ʽָ����������Ϊ����ʽ*/
    {
        c = p;
        return c;
    }
    while(e->exp >= q->exp)
    {
        co = e->coef / q->coef;
        ex = e->exp - q->exp;
        c = polyAttach(co, ex, c);
        d = polyMul(c, q);
        e = polySub(e, d);      /*�µı���ʽ*/
    }
    printf("��ʽ֮����Ϊ�� ");
    polyPrint(e);
    c = h->link;
    free(h);
    polyRank(&c);
    return c;
}

/*����x=x0����ʽ�ĺ�*/
float polyCalc(polypointer arg, float x)
{
    double sum = 0;
    double result = 0;
    while(arg != NULL)
    {
        result = pow((double)x, (double)arg->exp);
        sum = sum + (arg->coef) * result ;
        arg = arg->link;
    }
    return sum;
}

void polyState(polypointer a, polypointer b)
{
    printf( "========================\n"
            "���ݽṹ���㷨��һ��ʵ��\n"
            "A:");
    polyPrint(a);
    printf("B:");
    polyPrint(b);
    printf("========================\n");

}

/*�˵�*/
void Menu()
{
    polypointer a,b,c;  /*����3������ʽָ��*/
    a = newPoly();
    b = newPoly();
    c = newPoly();         /*��ʼ��*/
    float x = 0;
    while(1)
    {
        fflush(stdin);
        char op;
        system("cls");
        polyState(a, b);
        printf("1.����ָ���������ж���ʽ\n"
               "2.����x=x0��ֵ\n"
               "3.����ʽ����������\n"
               "4.��ӡ��ǰ����ʽ\n");
        op = getchar();
        switch(op)
        {
        case '1':
            {
                fflush(stdin);
                system("cls");
                polyState(a, b);
                printf("1.�ֶ�����\n2.�ļ�����\n3.�ļ����\n");
                op = getchar();
                if(op == '1')
                {
                    a = newPoly();
                    b = newPoly();
                    printf("�������һ������ʽ��ϵ����ָ�����м�ո�ֿ�,�س�ȷ��\n");
                    HandInput(&a);
                    polyRank(&a);
                    polyPrint(a);
                    printf("������ڶ�������ʽ��ϵ����ָ�����м�ո�ֿ�,�س�ȷ��\n");
                    HandInput(&b);
                    polyRank(&b);
                    polyPrint(b);
                    printf("�������������\n");
                    fflush(stdin);
                    getchar();
                }
                else if(op == '2')
                {
                    a = newPoly();
                    b = newPoly();
                    FileInput(&a, &b);
                    polyRank(&a);
                    polyRank(&b);
                    polyPrint(a);
                    polyPrint(b);
                    printf("�������������\n");
                    fflush(stdin);
                    getchar();
                }
                else if(op == '3')
                {
                    if(!FileOutput(a, b))
                    {
                        printf("�������\n");
                    }
                    printf("�������������\n");
                    fflush(stdin);
                    getchar();
                }
                else
                    printf("ѡ�����\n");
                break;
            }
        case '2':
            {
                printf("������x0��ֵ\n");
                scanf("%f", &x);
                printf("x=%f�ļ�����Ϊ�� \nA: %f\nB: %f\n", x,polyCalc(a, x), polyCalc(b,x));
                printf("�������������\n");
                fflush(stdin);
                getchar();
                break;
            }
        case '3':
            {
                fflush(stdin);
                system("cls");
                polyState(a, b);
                printf("1.����ʽ�ӷ�\n2.����ʽ����\n3.����ʽ�˷�\n4.����ʽ����\n");
                op = getchar();
                if(op == '1')
                {
                    polyPrint(a);
                    polyPrint(b);
                    c = polyAdd(a, b);
                    printf("��ʽ֮��Ϊ�� ");
                    polyPrint(c);
                    printf("�������������\n");
                    fflush(stdin);
                    getchar();
                }
                else if(op == '2')
                {
                    polyPrint(a);
                    polyPrint(b);
                    c = polySub(a, b);
                    printf("��ʽ֮��Ϊ�� ");
                    polyPrint(c);
                    printf("�������������\n");
                    fflush(stdin);
                    getchar();
                }
                else if(op == '3')
                {
                    polyPrint(a);
                    polyPrint(b);
                    c = polyMul(a, b);
                    printf("��ʽ֮��Ϊ�� ");
                    polyPrint(c);
                    printf("�������������\n");
                    fflush(stdin);
                    getchar();
                }
                else if(op == '4')
                {
                    polyPrint(a);
                    polyPrint(b);
                    c = polyDiv(a, b);
                    printf("��ʽ֮��Ϊ�� ");
                    polyPrint(c);
                    printf("�������������\n");
                    fflush(stdin);
                    getchar();
                }
                else
                {
                    printf("ѡ�����");
                    printf("�������������\n");
                    fflush(stdin);
                    getchar();
                }

                break;
            }
            case '4':
            {
                polyPrint(a);
                polyPrint(b);
                printf("�������������\n");
                fflush(stdin);
                getchar();
                break;
            }
            default :
                {

                }

        }
    }

}

int main()
{
    Menu();
    return 0;
}