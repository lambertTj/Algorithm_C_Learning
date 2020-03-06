/*线性表练习
线性顺序表一般为数组，这里不做练习
主要练习链表的基本操作
*/
#pragma once

#define LINER_LIST_MAXLEN 1024 //链表最大长度

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
LinerListNode * FindNode(int, LinerList *);

//合并链表
//入参：待合并的两张链表。返回：合并后的链表。
//若任意链表为空，则返回另一张链表
LinerList * MergeList(LinerList *,LinerList *);

//释放链表
//入参：需要释放的链表
int FreeList(LinerList *);

//打印链表
//入参：待打印链表
int PrintList(LinerList *);

//驱动测试
int Drive_LL();
