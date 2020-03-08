/*ջ��ϰ
����˳��ջ
ͬʱ��ϰC�﷨�е�UNION���÷������ٴ����ظ���
*/

#pragma once

#define MYSTACK_INIT_LEN	5		//��ʼ��ջ��С
#define MYSTACK_INCREMENT	5		//�洢�ռ��������
#define MYSTACK_MAX_LEN		15	//���ջ��С

//������
typedef union {
	int intData;
	char charData;
} myStackDataField;

typedef struct {
	myStackDataField* base;	//base�ڳ�ʼ��֮���ͣ����������ײ���
	myStackDataField* top;	//topָ����Զָ����䵫δʹ�õ��ڴ�
	int size;	//��ǰ�ѷ������󳤶�
} myStack;

/***** ջ���� *****/

//��ʼ��ջ
//ʧ�ܷ���NULL���ɹ������Ѿ�����
myStack * initMyStack();

//����ջ
//��Σ������յ�ջ��ַ
int freeMyStack(myStack *);

//��������
//��Σ�����������ݣ�ջ��ַ
int pushToMyStack(myStackDataField *, myStack *);