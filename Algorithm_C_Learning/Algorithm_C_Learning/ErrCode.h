//定义错误输出
#pragma once

#define SUCCESS 0; //代表成功返回
#define SYS_MEM_OVERFLOW 1; //系统内存溢出，多代表malloc函数失败

/*链表错误返回 100-199*/
//LL缩写代表 LinerList 线性表
#define LL_ISNULL			100;	//链表为空
#define LL_NODE_EXIST		101;	//节点重复
#define LL_NODE_UNINSERT	102;	//节点未插入