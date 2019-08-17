#include "common.h"

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        printf("Usage: %s <some dir includes *.jpg\n", argv[0]);
        exit(1);
    }
    int size = 0;
    char **filename = dir_for_jpg(argv[1],&size);
    // 1，初始化一条空链表
    dcir_list head = init_list();
    // 2，依次插入jpg的信息
    for(int i=0; i<size; i++)
    {
        // 新建一个节点new
        dcir_list new = new_node(filename[i],NULL);
        // 将新节点插入链表的末尾
        head = list_add_tail(new,head);
    }
    int lcd = open("/dev/fb0", O_RDWR);
    dcir_list p = head->next;
    display(p->next,lcd);
    int tp = open("/dev/input/event0",O_RDWR|O_NONBLOCK);
    while(1)
    {
        // 分析用户动作
        int m = get_motion(tp);
        
        // 根据用户动作，显示图片
        switch(m)
        {
        case LEFT:
            p = p->next;
            display(p,lcd);
            printf("左移\n");
            break;
        case RIGHT:
            p = p->prev;
            printf("右移\n");
            display(p,lcd);   
        }
    }
    //释放相应资源
    for(dcir_list p = head->next;p!=head;p=p->next)
        free(p);
    free(head);
}


