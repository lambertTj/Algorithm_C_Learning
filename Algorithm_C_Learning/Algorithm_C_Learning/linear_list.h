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

/* ---------- 驱动列表 ---------- */

//TODO 需要做的测试
/*
1.空链表中插入一个元素
2.一个元素时，往前插
3.一个元素时，往后插
4.多个元素时，往头前插，往头后插
5.多个元素时，往尾后插，往尾前插
6.多个元素时，往中间插

*/