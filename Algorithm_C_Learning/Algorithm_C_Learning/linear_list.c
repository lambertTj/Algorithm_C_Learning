/*���Ա���ϰ
����˳���һ��Ϊ���飬���ﲻ����ϰ
��Ҫ��ϰ����Ļ�������
*/

#include "ErrCode.h"
#include "linear_list.h"
#include <stdlib.h>
#include <stdio.h>

/*****  ���ļ�ע�Ͳ����ں������̽��ͣ����庯���÷���ο���Ӧͷ�ļ��еĺ���˵��  *****/

/*** �ڲ��������� ***/
//��static���Σ�Ϊ��̬������Ϊ���ļ�˽�У�ֻ���ں����������ļ�ʹ��
static LinerListNode * InitNode(int data);

/*** �������� ***/

//��ʼ������
LinerList * InitLinerList() {
	LinerList * result;
	result = (LinerList *)malloc(sizeof(LinerList));
	//�ж��Ƿ�ɹ�����
	if (result == NULL) {
		//TODO ��־  SYS_MEM_OVERFLOW
		return NULL;
	}
	//��ʼ����������
	result->head = NULL;
	result->tail = NULL;
	result->len = 0;

	return result;
}

//����ڵ�
int InsertNode(int data, LinerList * List) {
	//�ж�����Ƿ�Ϸ�
	if (List == NULL) {
		return LL_LIST_ISNULL;
	}
	if (List->len >= LINER_LIST_MAXLEN) {
		return LL_LEN_OVERFLOW;
	}
	//���ɽ��444
	LinerListNode * node = InitNode(data);
	if (node == NULL) {
		return SYS_MEM_OVERFLOW;
	}
	//���Ϊ����ĵ�һ���ڵ�
	if (List->head == NULL && List->tail == NULL) {
		List->head = node;
		List->tail = node;
		List->len++;
		return SUCCESS;
	}
	//�м�ڵ�Ĳ���
	for (LinerListNode * curr = List->head; curr != NULL; curr = curr->next) {
		//�ж��Ƿ����ظ��ڵ�
		if (curr->data == data) {
			//�ͷŽڵ�
			free(node);
			//һ����̵ĺ�ϰ�ߣ���free��ָ��ָ��գ���ֹ����ʱ��������
			node == NULL;
			return LL_NODE_EXIST;
		}
		//��ͷ�ڵ�ǰ��
		if ((curr == List->head) && (data < curr->data)) {
			node->next = curr;
			curr->pre = node;
			//ͷ�ڵ�ı�
			List->head = node;
			List->len++;
			return SUCCESS;
		}
		//��β�ڵ���
		if ((curr == List->tail) && (data > curr->data)) {
			node->pre = curr;
			curr->next = node;
			//β�ڵ�ı�
			List->tail = node;
			List->len++;
			return SUCCESS;
		}
		//�м����
		//��ǰ�ڵ��dataС����һ�ڵ��data��
		LinerListNode * next = curr->next;
		if ((curr->data < data) && (next->data > data)) {
			//����ǰ�ڵ���
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

//����һ���ڵ�
LinerListNode * InitNode(int data) {
	LinerListNode *result;
	result = (LinerListNode *)malloc(sizeof(LinerListNode));
	if (result == NULL) {
		return NULL;
	}
	//��������
	result->data = data;
	result->pre = NULL;
	result->next = NULL;

	return result;
}

//ɾ���ڵ�
int DeleteNode(int data, LinerList * List) {
	//������
	if (List == NULL) {
		return LL_LIST_ISNULL;
	}
	if (List->head == NULL || List->tail == NULL) {
		return LL_NODE_NOTEXIST;
	}
	//Ѱ�ҽڵ�
	for (LinerListNode *curr = List->head; curr != NULL; curr = curr->next) {
		if (data == curr->data) {
			//������ֻ��һ���ڵ�ʱ
			if (List->len == 1) {
				free(curr);
				curr == NULL;
				List->head = NULL;
				List->tail = NULL;
				List->len--;
				return SUCCESS;
			}
			//ɾ��ͷ�ڵ�
			if (curr == List->head) {
				LinerListNode* nextNode = curr->next;
				nextNode->pre = NULL;
				List->head = nextNode;

				free(curr);
				curr == NULL;

				List->len--;
				return SUCCESS;
			}

			//ɾ��β�ڵ�
			if (curr == List->tail) {
				LinerListNode * preNode = curr->pre;
				preNode->next = NULL;
				List->tail = preNode;

				free(curr);
				curr == NULL;

				List->len--;
				return SUCCESS;
			}

			//ɾ���м�ڵ�
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

//Ѱ�ҽڵ�
LinerListNode * FindNode(int data, LinerList * list) {
	//������
	if (list == NULL) {
		return NULL;
	}
	//��������
	for (LinerListNode * curr = list->head;curr != NULL;curr = curr->next) {
		if (curr->data == data) {
			return curr;
		}
	}

	return NULL;
}

//�ϲ�����
LinerList * MergeList(LinerList *listA, LinerList *listB) {
	//������
	if (listA == NULL) {
		return listB;
	}
	if (listB == NULL) {
		return listA;
	}
	if ((listA->len + listB->len) >= LINER_LIST_MAXLEN) {
		return NULL;
	}
	//��ʼ����������
	LinerList * result = InitLinerList();
	if (result == NULL) {
		return NULL;
	}
	//�ϲ�
	for (LinerListNode *currA = listA->head, *currB = listB->head; (currA != NULL) || (currB != NULL);) {
		//˭С��˭������һ�������ϵĽڵ��Ѳ�����
		if ((currA != NULL && currB == NULL) || (currA != NULL && currB != NULL && currA->data < currB->data) ) {
			//����A�ڵ�
			InsertNode(currA->data, result);
			//��һ��A
			currA = currA->next;
		}
		else if ((currA == NULL && currB != NULL) || (currA != NULL && currB != NULL && currA->data > currB->data)) {
			//����B�ڵ�
			InsertNode(currB->data, result);
			//��һ��B
			currB = currB->next;
		}
		else if (currA != NULL && currB != NULL && currA->data == currB->data) {
			//һ����ֻ��һ��
			InsertNode(currA->data, result);
			//������һλ
			currA = currA->next;
			currB = currB->next;
		}
		else{
			printf("WARNING: NO ELE IN \n");
		}
		
	}
	
	return result;
}

//�ͷ�����
int FreeList(LinerList * list) {
	//������
	if (list == NULL) {
		return LL_LIST_ISNULL;
	}
	//���ͷ����нڵ�
	for (LinerListNode* curr = list->head; curr != NULL;) {
		//��ֹfree���գ������м�ָ�����ͷ�ָ����ַ���ڴ�
		LinerListNode* tem = curr;
		curr = curr->next;//��ǰ��curr����
		free(tem);//�ͷ�֮ǰ��¼�Ľڵ㣬�����Ͳ���Ӱ��ѭ������currָ��
		tem == NULL;//���ϰ�ߣ�free����ָ���ÿ�
	}
	//���нڵ��ͷ���ϣ��ͷ�����
	free(list);
	list == NULL;
	
	return SUCCESS;
}

//��ӡ����
int PrintList(LinerList * list) {
	if (list == NULL) {
		return LL_LIST_ISNULL;
	}
	printf("\n---------- Print List ----------\n");
	printf("info: len:%d  ", list->len);
	if (list->head != NULL) {
		printf("Head:%d  ", list->head->data);
	}
	if (list->tail != NULL) {
		printf("Tail:%d", list->tail->data);
	}
	printf("\n");
	//ѭ����ӡ
	for (LinerListNode* curr = list->head; curr != NULL; curr = curr->next) {
		printf("data: %d\n", curr->data);
	}
	printf("---------- Print Success ----------\n\n");
}

/* ---------- �����б� ---------- */

//��������������ȫ��Ϊ��̬����
static int Drive_LL1();
static int Drive_LL2();
static int Drive_LL3();
static int Drive_LL4();
static int Drive_LL7();
static int Drive_LL8();
static int Drive_LL11();
static int Drive_LL13();

//��������
int Drive_LL() {
	//TODO ��ϸ������ɹ��ĵط����Ƿ���Բο�ʹ��golang�еķ�������������ƵĴ���
	//�˴�Ϊ�˷��㣬ֱ��ʹ��exit��������˷���ֵ�ڴ˴�������Բ���Ҫ
	//�պ���ʱ�������Ż���ģ��
	Drive_LL1();
	Drive_LL2();
	Drive_LL3();
	Drive_LL4();
	Drive_LL7();
	Drive_LL8();
	Drive_LL11();
	Drive_LL13();

	return SUCCESS;
}

//1.�������в���һ��Ԫ��
int Drive_LL1() {
	LinerList * list = InitLinerList();
	if (list == NULL) {
		return SYS_MEM_OVERFLOW;
	}
	//����
	InsertNode(5, list);
	//��ӡ��������Debug
	//PrintList(list);
	//���
	if (list->len != 1 || list->head->data != 5 || list->tail->data != 5) {
		exit(LL_DRIVE_FAIL);
	}
	//printf("\n***** Drive_LL1 success *****\n");

	FreeList(list);
	list == NULL;
	return SUCCESS;
}
//2.һ��Ԫ��ʱ����ǰ��
int Drive_LL2() {
	LinerList * list = InitLinerList();
	if (list == NULL) {
		return SYS_MEM_OVERFLOW;
	}
	InsertNode(5,list);
	InsertNode(3,list);

	//PrintList(list);

	FreeList(list);
	list == NULL;
	return SUCCESS;
}
//3.һ��Ԫ��ʱ�������
int Drive_LL3() {
	LinerList * list = InitLinerList();
	if (list == NULL) {
		return SYS_MEM_OVERFLOW;
	}
	InsertNode(5, list);
	InsertNode(8, list);

	//PrintList(list);

	FreeList(list);
	list == NULL;
	return SUCCESS;
}
//4.���Ԫ��ʱ����ͷǰ�壬��ͷ��壬���м��
int Drive_LL4() {
	LinerList * list = InitLinerList();
	if (list == NULL) {
		return SYS_MEM_OVERFLOW;
	}

	InsertNode(5, list);
	InsertNode(8, list);

	//InsertNode(2, list);
	//PrintList(list);

	//InsertNode(10, list);
	//PrintList(list);

	//InsertNode(3, list);
	//PrintList(list);

	//InsertNode(3, list);
	//PrintList(list);

	//InsertNode(9, list);
	//PrintList(list);

	FreeList(list);
	list == NULL;
	return SUCCESS;
}
//7.�������ڵı���
int Drive_LL7() {
	LinerList * list = NULL;

	int result = InsertNode(5, list);
	//if (result == LL_LIST_ISNULL) {
	//	printf("list is NULL;\n");
	//}

	return SUCCESS;
}
//8.ɾ��һ�������ڵ�Ԫ��
int Drive_LL8() {
	LinerList * list = InitLinerList();
	if (list == NULL) {
		return SYS_MEM_OVERFLOW;
	}

	//InsertNode(10, list);
	//InsertNode(20, list);
	//InsertNode(30, list);
	//InsertNode(40, list);

	//int res = DeleteNode(15, list);
	//if (res == LL_NODE_NOTEXIST) {
	//	printf("NODE NOT EXIST 15.\n");
	//}

	////9.ɾ��ͷ�ڵ㣬֮������ǰ�壬�������
	//DeleteNode(10, list);
	//PrintList(list);

	//InsertNode(21, list);
	//PrintList(list);
	//InsertNode(19, list);
	//PrintList(list);
	//InsertNode(10, list);
	//PrintList(list);

	////10.ɾ��β�ڵ㣬֮������ǰ�壬�������
	//DeleteNode(40, list);
	//PrintList(list);

	//InsertNode(29, list);
	//PrintList(list);
	//InsertNode(31, list);
	//PrintList(list);
	//InsertNode(32, list);
	//PrintList(list);

	FreeList(list);
	list == NULL;

	return SUCCESS;
}

//11.ɾ��ֻ��һ��Ԫ��ʱ���ٲ���һ��Ԫ��
int Drive_LL11() {
	LinerList * list = InitLinerList();
	if (list == NULL) {
		return SYS_MEM_OVERFLOW;
	}

	//InsertNode(10, list);
	//PrintList(list);

	//DeleteNode(10, list);
	//PrintList(list);

	//InsertNode(30, list);
	//PrintList(list);

	//InsertNode(35, list);
	//PrintList(list);

	////12.ɾ���м�ڵ㣬�����м�ڵ�ǰ������Ԫ���ϣ�����ǰ�����
	//InsertNode(20, list);
	//InsertNode(40, list);
	//DeleteNode(35, list);
	//PrintList(list);

	//InsertNode(34, list);
	//InsertNode(36, list);
	//PrintList(list);

	FreeList(list);
	list == NULL;

	return SUCCESS;
}

//�ϲ�����
int Drive_LL13() {
	LinerList * listA = InitLinerList();
	if (listA == NULL) {
		return SYS_MEM_OVERFLOW;
	}

	InsertNode(10, listA);
	InsertNode(20, listA);
	InsertNode(30, listA);
	InsertNode(31, listA);
	InsertNode(32, listA);
	InsertNode(33, listA);
	InsertNode(50, listA);
	InsertNode(80, listA);
	//PrintList(listA);

	LinerList * listB = InitLinerList();
	if (listB == NULL) {
		return SYS_MEM_OVERFLOW;
	}

	InsertNode(11, listB);
	InsertNode(21, listB);
	InsertNode(40, listB);
	InsertNode(41, listB);
	InsertNode(42, listB);
	InsertNode(43, listB);
	InsertNode(51, listB);
	InsertNode(100, listB);
	InsertNode(101, listB);
	InsertNode(105, listB);
	//PrintList(listB);

	//�ϲ�����
	LinerList * listC = MergeList(listA, listB);
	if (listC != NULL) {
		//PrintList(listC);
	}

	return SUCCESS;
}