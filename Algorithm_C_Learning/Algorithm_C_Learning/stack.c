/*栈练习
采用顺序栈
同时练习C语法中的UNION的用法，减少代码重复率
*/

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "ErrCode.h"

/*
开发过程中查阅了书本上未提及的新函数
***** realloc ***** 函数说明如下：
入参：（当前指针，新分配后的大小）   返回：新指针
1）如果当前内存段后面有需要的内存空间，则直接扩展这段内存空间，realloc()将返回原指针。
2）如果当前内存段后面的空闲字节不够，那么就使用堆中的第一个能够满足这一要求的内存块，
将目前的数据复制到新的位置，并将原来的数据块释放掉，返回新的内存块位置。
3）如果申请失败，将返回NULL，此时，原来的指针仍然有效。

注意：如果调用成功，不管当前内存段后面的空闲空间是否满足要求，都会释放掉原来的指针，重新返回一个指针，
虽然返回的指针有可能和原来的指针一样。因此没必要再次释放掉原来的指针。

ctrl + F 检索可以查看我认为的realloc的标准用法
*/

//初始化栈
myStack* initMyStack() {
	//为栈结构申请空间
	myStack* result = (myStack*)malloc(sizeof(myStack));
	if (result == NULL) {
		return NULL;
	}
	//初始化
	result->base = (myStackDataField *)malloc(sizeof(myStackDataField) * MYSTACK_INIT_LEN);
	//检查是否分配成功
	if (result->base == NULL) {
		//若数据域分配失败
		//释放之前已经分配的栈结构
		free(result);
		result == NULL;

		return NULL;
	}
	//初始化TOP指针
	result->top = result->base;
	//记录当前已分配长度
	result->size = MYSTACK_INIT_LEN;

	return result;
}

//回收栈
int freeMyStack(myStack* stack) {
	//检查入参
	if (stack == NULL) {
		return MS_STACK_ISNULL;
	}
	//首先将 top 置空
	stack->top = NULL;
	//回收数据域
	free(stack->base);
	stack->base = NULL;

	//回收栈结构
	free(stack);
	stack = NULL;

	return SUCCESS;
}

//插入数据
int pushToMyStack(myStackDataField* data, myStack* stack) {
	//检查入参
	if (stack == NULL) {
		return MS_STACK_ISNULL;
	}
	if (data == NULL) {
		return MS_DATAISNULL;
	}
	//检查大小
	if (stack->top - stack->base >= MYSTACK_MAX_LEN) {
		return MS_DATA_MAX_LEN;
	}
	if (stack->top - stack->base >= stack->size) {
		//DEBUG
		printf("now stack is overflow. \n");
		//重分配空间
		myStackDataField * tem = (myStackDataField *)realloc(stack->base, stack->size + MYSTACK_INCREMENT);
		//分配失败
		if (tem == NULL) {
			//原地址不变
			return SYS_MEM_OVERFLOW;
		}
		//分配成功
		stack->base = tem;
		stack->top = stack->base + stack->size -1;
	}
	//插入数据
	*stack->top = *data; //不能赋地址，不然变成离散数据，内存由外面管理
	stack->top++;

	return SUCCESS;
}

//拿出数据，取头部数据
int popFromStack(myStack* stack, myStackDataField* result) {
	//检查入参
	if (stack == NULL) {
		return MS_STACK_ISNULL;
	}
	//确认栈不为空
	if (stack->base == stack->top) {
		return MS_STACK_DATA_ISNULL;
	}
	//拿出头顶数据，同时TOP指针下移
	*result = *stack->top;
	stack->top--;

	return SUCCESS;
}

//清空栈
int ClearStack(myStack* stack) {
	//检查入参
	if (stack == NULL) {
		return MS_STACK_ISNULL;
	}
	//将头指向base即可
	stack->top = stack->base;

	return SUCCESS;
}

//栈长度
int StackLength(myStack* stack) {
	return stack->top - stack->base;
}

//遍历栈
int VisitStack(myStack* stack, int visit(myStackDataField*)) {
	if (stack == NULL) {
		return MS_STACK_ISNULL;
	}
	printf("----- print stack -----\n");
	printf("info: size:%d len:%d\n", stack->size, StackLength(stack));
	//新建一个访问指针
	for (myStackDataField* visitPtr = stack->base; visitPtr != stack->top; visitPtr++) {
		visit(visitPtr);
	}
	printf("----- end of printing -----\n");
	return SUCCESS;
}

//浏览
int VisitStackData(myStackDataField* ptr) {
	//根据用户自定义的，这里就默认打印int了
	printf("%d\n",ptr->intData);
	return SUCCESS;
}

/* ---------- 驱动列表 ---------- */
static int Drive_MS1();

//
int Drive_MS1(){
	//生成栈
	myStack* testStack = initMyStack();
	if (testStack == NULL) {
		return SYS_MEM_OVERFLOW;
	}
	//打印
	VisitStack(testStack,VisitStackData);

	//销毁
	freeMyStack(testStack);
	testStack = NULL;

	return SUCCESS;
}

//驱动测试
int Drive_MS() {
	Drive_MS1();

	return SUCCESS;
}