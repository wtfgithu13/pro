//功能:显示图片,参数为显示屏描述符,rgb_buffer
#include "common.h"
void display(dcir_list p,int lcd)
{
    char *filename = p->filename;
    int tu_h;
    int tu_w;
    int tu_b;
     int row_stride;
    if(strstr(filename,".jpg"))
    {
        if(p->rgb_buffer == NULL)
        {
            //p->rgb_buffer = get_jpg_rgb(filename,&tu_w,&tu_h,&tu_b);
            char *buffer = get_jpg_rgb(filename,&tu_w,&tu_h,&tu_b);
            printf("原图:\n");
            printf("w=%d\n",tu_w);
            printf("h=%d\n",tu_h);
            char *bbuf = big(buffer,&tu_w,&tu_h,&tu_b,3);
            printf("放大3倍后:\n");
            printf("w=%d\n",tu_w);
            printf("h=%d\n",tu_h);
            p->rgb_buffer = small(bbuf,&tu_w,&tu_h,&tu_b,2);

            p->w = tu_w;
            p->h = tu_h;
            p->b = tu_b;
            printf("再缩小2倍后:\n");
            printf("w=%d\n",tu_w);
            printf("h=%d\n",tu_h);
        }
        row_stride = (p->w)*(p->b);
    }
    if(strstr(filename,".bmp"))
    {
        if(p->rgb_buffer == NULL)
        {
            //p->rgb_buffer = get_bmp_rgb(filename,&tu_w,&tu_h,&tu_b);
            char *buffer = get_bmp_rgb(filename,&tu_w,&tu_h,&tu_b);
            p->rgb_buffer = big(buffer,&tu_w,&tu_h,&tu_b,2);
            p->w = tu_w;
            p->h = tu_h;
            p->b = tu_b;
        }
        row_stride = (p->w)*(p->b);
    }
    char *rgb_buffer = p->rgb_buffer;
	struct fb_var_screeninfo vsinfo;
	bzero(&vsinfo, sizeof(vsinfo));
	ioctl(lcd, FBIOGET_VSCREENINFO, &vsinfo); // 获取了LCD的硬件参数
    int lcd_w = vsinfo.xres;
    int lcd_h = vsinfo.yres;
    int lcd_bpp =  vsinfo.bits_per_pixel;
    int screen_size = lcd_w * lcd_h * lcd_bpp/8;
    char *lcdmem = mmap(NULL, screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, lcd, 0);
    bzero(lcdmem,screen_size);
    int red_offset  = vsinfo.red.offset;
    int green_offset= vsinfo.green.offset;
    int blue_offset = vsinfo.blue.offset;
    char *lcdtmp = lcdmem;
    char *rgbtmp = rgb_buffer;
    int w = lcd_w<p->w ? lcd_w : p->w;
    int h = lcd_h<p->h ? lcd_h : p->h;
    int x = lcd_w-p->w > 0 ? (lcd_w-p->w)/2 : 0;
    int y = lcd_h-p->h > 0 ? (lcd_h-p->h)/2 : 0;
    lcdtmp +=  (y*lcd_w+ x)*(lcd_bpp/8);
    // 将rgb数据妥善地放入lcdmem
    for(int j=0; j<h; j++)
    {
        for(int i=0; i<w; i++)
        {
            memcpy(lcdtmp + 4*i + red_offset/8,  rgbtmp + 3*i + 0, 1);
            memcpy(lcdtmp + 4*i + green_offset/8, rgbtmp + 3*i + 1, 1);
            memcpy(lcdtmp + 4*i + blue_offset/8,   rgbtmp + 3*i + 2, 1);
        }
        lcdtmp += (lcd_w*lcd_bpp/8); // lcd显存指针向下偏移一行
        rgbtmp += (row_stride); // rgb指针向下偏移一行
    }
}