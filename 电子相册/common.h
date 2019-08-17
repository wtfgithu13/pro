#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <time.h>
#include <stdbool.h>

// 目录
#include <dirent.h>

// 触摸屏
#include <linux/input.h>

// 液晶屏
#include <sys/mman.h> // 映射内存
#include <linux/fb.h> // LCD设备操作结构体
//dl动态库
#include <dlfcn.h>
#include "jpeglib.h"
//定义节点
typedef struct node
{
    char *filename;
    char *rgb_buffer;
    struct node *next;
    struct node *prev;
    int w;
    int h;
    int b;
}listnode, *dcir_list;

char **dir_for_jpg(char *dirname,int *size);
char *get_jpg_rgb(char *jpgname,int *w,int *h,int *b);
char* get_bmp_rgb(char *bmpname,int *w,int *h,int *b);
dcir_list new_node(char *filename,char *rgb_buffer);
dcir_list list_add_tail(dcir_list new, dcir_list head);
dcir_list init_list();
int get_motion(int tp);
void display(dcir_list head,int lcd);
char *small(char *rgb_buffer,int *w,int *h,int *b,int n);
char *big(char *rgb_buffer,int *w,int *h,int *b,int n);

enum motion{LEFT, RIGHT, UP, DOWN};

#endif
