//定义错误输出
#pragma once

//注意点：宏定义会将整行做替换，只有注释会将其忽略
/*
典型错误 
#define LL_FAIL 101;
则在调用函数时：exit(LL_FAIL);
变为：exit(101;);
由于多了一个;语法错误导致编译不通过
*/

#define SUCCESS 0 //代表成功返回
#define SYS_MEM_OVERFLOW 1 //系统内存溢出，多代表malloc函数失败

/***** 错误码宏命名规范 *****/
/***** XX_XXXX XX代表模块缩写，XXXX简单描述错误类型，全部采用大写，使用_分隔  *****/

/*链表错误返回 100-199*/
//LL缩写代表 LinerList 线性表
#define LL_LIST_ISNULL		100	//链表为空
#define LL_NODE_EXIST		101	//节点重复
#define LL_NODE_UNINSERT	102	//节点未插入
#define LL_NODE_NOTEXIST	103	//节点不存在
#define LL_DRIVE_FAIL		104 //线性表驱动测试失败
#define LL_LEN_OVERFLOW		105 //线性表已达最大长度