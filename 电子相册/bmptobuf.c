#include "common.h"
#include "bmp.h"

char* get_bmp_rgb(char *bmpname,int *w,int *h,int *b)
{
	// 0，分析BMP图片的头部信息，提取长宽深等信息
	int fd = open(bmpname, O_RDWR);
	if(fd==-1)
		perror("shibai");
	struct bitmap_header head;
	struct bitmap_info   info;
	bzero(&head, sizeof(head));
	bzero(&info, sizeof(info));
	read(fd, &head, sizeof(head));
	read(fd, &info, sizeof(info));
	*w = info.width; 
	*h = info.height;
	*b = info.bit_count/8; 
	// 1，读取BMP图片的具体图像数据（RGB）
	int rgb_size = head.size-sizeof(head)-sizeof(info);
	char *rgb = calloc(1, rgb_size);
	int n = 0;
	int total = 0;
	int val = rgb_size;
	// 确保将文件中的RGB数据读完
	while(val > 0)
	{
		n = read(fd, rgb+total, val);
		val -= n;
		total    += n;
	}//数据都在rgb中,包含空格
	int pad = (4-(info.width*3 % 4)) % 4; // pad = 0~3
	int img_line_size = info.width*3 + pad; // 图片一行的总字节数
	char *rgb_r = rgb + img_line_size*(info.height-1);
	int rgb_buf_size = rgb_size-pad*info.height;
	char *rgb_buffer= calloc(1,rgb_buf_size);
	char *tmp = rgb_buffer;
	int k=0;
	//5，妥善地将BMP中的RGB数据搬到rgb_buffer中
	for(int j=0; j<*h; j++)
	{
		for(int i=0; i<*w; i++)
		{
			memcpy(tmp+j*(img_line_size-pad)+3*i, (rgb_r-j*img_line_size)+3*i, 3);
		}
	}
	free(rgb);
	return rgb_buffer;
}
