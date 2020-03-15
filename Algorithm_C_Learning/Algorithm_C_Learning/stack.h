/*栈练习
采用顺序栈
同时练习C语法中的UNION的用法，减少代码重复率
练习函数指针，传递函数地址
*/

#pragma once

#define MYSTACK_INIT_LEN	5		//初始化栈大小
#define MYSTACK_INCREMENT	5		//存储空间分配增量
#define MYSTACK_MAX_LEN		15		//最大栈大小

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
myStack* initMyStack();

//回收栈
//入参：待回收的栈地址
int freeMyStack(myStack*);

//插入数据
//入参：待插入的数据，栈地址
int pushToMyStack(myStackDataField*, myStack*);

//拿出数据，总是从栈顶拿出数据
//由于内存管理的方便，应该由外头自己初始化，自己销毁内存
//因此返回数据也使用入参，由外头自行负责内存管理
//即：谁创建，谁负责
//入参：栈地址，返回的数据
int popFromStack(myStack*, myStackDataField*);

//清空栈
//入参：待清空的栈
int ClearStack(myStack*);

//栈长度
//入参：待计算的栈
int StackLength(myStack*);

//遍历栈
int VisitStack(myStack*, int visit(myStackDataField*));

//其实visit可以由用户自定义，这里只是为了练习，就干脆写在这里了
int VisitStackData(myStackDataField*);

/***** 驱动测试 *****/
int Drive_MS();