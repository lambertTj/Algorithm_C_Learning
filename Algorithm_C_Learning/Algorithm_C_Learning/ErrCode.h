//����������
#pragma once

//ע��㣺�궨��Ὣ�������滻��ֻ��ע�ͻὫ�����
/*
���ʹ��� 
#define LL_FAIL 101;
���ڵ��ú���ʱ��exit(LL_FAIL);
��Ϊ��exit(101;);
���ڶ���һ��;�﷨�����±��벻ͨ��
*/

#define SUCCESS 0 //����ɹ�����
#define SYS_MEM_OVERFLOW 1 //ϵͳ�ڴ�����������malloc����ʧ��

/***** ������������淶 *****/
/***** XX_XXXX XX����ģ����д��XXXX�������������ͣ�ȫ�����ô�д��ʹ��_�ָ�  *****/

/*������󷵻� 100-199*/
//LL��д���� LinerList ���Ա�
#define LL_LIST_ISNULL		100	//����Ϊ��
#define LL_NODE_EXIST		101	//�ڵ��ظ�
#define LL_NODE_UNINSERT	102	//�ڵ�δ����
#define LL_NODE_NOTEXIST	103	//�ڵ㲻����
#define LL_DRIVE_FAIL		104 //���Ա���������ʧ��
#define LL_LEN_OVERFLOW		105 //���Ա��Ѵ���󳤶