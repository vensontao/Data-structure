/*************************************************************************************/
/*         链串的基本操作函数
/*------------------------------------------------------------------------------------
/*
/*
/* Date: 2016-12-15
/************************************************************************************/

#include <stdio.h>
#include <malloc.h>

//--------------------------------------------------------
//  顺序串定义 【结构体】
//--------------------------------------------------------
typedef struct snode 
{    
    char data;
    struct snode *next;
} LiString;

//========================================================
// 字符串赋值
//========================================================
void StrAssign(LiString *&s,char t[])
{
    int i;
    LiString *r,*p;    
    s=(LiString *)malloc(sizeof(LiString));
    r=s;        /*r始终指向尾结点*/
    for (i=0;t[i]!='\0';i++) 
    { 
        p=(LiString *)malloc(sizeof(LiString));
        p->data=t[i];
        r->next=p;
        r=p;
    }
    r->next=NULL;
}

//========================================================
// 字符串复制函数，同等复制
//========================================================
void StrCopy(LiString *&s,LiString *t)
{
    LiString *p=t->next,*q,*r;
    s=(LiString *)malloc(sizeof(LiString));
    r=s;                /*r始终指向尾结点*/
    while (p!=NULL)         /*将t的所有结点复制到s*/
    {    
        q=(LiString *)malloc(sizeof(LiString));
        q->data=p->data;
        r->next=q;
        r=q;
        p=p->next;
    }
    r->next=NULL;
}

//========================================================
// 字符串比较，判断是否相等
//========================================================
int StrEqual(LiString *s,LiString *t)
{
    LiString *p=s->next,*q=t->next;
    while (p!=NULL && q!=NULL && p->data==q->data) 
    {    
        p=p->next;
        q=q->next;
    }
    if (p==NULL && q==NULL)
        return 1;
    else
        return 0;
}

//========================================================
// 求字符串的长度
//========================================================
int StrLength(LiString *s)
{
    int i=0;
    LiString *p=s->next;
    while (p!=NULL) 
    {       
        i++;
        p=p->next;
    }
    return i;
}

//========================================================
// 字符串拼接
//========================================================
LiString *Concat(LiString *s,LiString *t)
{
    LiString *str,*p=s->next,*q,*r;
    str=(LiString *)malloc(sizeof(LiString));
    r=str;
    while (p!=NULL)             /*将s的所有结点复制到str*/
    {    
        q=(LiString *)malloc(sizeof(LiString));
        q->data=p->data;
        r->next=q;
        r=q;
        p=p->next;
    }

    p=t->next;
    while (p!=NULL)             /*将t的所有结点复制到str*/
    {    
        q=(LiString *)malloc(sizeof(LiString));
        q->data=p->data;
        r->next=q;
        r=q;
        p=p->next;
    }
    r->next=NULL;
    return str;
}

//========================================================
// 求特定位置的子串
//========================================================
LiString *SubStr(LiString *s,int i,int j)
{
    int k;
    LiString *str,*p=s->next,*q,*r;
    str=(LiString *)malloc(sizeof(LiString));
    str->next=NULL;
    r=str;                        /*r指向新建链表的尾结点*/
    if (i<=0 || i>StrLength(s) || j<0 || i+j-1>StrLength(s))
        return str;                 /*参数不正确时返回空串*/
    for (k=0;k<i-1;k++)
        p=p->next;
    for (k=1;k<=j;k++)              /*将s的第i个结点开始的j个结点复制到str*/
    {    
        q=(LiString *)malloc(sizeof(LiString));
        q->data=p->data;
        r->next=q;r=q;
        p=p->next;
    }
    r->next=NULL;
    return str;
}

