/*************************************************************************************/
/*         双链表基本操作函数
/*------------------------------------------------------------------------------------
/*
/*
/* 创建时间; 2016年12月27日
/************************************************************************************/

#include <stdio.h>
#include <malloc.h>

typedef char ElemType;

//-----------------------------------------------------------------------------------
// 定义双链表结点类型
//-----------------------------------------------------------------------------------
typedef struct DNode        //定义双链表结点类型
{
    ElemType data;
    struct DNode *prior;    // 指向前驱结点
    struct DNode *next;     // 指向后继结点
} DLinkList;

//===================================================================================
// 初始化双链表函数
//===================================================================================
void InitList(DLinkList *&L)
{
    L=(DLinkList *)malloc(sizeof(DLinkList));      // 创建头结点
    L->prior=NULL;                                 // 指针均为空
    L->next=NULL;
}

//===================================================================================
// 头插法建双链表
//===================================================================================
void CreateListF(DLinkList *&L, ElemType a[], int n)
{
    int i;
    DLinkList *s;
    L=(DLinkList *)malloc(sizeof(DLinkList));      // 创建头结点
    L->prior=NULL;
    L->next=NULL;

    for (i=0;i<n;i++)
    {    
        s=(DLinkList *)malloc(sizeof(DLinkList)); // 创建新结点
        s->data=a[i];
        s->next=L->next;                          // 将*s插在原开始结点之前,头结点之后
        if (L->next!=NULL)
            L->next->prior=s;
        L->next=s;
        s->prior=L;
    }
}

//===================================================================================
// 尾插法建双链表
//===================================================================================
void CreateListR(DLinkList *&L,ElemType a[],int n)
{
    int i;
    DLinkList *s,*r;
    L=(DLinkList *)malloc(sizeof(DLinkList));      // 创建头结点
    L->prior=NULL;
    L->next=NULL;
    r=L;                    // r始终指向终端结点,开始时指向头结点

    for (i=0;i<n;i++)
    {
        s=(DLinkList *)malloc(sizeof(DLinkList));/*创建新结点*/
        s->data=a[i];
        r->next=s;
        s->prior=r;        // 将*s插入*r之后
        r=s;
    }
    r->next=NULL;         /*终端结点next域置为NULL*/
}

//===================================================================================
//  双链表删除元素
//===================================================================================
void DestroyList(DLinkList *&L)
{
    DLinkList *p=L,*q=p->next;
    while (q!=NULL)
    {
        free(p);
        p=q;
        q=p->next;
    }
    free(p);
}

//===================================================================================
//  判断双链表是否为空
//===================================================================================
int ListEmpty(DLinkList *L)
{
    return(L->next==NULL);
}

//===================================================================================
//  求双链表的长度
//===================================================================================
int ListLength(DLinkList *L)
{
    int i=0;
    DLinkList *p=L;
    while (p->next!=NULL)
    {
        i++;
        p=p->next;
    }
    return(i);
}

//===================================================================================
// 展示双链表中的元素
//===================================================================================
void DispList(DLinkList *L)
{
    DLinkList *p=L->next;
    while (p!=NULL)
    {
        printf("%c ",p->data);
        p=p->next;
    }
    printf("\n");
}

//===================================================================================
// 获取双链表中指定元素
//===================================================================================
int GetElem(DLinkList *L, int i, ElemType &e)
{
    int j=0;
    DLinkList *p=L;
    while (j<i && p!=NULL)
    {
        j++;
        p=p->next;
    }
    if (p==NULL)
        return 0;
    else
    {
        e=p->data;
        return 1;
    }
}

//===================================================================================
// 获取双链中指定元素的索引
//===================================================================================
int LocateElem(DLinkList *L, ElemType e)
{
    int n=1;
    DLinkList *p=L->next;
    while (p!=NULL && p->data!=e)
    {
        n++;
        p=p->next;
    }
    if (p==NULL)
        return(0);
    else
        return(n);
}

//===================================================================================
// 双链表插入新的元素
//===================================================================================
int ListInsert(DLinkList *&L,int i,ElemType e)
{
    int j=0;
    DLinkList *p=L,*s;
    while (j<i-1 && p!=NULL)
    {
        j++;
        p=p->next;
    }
    if (p==NULL)    /*未找到第i-1个结点*/
        return 0;
    else            /*找到第i-1个结点*p*/
    {
        s=(DLinkList *)malloc(sizeof(DLinkList));    /*创建新结点*s*/
        s->data=e;    
        s->next=p->next;        /*将*s插入到*p之后*/
        if (p->next!=NULL) 
            p->next->prior=s;
        s->prior=p;
        p->next=s;
        return 1;
    }
}

//===================================================================================
// 双链表删除元素
//===================================================================================
int ListDelete(DLinkList *&L, int i, ElemType &e)
{
    int j=0;
    DLinkList *p=L,*q;
    while (j<i-1 && p!=NULL)
    {
        j++;
        p=p->next;
    }
    if (p==NULL)                /*未找到第i-1个结点*/
        return 0;
    else                        /*找到第i-1个结点*p*/
    {
        q=p->next;                /*q指向要删除的结点*/
        if (q==NULL)
           return 0;            /*不存在第i个结点*/
        p->next=q->next;        /*从单链表中删除*q结点*/
        if (p->next!=NULL)
            p->next->prior=p;
        free(q);                /*释放*q结点*/
        return 1;
    }
}

//===================================================================================
// 双链表元素排序
//===================================================================================
void sort(LinkList *&L)
{
    LinkList *p=L->next,*q,*r;
    if (p!=NULL)                 /*若原单链表中有一个或以上的数据结点*/
    {
        r=p->next;               /*r保存*p结点后继结点的指针*/
        p->next=NULL;            /*构造只含一个数据结点的有序表*/
        p=r;

        while (p!=NULL)
        {
            r=p->next;          /*r保存*p结点后继结点的指针*/
            q=L;
            while (q->next!=NULL && q->next->data<p->data)
                q=q->next;      /*在有序表中找插入*p的前驱结点*q*/
            p->next=q->next;    /*将*p插入到*q之后*/
            q->next=p;
            p=r;                /*扫描原单链表余下的结点*/
        }
    }
}

//-----------------------------------------------------------------------------------
// 双链表元素排序
//-----------------------------------------------------------------------------------
void main()
{
    LinkList *L;
    int n=10;
    char a[]={'1','3','2','9','0','4','7','6','5','8'};
    InitList(L);
    CreateListR(L,a,n);
    printf("L:");
    DispList(L);
    printf("排序\n");
    sort(L);
    printf("L:");
    DispList(L);
    DestroyList(L);
}