/*************************************************************************************/
/*         顺序表基本操作函数
/*------------------------------------------------------------------------------------
/*
/* 
/* 创建日期： 2016年12月27日
/************************************************************************************/

#include <stdio.h>
#include <malloc.h>

#define MaxSize 100

typedef char ElemType;

//--------------------------------------------------------
// 顺序表的类型定义
//--------------------------------------------------------
typedef struct 
{
    ElemType data[MaxSize];        // 存放顺序表元素
    int length;                    // 存放顺序表的长度
} SqList;

//========================================================
// 初始化顺序表
//========================================================
void InitList(SqList *&L)
{
    L=(SqList *)malloc(sizeof(SqList));    /*分配存放线性表的空间*/
    L->length=0;
}

//========================================================
// 建立顺序表
//========================================================
void CreateList(SqList *&L, ElemType a[], int n)
{
    int i;
    for (i=0;i<n;i++)
        L->data[i]=a[i];
    L->length=n;
}

//========================================================
// 销毁顺序表
//========================================================
void DestroyList(SqList *&L)
{
    free(L);
}

//========================================================
// 判断顺序表是否为空
//========================================================
int ListEmpty(SqList *L)
{
    return (L->length==0);
}

//========================================================
// 求顺序表的长度
//========================================================
int ListLength(SqList *L)
{
    return (L->length);
}

//========================================================
// 输出顺序表元素
//========================================================
void DispList(SqList *L)
{
    int i;
    if (ListEmpty(L)) 
        return;
    for (i=0;i<L->length;i++)
        printf(" %c ",L->data[i]);
    printf("\n");
}

//========================================================
// 求顺序表中某个元素的值
//========================================================
int GetElem(SqList *L,int i,ElemType &e)
{
    if (i<1 || i>L->length)
        return 0;
    e=L->data[i-1];
    return 1;
}

//========================================================
// 求顺序表中某个元素的位置
//========================================================
int LocateElem(SqList *L, ElemType e)
{
    int i=0;
    while (i<L->length && L->data[i]!=e) 
        i++;
    if (i>=L->length)
        return 0;
    else
        return i+1;
}

//========================================================
// 向顺序表指定位置插入元素
//========================================================
int ListInsert(SqList *&L,int i,ElemType e)
{
    int j;
    if (i<1 || i>L->length+1)
        return 0;
    i--;                          /*将顺序表位序转化为elem下标*/
    for (j=L->length;j>i;j--)     /*将data[i]及后面元素后移一个位置*/
        L->data[j]=L->data[j-1];
    L->data[i]=e;
    L->length++;                  /*顺序表长度增1*/
    return 1;
}

//========================================================
// 删除顺序表中指定位置的元素
//========================================================
int ListDelete(SqList *&L,int i,ElemType &e)
{
    int j;
    if (i<1 || i>L->length)
        return 0;
    i--;                           /*将顺序表位序转化为elem下标*/
    e=L->data[i];
    for (j=i;j<L->length-1;j++)    /*将data[i]之后的元素前移一个位置*/
        L->data[j]=L->data[j+1];
    L->length--;                   /*顺序表长度减1*/
    return 1;
}

//========================================================
// 两顺序表合并
//========================================================
void unionList(SqList *LA, SqList *LB, SqList *&LC)
{
    int lena,i;
    ElemType e;
    InitList(LC);
    for (i=1;i<=ListLength(LA);i++)    /*将LA的所有元素插入到Lc中*/
    {    
        GetElem(LA,i,e);
        ListInsert(LC,i,e);
    }
    lena=ListLength(LA);                /*求线性表LA的长度*/

    for (i=1;i<=ListLength(LB);i++) 
    {    
        GetElem(LB,i,e);                 /*取LB中第i个数据元素赋给e*/
        if (!LocateElem(LA,e)) 
            ListInsert(LC,++lena,e);     /*LA中不存在和e相同者,则插入到LC中*/
    }
}

//---------------------------------------------------------
// 测试接口 
//---------------------------------------------------------
int main()
{
    SqList *L;
    ElemType e;
    InitList(L);
    ListInsert(L,1,'a');
    ListInsert(L,2,'c');
    ListInsert(L,3,'a');
    ListInsert(L,4,'d');
    ListInsert(L,5,'b');
    printf("ListLength(L)=%d\n",ListLength(L));
    printf("ListEmpty(L)=%d\n",ListEmpty(L));
    GetElem(L,3,e);
    printf("e=%c\n",e);
    printf("LocateElem(L,'a')=%d\n",LocateElem(L,'a'));
    ListInsert(L,4,'e');
    DispList(L);
    ListDelete(L,3,e);
    DispList(L);
    DestroyList(L);

    SqList *LA,*LB,*LC;
    InitList(LA);
    InitList(LB);

    /*构造LA={'a','c','b'}*/
    ListInsert(LA,1,'a');
    ListInsert(LA,2,'c');
    ListInsert(LA,3,'b');
    printf("LA:");
    DispList(LA);

    /*构造LB={'a','d','b'}*/
    ListInsert(LB,1,'a');
    ListInsert(LB,2,'d');
    ListInsert(LB,3,'b');
    printf("LB:");
    DispList(LB);

    unionList(LA,LB,LC);
    printf("LC=LA∪LB\n");
    printf("LC:");
    DispList(LC);
    DestroyList(LA);
    DestroyList(LB);
    DestroyList(LC);
}