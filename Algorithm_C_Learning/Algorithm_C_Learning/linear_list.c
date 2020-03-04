/*���Ա���ϰ
����˳���һ��Ϊ���飬���ﲻ����ϰ
��Ҫ��ϰ����Ļ�������
*/

#include "ErrCode.h"
#include "linear_list.h"
#include <stdlib.h>

/*****  ���ļ�ע�Ͳ����ں������̽��ͣ����庯���÷���ο���Ӧͷ�ļ��еĺ���˵��  *****/

/* �ڲ��������� */
//��static���Σ�Ϊ��̬������Ϊ���ļ�˽�У�ֻ���ں����������ļ�ʹ��
static LinerListNode * InitNode(int data);

/* �������� */

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
		return LL_ISNULL;
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
			return LL_NODE_EXIST;
		}
		//��ͷ�ڵ�ǰ��
		if ((curr == List->head) && (data < curr->data)) {
			node->next = curr;
			curr->pre = node;
			//ͷ�ڵ�ı�
			List->head = node;
			return SUCCESS;
		}
		//��β�ڵ���
		if ((curr == List->tail) && (data > curr->data)) {
			node->pre = curr;
			curr->next = node;
			//β�ڵ�ı�
			List->tail = node;
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
//��Σ�ɾ���ڵ�������򣬶�Ӧ����
//int DeleteNode(int, LinerList *);