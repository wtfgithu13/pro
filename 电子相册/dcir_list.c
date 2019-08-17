//创建一条链表,返回头指针
#include "common.h"
//创建新节点
dcir_list new_node(char *filename,char *rgb_buffer)
{
    dcir_list p = calloc(1,sizeof(listnode));
    if(p == NULL)
        return NULL;
    p->filename= filename;
    p->rgb_buffer = rgb_buffer;
    p->next = p;
    p->prev = p;
	return p;
}
// 将new插入到以head为首的链表的尾部（即最后一个节点的后面）
dcir_list list_add_tail(dcir_list new, dcir_list head)
{
    if(head == NULL)
    {
        head = new;
        return head;
    }
    if(new == NULL)
            return NULL;
    head->prev->next = new;
    new->prev = head->prev;
    new->next = head;
    head->prev = new;
    return head;
}
// 初始化一条空链表,无头节点的
dcir_list init_list()
{
    dcir_list head = NULL;
    return head;
}