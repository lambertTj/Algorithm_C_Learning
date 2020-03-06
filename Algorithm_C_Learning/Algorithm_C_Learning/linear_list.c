/*���Ա���ϰ
����˳���һ��Ϊ���飬���ﲻ����ϰ
��Ҫ��ϰ����Ļ�������
*/

#include "ErrCode.h"
#include "linear_list.h"
#include <stdlib.h>

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
	//���ɽ��
	LinerListNode * node = InitNode(data);
	if (node == NULL) {
		return SYS_MEM_OVERFLOW;
	}
	//���Ϊ����ĵ�һ���ڵ�
	if (List->head == NULL && List->tail == NULL) {
		List->head = node;
		List->tail = node;
		List->len++;
		return SUCCESS
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
	//��ʼ����������
	LinerList * result = InitLinerList();
	if (result == NULL) {
		return NULL;
	}
	//�ϲ�
	for (LinerListNode *currA = listA->head, *currB = listB->head; (currA != NULL) || (currB != NULL);) {
		//˭С��˭������һ�������ϵĽڵ��Ѳ�����
		if (currA->data < currB->data || currB == NULL) {
			//����A�ڵ�
			InsertNode(currA->data, result);
			//��һ��A
			currA = currA->next;
		}
		else if (currA->data > currB->data || currA == NULL) {
			//����B�ڵ�
			InsertNode(currB->data, result);
			//��һ��B
			currB = currB->next;
		}
		else if (currA->data == currB->data) {
			//һ����ֻ��һ��
			InsertNode(currA->data, result);
			//������һλ
			currA = currA->next;
			currB = currB->next;
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
	
	return SUCCESS
}