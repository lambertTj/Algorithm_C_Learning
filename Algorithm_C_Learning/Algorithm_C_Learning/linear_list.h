/*���Ա���ϰ
����˳���һ��Ϊ���飬���ﲻ����ϰ
��Ҫ��ϰ�����Ļ�������
*/
#pragma once

//�����ڵ㣬˫������
//�����������ظ��ڵ�
typedef struct {
	int data;	//�����в���һ���������������Ҳ�����ǽṹ�壬����Ĭ�ϴ�С��������
	struct LinerListNode *next;
	struct LinerListNode *pre;
} LinerListNode;

//����
typedef struct  {
	int len;//��������
	LinerListNode *head;
	LinerListNode *tail;
} LinerList;

/* ---------- �����б� ---------- */
//��������˵�������º�������ֵint���������Ƿ�ɹ�
//�ɹ�����0�����㷵��ֵ�ο�"ErrCode.h"�еĺ궨��

//��ʼ������
//ͷ�ڵ�Ϊ�գ�����Ϊ0
//��ʼ���ɹ��������������ĵ�ַ�����ɹ����ؿ�ָ��
LinerList * InitLinerList();

//����ڵ�
//�Զ�����С�����˳�����
//��Σ�����ڵ�������򣬶�Ӧ����
int InsertNode(int,LinerList *);

//ɾ���ڵ�
//��Σ�ɾ���ڵ�������򣬶�Ӧ����
int DeleteNode(int, LinerList *);

/* ---------- �����б� ---------- */

//TODO ��Ҫ���Ĳ���
/*
1.�������в���һ��Ԫ��
2.һ��Ԫ��ʱ����ǰ��
3.һ��Ԫ��ʱ�������
4.���Ԫ��ʱ����ͷǰ�壬��ͷ���
5.���Ԫ��ʱ����β��壬��βǰ��
6.���Ԫ��ʱ�����м��

*/