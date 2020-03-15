/*ջ��ϰ
����˳��ջ
ͬʱ��ϰC�﷨�е�UNION���÷������ٴ����ظ���
*/

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "ErrCode.h"

/*
���������в������鱾��δ�ἰ���º���
***** realloc ***** ����˵�����£�
��Σ�����ǰָ�룬�·����Ĵ�С��   ���أ���ָ��
1�������ǰ�ڴ�κ�������Ҫ���ڴ�ռ䣬��ֱ����չ����ڴ�ռ䣬realloc()������ԭָ�롣
2�������ǰ�ڴ�κ���Ŀ����ֽڲ�������ô��ʹ�ö��еĵ�һ���ܹ�������һҪ����ڴ�飬
��Ŀǰ�����ݸ��Ƶ��µ�λ�ã�����ԭ�������ݿ��ͷŵ��������µ��ڴ��λ�á�
3���������ʧ�ܣ�������NULL����ʱ��ԭ����ָ����Ȼ��Ч��

ע�⣺������óɹ������ܵ�ǰ�ڴ�κ���Ŀ��пռ��Ƿ�����Ҫ�󣬶����ͷŵ�ԭ����ָ�룬���·���һ��ָ�룬
��Ȼ���ص�ָ���п��ܺ�ԭ����ָ��һ�������û��Ҫ�ٴ��ͷŵ�ԭ����ָ�롣

ctrl + F �������Բ鿴����Ϊ��realloc�ı�׼�÷�
*/

//��ʼ��ջ
myStack* initMyStack() {
	//Ϊջ�ṹ����ռ�
	myStack* result = (myStack*)malloc(sizeof(myStack));
	if (result == NULL) {
		return NULL;
	}
	//��ʼ��
	result->base = (myStackDataField *)malloc(sizeof(myStackDataField) * MYSTACK_INIT_LEN);
	//����Ƿ����ɹ�
	if (result->base == NULL) {
		//�����������ʧ��
		//�ͷ�֮ǰ�Ѿ������ջ�ṹ
		free(result);
		result == NULL;

		return NULL;
	}
	//��ʼ��TOPָ��
	result->top = result->base;
	//��¼��ǰ�ѷ��䳤��
	result->size = MYSTACK_INIT_LEN;

	return result;
}

//����ջ
int freeMyStack(myStack* stack) {
	//������
	if (stack == NULL) {
		return MS_STACK_ISNULL;
	}
	//���Ƚ� top �ÿ�
	stack->top = NULL;
	//����������
	free(stack->base);
	stack->base = NULL;

	//����ջ�ṹ
	free(stack);
	stack = NULL;

	return SUCCESS;
}

//��������
int pushToMyStack(myStackDataField* data, myStack* stack) {
	//������
	if (stack == NULL) {
		return MS_STACK_ISNULL;
	}
	if (data == NULL) {
		return MS_DATAISNULL;
	}
	//����С
	if (stack->top - stack->base >= MYSTACK_MAX_LEN) {
		return MS_DATA_MAX_LEN;
	}
	if (stack->top - stack->base >= stack->size) {
		//DEBUG
		printf("now stack is overflow. \n");
		//�ط���ռ�
		myStackDataField * tem = (myStackDataField *)realloc(stack->base, stack->size + MYSTACK_INCREMENT);
		//����ʧ��
		if (tem == NULL) {
			//ԭ��ַ����
			return SYS_MEM_OVERFLOW;
		}
		//����ɹ�
		stack->base = tem;
		stack->top = stack->base + stack->size -1;
	}
	//��������
	*stack->top = *data; //���ܸ���ַ����Ȼ�����ɢ���ݣ��ڴ����������
	stack->top++;

	return SUCCESS;
}

//�ó����ݣ�ȡͷ������
int popFromStack(myStack* stack, myStackDataField* result) {
	//������
	if (stack == NULL) {
		return MS_STACK_ISNULL;
	}
	//ȷ��ջ��Ϊ��
	if (stack->base == stack->top) {
		return MS_STACK_DATA_ISNULL;
	}
	//�ó�ͷ�����ݣ�ͬʱTOPָ������
	*result = *stack->top;
	stack->top--;

	return SUCCESS;
}

//���ջ
int ClearStack(myStack* stack) {
	//������
	if (stack == NULL) {
		return MS_STACK_ISNULL;
	}
	//��ͷָ��base����
	stack->top = stack->base;

	return SUCCESS;
}

//ջ����
int StackLength(myStack* stack) {
	return stack->top - stack->base;
}

//����ջ
int VisitStack(myStack* stack, int visit(myStackDataField*)) {
	if (stack == NULL) {
		return MS_STACK_ISNULL;
	}
	printf("----- print stack -----\n");
	printf("info: size:%d len:%d\n", stack->size, StackLength(stack));
	//�½�һ������ָ��
	for (myStackDataField* visitPtr = stack->base; visitPtr != stack->top; visitPtr++) {
		visit(visitPtr);
	}
	printf("----- end of printing -----\n");
	return SUCCESS;
}

//���
int VisitStackData(myStackDataField* ptr) {
	//�����û��Զ���ģ������Ĭ�ϴ�ӡint��
	printf("%d\n",ptr->intData);
	return SUCCESS;
}

/* ---------- �����б� ---------- */
static int Drive_MS1();

//
int Drive_MS1(){
	//����ջ
	myStack* testStack = initMyStack();
	if (testStack == NULL) {
		return SYS_MEM_OVERFLOW;
	}
	//��ӡ
	VisitStack(testStack,VisitStackData);

	//����
	freeMyStack(testStack);
	testStack = NULL;

	return SUCCESS;
}

//��������
int Drive_MS() {
	Drive_MS1();

	return SUCCESS;
}