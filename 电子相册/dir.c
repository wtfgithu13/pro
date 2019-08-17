//功能:打开指定目录,获得jpg文件个数,返回一个元素均为jpg文件名的数组
#include "common.h"
char **dir_for_jpg(char *dirname,int *size)
{
	DIR *dp = opendir(dirname);
    if(dp == NULL)
    {
        perror("opendir()");
        return NULL;
    }
    chdir(dirname);
    int i, n,j=0;
    struct dirent *ep;
    // 目录下有n个文件包括本目录.和上一级目录..
    for(n=0; (ep=readdir(dp)) && ep!=NULL; n++);
    // 将所有的图片名字存放在filename[]里面
	char **filename = calloc(n,sizeof(char *));
    // 重置目录指针，从头又读一遍目录项
    rewinddir(dp);
    for(i=0; i<n;i++)
    {
        ep = readdir(dp);
        if(strstr(ep->d_name, ".jpg") || strstr(ep->d_name, ".bmp")) //文件是jpg或bmp
        {
           filename[j++] = ep->d_name;
        } //filename里面jpb和bmp文件共有j个
    }
    *size = j;//得到所需文件的个数
    if(*size == 0)
    {
        printf("无(jpg/bmp)文件\n");
        return NULL;
    }
    return filename;
}