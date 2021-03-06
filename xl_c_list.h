#ifndef XL_C_LIST_H
#define XL_C_LIST_H
#include <stdlib.h>
#include <stddef.h>

#define I_END NULL


//前向链表节点类型
typedef  struct _fs_node
{
	void *data;  //数据
	struct _fs_node* next;

}fs_node, *fs_pnode;


//前向链表类型
typedef struct _forward_list
{
	unsigned size;    //每个数据的大小
	unsigned n;       //节点数
	fs_pnode headPrev;//haed前面的节点
	fs_pnode head;    //首 
	fs_pnode tail;  //尾

}forward_list, *pforward_list;

//创建一个链表
pforward_list fs_create(size_t dsize);
//销毁一个链表
void fs_destroy(pforward_list fs);
//把数据data添加到node的后面
//iscpy 为真则使用data副本，否则使用data指向的数据
//返回新插入的数据的节点指针，失败返回END
fs_pnode  fs_insert_after(pforward_list fs,fs_pnode node,const void *data,int iscpy);
//把数据添加到头节点前面,返回新添加的数据的节点指针，失败返回END
fs_pnode  fs_push_front(pforward_list fs,const void *data, int iscpy);
//把数据添加到尾节点后面,返回新添加的数据的节点指针，失败返回END
fs_pnode  fs_push_back(pforward_list fs,const void *data, int iscpy);
//删除node节点前面的节点，返回被删除的节点的下一个节点指针
fs_pnode fs_erase_after(pforward_list fs, fs_pnode node,int isspl);

////////////////////////////////////////////////////////////////////



typedef char BOOL_;


/*链表节点结构*/
typedef struct _ls_node
{
	struct _ls_node *next;  //指向下一个节点
	struct _ls_node *back;  //指向上一个节点

	void  *data;  //数据
	size_t size;  //data长度
	BOOL_ isfree;   //是否需要释放内存
}ls_node, *ls_pnode;

/*数据头*/
typedef struct _dhead
{
	ls_pnode thisNode; //当前节点指针

}ls_dhead,*ls_pdhead;

/*链表结构*/
typedef struct _list
{
	ls_pnode first;  //链表头
	ls_pnode last;   //链表尾
	size_t  number;       //节点数

}list, *plist;



//清空链表
void list_clear(plist list);
//销毁链表
void list_destroy(plist list);

void list_insertp(plist list, ls_pnode ndPos, ls_pnode node, BOOL_ isFont);

//在指定节点前面或后面插入对象
ls_pnode list_insert(plist list, ls_pnode ndPos, void *obj, size_t size, BOOL_ isFree, BOOL_ isFont);
//在链表尾添加一个对象,对象将被复制到新的空间中
ls_pnode list_add_new(plist list, void *obj, size_t size);
//在链表尾添加一个对象,使用obj所指向的对象
ls_pnode list_add_old(plist list, void *obj);
//删除一个节点
void list_erase(plist list, ls_pnode node, BOOL_ isDesy);
//把链表ls2复制到ls1中
void list_copy(plist ls1, plist ls2);
//从data获取数据头
#define list_get_head(data) ((ls_pdhead)((char*)(data) - sizeof(ls_dhead)))
//从data获取节点的指针
#define list_get_node(data) (((ls_pdhead)((char*)(data) - sizeof(ls_dhead)))->thisNode)
#define list_first(ls) ((ls)->first)
#define list_last(ls) ((ls)->last)
#define list_size(ls) ((ls)->number)
#define list_offset_first (offsetof(list, first))
#define list_offset_last (offsetof(list, last))
#define list_offset_next (offsetof(ls_node, next))
#define list_offset_back (offsetof(ls_node, back))
#endif