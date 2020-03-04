/*线性表练习
线性顺序表一般为数组，这里不做练习
主要练习链表的基本操作
*/
#pragma once

//链表节点，双向链表
//链表不允许重复节点
typedef struct {
	int data;	//数据阈采用一个整数，复杂情况也可以是结构体，链表默认从小到大排列
	struct LinerListNode *next;
	struct LinerListNode *pre;
} LinerListNode;

//链表
typedef struct  {
	int len;//链表长度
	LinerListNode *head;
	LinerListNode *tail;
} LinerList;

/* ---------- 方法列表 ---------- */
//如无特殊说明，以下函数返回值int代表操作是否成功
//成功返回0，非零返回值参考"ErrCode.h"中的宏定义

//初始化链表
//头节点为空，长度为0
//初始化成功返回生成链表的地址，不成功返回空指针
LinerList * InitLinerList();

//插入节点
//自动按从小到大的顺序插入
//入参：插入节点的数据域，对应链表
int InsertNode(int,LinerList *);

//删除节点
//入参：删除节点的数据域，对应链表
int DeleteNode(int, LinerList *);

//寻找节点
//入参：待寻找数据域，对应链表。返回：对应节点，若没找到则返回NULL
int FindNode(int, LinerList *);

/* ---------- 驱动列表 ---------- */

//TODO 需要做的测试
/*
1.空链表中插入一个元素
2.一个元素时，往前插
3.一个元素时，往后插
4.多个元素时，往头前插，往头后插
5.多个元素时，往尾后插，往尾前插
6.多个元素时，往中间插

7.链表不存在的报错 
8.删除一个不存在的元素
9.删除头节点，之后再往前插，或往后插
10.删除尾节点，之后再往前插，或往后插
11.删除只有一个元素时，再插入一个元素
12.删除中间节点，再在中间节点前后两个元素上，进行前后插入
*/