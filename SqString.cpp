/*************************************************************************************/
/*         顺序串的基本操作函数
/*------------------------------------------------------------------------------------
/*
/*
/* Date: 2016-12-15
/************************************************************************************/

#include <stdio.h>

#define MaxSize 100

//--------------------------------------------------------
//  顺序串定义 【结构体】
//--------------------------------------------------------
typedef struct
{
    char data[MaxSize];       // 字符串数组
    int  len;                 // 串长
} SqString;

//========================================================
// 字符串赋值
//========================================================
void StrAssign(SqString &str, char cstr[])    /*str为引用型参数*/
{
    int i;
    for (i=0; cstr[i]!='\0'; i++)
        str.data[i] = cstr[i];
    str.len=i;
}

//========================================================
// 求字符串的长度
//========================================================
int StrLength(SqString s)
{
    return s.len;
}

//========================================================
// 字符串复制函数，同等复制
//========================================================
void StrCopy(SqString &s, SqString t)        /*s为引用型参数*/
{
    int i;
    for (i=0;i<t.len;i++)
        s.data[i]=t.data[i];
    s.len=t.len;
}

//========================================================
// 字符串比较，判断是否相等
//========================================================
int StrEqual(SqString s, SqString t)
{
    int same=1,i;
    if (s.len!=t.len)                    /*长度不相等时，直接返回0*/
        same=0;
    else
        for (i=0;i<s.len;i++)
            if (s.data[i]!=t.data[i])    /*有一个对应字符不相同时返回0*/
            {
                same=0;
                break;
            }
    return same;
}

//========================================================
// 字符串拼接, t串加到S串的后面
//========================================================
SqString Concat(SqString s, SqString t)
{
    int i;
    SqString str;               // 创建新的字符串, 作为结果返回

    str.len=s.len+t.len;
    for (i=0;i<s.len;i++)       /*将s.data[0]～s.data[s.len-1]复制到str*/
        str.data[i]=s.data[i]; 

    for (i=0;i<t.len;i++)       /*将t.data[0]～t.data[t.len-1]复制到str*/
        str.data[s.len+i]=t.data[i];

    return str;
}

//========================================================
// 求特定位置的子串
//========================================================
SqString SubStr(SqString s, int i, int j)
{
    int k;
    SqString str;
    str.len=0;

    if (i<=0 || i>s.len || j<0 || i+j-1>s.len)
        return str;                    /*参数不正确时返回空串*/

    for (k=i-1; k<i+j-1; k++)          /*将s.data[i]～s.data[i+j]复制到str*/
        str.data[k-i+1]=s.data[k];

    str.len=j;
    return str;
} 

//========================================================
// 删除指定顺序字符
//========================================================
SqString DelStr(SqString s,int i,int j)
{
    int k;
    SqString str;
    str.len=0;

    if (i<=0 || i>s.len || i+j>s.len+1) /*参数不正确时返回空串*/
        return str;

    for (k=0;k<i-1;k++)           /*将s.data[0]～s.data[i-2]复制到str*/
        str.data[k]=s.data[k];

    for (k=i+j-1;k<s.len;k++)     /*将s.data[i+j-1]～data[s.len-1]复制到str*/
        str.data[k-j]=s.data[k];

    str.len=s.len-j;
    return str;
}

//========================================================
// 字符串插入操作，S2插入S1串 
//========================================================
SqString InsStr(SqString s1, int i, SqString s2)
{
    int j;
    SqString str;
    str.len=0;

    if (i<=0 || i>s1.len+1)     /*参数不正确时返回空串*/
        return str;

    for (j=0;j<i-1;j++)                 /*将s1.data[0]～s1.data[i-2]复制到str*/
        str.data[j]=s1.data[j];

    for (j=0;j<s2.len;j++)              /*将s2.data[0]～s2.data[s2.len-1]复制到str*/
        str.data[i+j-1]=s2.data[j];

    for (j=i-1;j<s1.len;j++)            /*将s1.data[i-1]～s.data[s1.len-1]复制到str*/
        str.data[s2.len+j]=s1.data[j];

    str.len=s1.len+s2.len;
    return str;
}

//========================================================
// 字符串替换
//========================================================
SqString RepStr(SqString s,int i,int j,SqString t)
{
    int k;
    SqString str;
    str.len=0;

    if (i<=0 || i>s.len || i+j-1>s.len) /*参数不正确时返回串s*/
        return str;
    for (k=0;k<i-1;k++)            /*将s.data[0]～s.data[i-2]复制到str*/
        str.data[k]=s.data[k];
    for (k=0;k<t.len;k++)          /*将t.data[0]～t.data[t.len-1]复制到str*/
        str.data[i+k-1]=t.data[k];
    for (k=i+j-1;k<s.len;k++)    /*将s.data[i+j-1]～data[s.len-1]复制到str*/
        str.data[t.len+k-j]=s.data[k];

    str.len=s.len-j+t.len;
    return str;
}

int Strcmp(SqString s, SqString t)
{
    int i,comlen;
    if (s.len<t.len)
        comlen=s.len;           /*求s和t的共同长度*/
    else
        comlen=t.len;

    for (i=0;i<comlen;i++)      /*在共同长度内逐个字符比较*/
        if (s.data[i]<t.data[i]) 
            return -1;
        else if (s.data[i]>t.data[i]) 
            return 1;

    if (s.len==t.len)               /*s==t*/
        return 0;
    else if (s.len<t.len)           /*s<t*/
        return -1;
    else
        return 1;                   /*s>t*/
}

//========================================================
// 打印输出字符串内容
//========================================================
void DispStr(SqString s)
{
    int i;
    if (s.len>0)
    {
        for (i=0; i<s.len; i++)
            printf("%c", s.data[i]);
        printf("\n");
    }
}

//========================================================
//    主程序
//========================================================
void main()
{
    SqString s,t;
    StrAssign(s,"abcdefg");
    StrAssign(t,"ab");
    printf("s:");DispStr(s);
    printf("t:");DispStr(t);
    printf("Strcmp(s,t)=%d\n",Strcmp(s,t));

    StrAssign(s,"abcd");
    StrAssign(t,"abcd");
    printf("s:");
    DispStr(s);
    printf("t:");
    DispStr(t);
    printf("Strcmp(s,t)=%d\n",Strcmp(s,t));
}