//========================================================
// 字符串插入操作，S2插入S1串
//========================================================
LiString *InsStr(LiString *s,int i,LiString *t)
{
    int k;
    LiString *str,*p=s->next,*p1=t->next,*q,*r;
    str=(LiString *)malloc(sizeof(LiString));
    str->next=NULL;
    r=str;                                /*r指向新建链表的尾结点*/
    if (i<=0 || i>StrLength(s)+1)          /*参数不正确时返回空串*/
        return str;
    for (k=1;k<i;k++)                    /*将s的前i个结点复制到str*/
    {
        q=(LiString *)malloc(sizeof(LiString));
        q->data=p->data;
        r->next=q;r=q;
        p=p->next;
    }
    while (p1!=NULL)                        /*将t的所有结点复制到str*/
    {
        q=(LiString *)malloc(sizeof(LiString));
        q->data=p1->data;
        r->next=q;r=q;
        p1=p1->next;
    }
    while (p!=NULL)                      /*将*p及其后的结点复制到str*/
    {
        q=(LiString *)malloc(sizeof(LiString));
        q->data=p->data;
        r->next=q;r=q;
        p=p->next;
    }
    r->next=NULL;
    return str;
}

//========================================================
// 删除指定顺序字符
//========================================================
LiString *DelStr(LiString *s,int i,int j)
{
    int k;
    LiString *str,*p=s->next,*q,*r;
    str=(LiString *)malloc(sizeof(LiString));
    r=str;                        /*r指向新建链表的尾结点*/
    if (i<=0 || i>StrLength(s) || j<0 || i+j-1>StrLength(s))
        return str;               /*参数不正确时返回空串*/
    for (k=0;k<i-1;k++)          /*将s的前i-1个结点复制到str*/
    {
        q=(LiString *)malloc(sizeof(LiString));
        q->data=p->data;
        r->next=q;r=q;
        p=p->next;
    }
    for (k=0;k<j;k++)                 /*让p沿next跳j个结点*/
        p=p->next;
    while (p!=NULL)                    /*将*p及其后的结点复制到str*/
    {
        q=(LiString *)malloc(sizeof(LiString));
        q->data=p->data;
        r->next=q;r=q;
        p=p->next;
    }
    r->next=NULL;
    return str;
}

//========================================================
// 字符串替换
//========================================================
LiString *RepStr(LiString *s,int i,int j,LiString *t)
{
    int k;
    LiString *str,*p=s->next,*p1=t->next,*q,*r;
    str=(LiString *)malloc(sizeof(LiString));
    str->next=NULL;
    r=str;                            /*r指向新建链表的尾结点*/
    if (i<=0 || i>StrLength(s) || j<0 || i+j-1>StrLength(s))
        return str;                      /*参数不正确时返回空串*/
    for (k=0;k<i-1;k++)              /*将s的前i-1个结点复制到str*/
    {
        q=(LiString *)malloc(sizeof(LiString));
        q->data=p->data;q->next=NULL;
        r->next=q;r=q;
        p=p->next;
    }
    for (k=0;k<j;k++)               /*让p沿next跳j个结点*/
        p=p->next;
    while (p1!=NULL)                 /*将t的所有结点复制到str*/
    {
        q=(LiString *)malloc(sizeof(LiString));
        q->data=p1->data;q->next=NULL;
        r->next=q;r=q;
        p1=p1->next;
    }
    while (p!=NULL)                  /*将*p及其后的结点复制到str*/
    {
        q=(LiString *)malloc(sizeof(LiString));
        q->data=p->data;q->next=NULL;
        r->next=q;r=q;
        p=p->next;
    }
    return str;
}

void Repl(LiString *&s)
{
    LiString *p=s->next,*q;
    int find=0;
    while (p->next!=NULL && find==0)    /*查找'ab'子串*/
    {
        if (p->data=='a' && p->next->data=='b')       /*找到了ab子串*/
        {    
            p->data='x';p->next->data='z';            /*替换为xyz*/
            q=(LiString *)malloc(sizeof(LiString));
            q->data='y';q->next=p->next;p->next=q;
            find=1;
        }
        else p=p->next; 
    }
}

//========================================================
// 打印输出字符串内容
//========================================================
void DispStr(LiString *s)
{
    LiString *p=s->next;
    while (p!=NULL) 
    {
        printf("%c",p->data);
        p=p->next;
    }
    printf("\n");
}

void main()
{
    LiString *s;
    StrAssign(s,"aabcabcd");
    printf("s:");DispStr(s);
    printf("ab->xyz\n");
    Repl(s);
    printf("s:");DispStr(s);
}