/*线性表练习
线性顺序表一般为数组，这里不做练习
主要练习链表的基本操作
*/

#include "ErrCode.h"
#include "linear_list.h"
#include <stdlib.h>

/*****  此文件注释侧重于函数过程解释，具体函数用法请参考相应头文件中的函数说明  *****/

/*** 内部函数声明 ***/
//带static修饰，为静态函数，为该文件私有，只能在函数声明处文件使用
static LinerListNode * InitNode(int data);

/*** 函数定义 ***/

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
		return LL_LIST_ISNULL;
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
			//一个编程的好习惯，将free的指针指向空，防止再用时发生意外
			node == NULL;
			return LL_NODE_EXIST;
		}
		//往头节点前插
		if ((curr == List->head) && (data < curr->data)) {
			node->next = curr;
			curr->pre = node;
			//头节点改变
			List->head = node;
			List->len++;
			return SUCCESS;
		}
		//往尾节点后插
		if ((curr == List->tail) && (data > curr->data)) {
			node->pre = curr;
			curr->next = node;
			//尾节点改变
			List->tail = node;
			List->len++;
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
			List->len++;
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
int DeleteNode(int data, LinerList * List) {
	//检查入参
	if (List == NULL) {
		return LL_LIST_ISNULL;
	}
	if (List->head == NULL || List->tail == NULL) {
		return LL_NODE_NOTEXIST;
	}
	//寻找节点
	for (LinerListNode *curr = List->head; curr != NULL; curr = curr->next) {
		if (data == curr->data) {
			//链表中只有一个节点时
			if (List->len == 1) {
				free(curr);
				curr == NULL;
				List->head = NULL;
				List->tail = NULL;
				List->len--;
				return SUCCESS;
			}
			//删除头节点
			if (curr == List->head) {
				LinerListNode* nextNode = curr->next;
				nextNode->pre = NULL;
				List->head = nextNode;

				free(curr);
				curr == NULL;

				List->len--;
				return SUCCESS;
			}

			//删除尾节点
			if (curr == List->tail) {
				LinerListNode * preNode = curr->pre;
				preNode->next = NULL;
				List->tail = preNode;

				free(curr);
				curr == NULL;

				List->len--;
				return SUCCESS;
			}

			//删除中间节点
			LinerListNode * preNode = curr->pre;
			LinerListNode * nextNode = curr->next;

			preNode->next = nextNode;
			nextNode->pre = preNode;

			free(curr);
			curr == NULL;

			List->len--;
			return SUCCESS;
		}

	}

	return LL_NODE_NOTEXIST;
}

//寻找节点
LinerListNode * FindNode(int data, LinerList * list) {
	//检查入参
	if (list == NULL) {
		return NULL;
	}
	//遍历链表
	for (LinerListNode * curr = list->head;curr != NULL;curr = curr->next) {
		if (curr->data == data) {
			return curr;
		}
	}

	return NULL;
}

//合并链表
LinerList * MergeList(LinerList *listA, LinerList *listB) {
	//检查入参
	if (listA == NULL) {
		return listB;
	}
	if (listB == NULL) {
		return listA;
	}
	//初始化返回链表
	LinerList * result = InitLinerList();
	if (result == NULL) {
		return NULL;
	}
	//合并
	for (LinerListNode *currA = listA->head, *currB = listB->head; (currA != NULL) || (currB != NULL);) {
		//谁小放谁，或另一个链表上的节点已不存在
		if (currA->data < currB->data || currB == NULL) {
			//放入A节点
			InsertNode(currA->data, result);
			//下一个A
			currA = currA->next;
		}
		else if (currA->data > currB->data || currA == NULL) {
			//放入B节点
			InsertNode(currB->data, result);
			//下一个B
			currB = currB->next;
		}
		else if (currA->data == currB->data) {
			//一样的只放一个
			InsertNode(currA->data, result);
			//都后移一位
			currA = currA->next;
			currB = currB->next;
		}
	}

	return result;
}

//释放链表
int FreeList(LinerList * list) {
	//检查入参
	if (list == NULL) {
		return LL_LIST_ISNULL;
	}
	//先释放所有节点
	for (LinerListNode* curr = list->head; curr != NULL;) {
		//防止free风险，采用中间指针来释放指定地址的内存
		LinerListNode* tem = curr;
		curr = curr->next;//提前将curr后移
		free(tem);//释放之前记录的节点，这样就不会影响循环体中curr指针
		tem == NULL;//编程习惯，free掉的指针置空
	}
	//所有节点释放完毕，释放链表
	free(list);
	list == NULL;
	
	return SUCCESS
}