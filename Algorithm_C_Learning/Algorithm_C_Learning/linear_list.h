/*���Ա���ϰ
����˳���һ��Ϊ���飬���ﲻ����ϰ
��Ҫ��ϰ����Ļ�������
*/
#pragma once

#define LINER_LIST_MAXLEN 1024 //������󳤶�

//����ڵ㣬˫������
//���������ظ��ڵ�
typedef struct {
	int data;	//�����в���һ���������������Ҳ�����ǽṹ�壬����Ĭ�ϴ�С��������
	struct LinerListNode *next;
	struct LinerListNode *pre;
} LinerListNode;

//����
typedef struct  {
	int len;//������
	LinerListNode *head;
	LinerListNode *tail;
} LinerList;

/* ---------- �����б� ---------- */
//��������˵�������º�������ֵint��������Ƿ�ɹ�
//�ɹ�����0�����㷵��ֵ�ο�"ErrCode.h"�еĺ궨��

//��ʼ������
//ͷ�ڵ�Ϊ�գ�����Ϊ0
//��ʼ���ɹ�������������ĵ�ַ�����ɹ����ؿ�ָ��
LinerList * InitLinerList();

//����ڵ�
//�Զ�����С�����˳�����
//��Σ�����ڵ�������򣬶�Ӧ����
int InsertNode(int,LinerList *);

//ɾ���ڵ�
//��Σ�ɾ���ڵ�������򣬶�Ӧ����
int DeleteNode(int, LinerList *);

//Ѱ�ҽڵ�
//��Σ���Ѱ�������򣬶�Ӧ�������أ���Ӧ�ڵ㣬��û�ҵ��򷵻�NULL
LinerListNode * FindNode(int, LinerList *);

//�ϲ�����
//��Σ����ϲ��������������أ��ϲ��������
//����������Ϊ�գ��򷵻���һ������
LinerList * MergeList(LinerList *,LinerList *);

//�ͷ�����
//��Σ���Ҫ�ͷŵ�����
int FreeList(LinerList *);

//��ӡ����
//��Σ�����ӡ����
int PrintList(LinerList *);

//��������
int Drive_LL();
