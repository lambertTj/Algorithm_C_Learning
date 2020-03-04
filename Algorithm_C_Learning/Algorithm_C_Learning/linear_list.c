/*线性表练习
线性顺序表一般为数组，这里不做练习
主要练习链表的基本操作
*/

#include "ErrCode.h"
#include "linear_list.h"
#include <stdlib.h>

/*****  此文件注释侧重于函数过程解释，具体函数用法请参考相应头文件中的函数说明  *****/

/* 内部函数声明 */
//带static修饰，为静态函数，为该文件私有，只能在函数声明处文件使用
static LinerListNode * InitNode(int data);

/* 函数定义 */

//初始化链表
LinerList * InitLinerList() {
	LinerList * result;
	result = (LinerList *)malloc(sizeof(LinerList));
	//判断是否成功生成
	if (result == NULL) {
		//TODO 日志  SYS_MEM_OVERFLOW
		return NULL;
	}
	//初始化其他变量
	result->head = NULL;
	result->tail = NULL;
	result->len = 0;

	return result;
}

//插入节点
int InsertNode(int data, LinerList * List) {
	//判断入参是否合法
	if (List == NULL) {
		return LL_ISNULL;
	}
	//生成结点
	LinerListNode * node = InitNode(data);
	if (node == NULL) {
		return SYS_MEM_OVERFLOW;
	}
	//如果为链表的第一个节点
	if (List->head == NULL && List->tail == NULL) {
		List->head = node;
		List->tail = node;
		List->len++;
		return SUCCESS
	}
	//中间节点的插入
	for (LinerListNode * curr = List->head; curr != NULL; curr = curr->next) {
		//判断是否是重复节点
		if (curr->data == data) {
			//释放节点
			free(node);
			return LL_NODE_EXIST;
		}
		//往头节点前插
		if ((curr == List->head) && (data < curr->data)) {
			node->next = curr;
			curr->pre = node;
			//头节点改变
			List->head = node;
			return SUCCESS;
		}
		//往尾节点后插
		if ((curr == List->tail) && (data > curr->data)) {
			node->pre = curr;
			curr->next = node;
			//尾节点改变
			List->tail = node;
			return SUCCESS;
		}
		//中间插入
		//当前节点比data小；后一节点比data大
		LinerListNode * next = curr->next;
		if ((curr->data < data) && (next->data > data)) {
			//往当前节点后插
			node->pre = curr;
			node->next = curr->next;

			next->pre = node;
			curr->next = node;
			return SUCCESS;
		}
	}

	return LL_NODE_UNINSERT;
}

//生成一个节点
LinerListNode * InitNode(int data) {
	LinerListNode *result;
	result = (LinerListNode *)malloc(sizeof(LinerListNode));
	if (result == NULL) {
		return NULL;
	}
	//填入数据
	result->data = data;
	result->pre = NULL;
	result->next = NULL;

	return result;
}

//删除节点
//入参：删除节点的数据域，对应链表
//int DeleteNode(int, LinerList *);