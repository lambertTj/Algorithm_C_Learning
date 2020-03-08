/*栈练习
采用顺序栈
同时练习C语法中的UNION的用法，减少代码重复率
*/

#pragma once

#define MYSTACK_INIT_LEN	5		//初始化栈大小
#define MYSTACK_INCREMENT	5		//存储空间分配增量
#define MYSTACK_MAX_LEN		15	//最大栈大小

//数据域
typedef union {
	int intData;
	char charData;
} myStackDataField;

typedef struct {
	myStackDataField* base;	//base在初始化之后就停在数据域最底层上
	myStackDataField* top;	//top指针永远指向分配但未使用的内存
	int size;	//当前已分配的最大长度
} myStack;

/***** 栈操作 *****/

//初始化栈
//失败返回NULL，成功返回已经生成
myStack * initMyStack();

//回收栈
//入参：待回收的栈地址
int freeMyStack(myStack *);

//插入数据
//入参：待插入的数据，栈地址
int pushToMyStack(myStackDataField *, myStack *);