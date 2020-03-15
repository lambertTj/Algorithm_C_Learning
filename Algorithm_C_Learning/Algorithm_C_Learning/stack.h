/*ջ��ϰ
����˳��ջ
ͬʱ��ϰC�﷨�е�UNION���÷������ٴ����ظ���
��ϰ����ָ�룬���ݺ�����ַ
*/

#pragma once

#define MYSTACK_INIT_LEN	5		//��ʼ��ջ��С
#define MYSTACK_INCREMENT	5		//�洢�ռ��������
#define MYSTACK_MAX_LEN		15		//���ջ��С

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
myStack* initMyStack();

//����ջ
//��Σ������յ�ջ��ַ
int freeMyStack(myStack*);

//��������
//��Σ�����������ݣ�ջ��ַ
int pushToMyStack(myStackDataField*, myStack*);

//�ó����ݣ����Ǵ�ջ���ó�����
//�����ڴ����ķ��㣬Ӧ������ͷ�Լ���ʼ�����Լ������ڴ�
//��˷�������Ҳʹ����Σ�����ͷ���и����ڴ����
//����˭������˭����
//��Σ�ջ��ַ�����ص�����
int popFromStack(myStack*, myStackDataField*);

//���ջ
//��Σ�����յ�ջ
int ClearStack(myStack*);

//ջ����
//��Σ��������ջ
int StackLength(myStack*);

//����ջ
int VisitStack(myStack*, int visit(myStackDataField*));

//��ʵvisit�������û��Զ��壬����ֻ��Ϊ����ϰ���͸ɴ�д��������
int VisitStackData(myStackDataField*);

/***** �������� *****/
int Drive_MS();