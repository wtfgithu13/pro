
//功能:解码,返回一个rgb_buffer
#include "common.h"
#include "jpeglib.h"
//解压缩结构体
struct jpeg_decompress_struct cinfo;
int row_stride;
// 打开JPG图片并读取图像数据(这里打开的就是节点元素了)
char *get_jpg_rgb(char *jpgname,int *w,int *h,int *b)
{
	int jpgfd = open(jpgname, O_RDONLY);
    int jpg_size = lseek(jpgfd, 0L, SEEK_END);
    lseek(jpgfd, 0L, SEEK_SET);
    char *jpg_buffer = calloc(1, jpg_size);
    // 完整地读完了 a.jpg 文件的内容，妥妥地放到了 jpg_buffer 中
    int total = jpg_size;
    while(total > 0)
    {
        int n = read(jpgfd, jpg_buffer+(jpg_size-total), total);
        total -= n;
    }
    close(jpgfd);
    // JPG  ==>  RGB
    // 声明解压缩结构体，以及错误管理结构体
    
    struct jpeg_error_mgr jerr;
    // 使用缺省的出错处理来初始化解压缩结构体
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    // 配置该cinfo，使其从jpg_buffer中读取jpg_size个字节
    // 这些数据必须是完整的JPEG数据
    jpeg_mem_src(&cinfo, jpg_buffer, jpg_size);
    // 读取JPEG文件的头，并判断其格式是否合法
    int ret = jpeg_read_header(&cinfo, true);
    if(ret != 1)
    {
        fprintf(stderr, "[%d]: jpeg_read_header failed: "
            "%s\n", __LINE__, strerror(errno));
        exit(1);
    }
    // 开始解码
    jpeg_start_decompress(&cinfo);
    // cinfo中保存了图片文件的尺寸信息
    *w = cinfo.output_width; // 宽
    *h = cinfo.output_height; // 高
    *b = cinfo.output_components; // 深：每个像素点包含的字节数
    // 图片的每一行所包含的字节数
    row_stride = cinfo.output_width * cinfo.output_components;
    // 根据图片的尺寸大小，分配一块相应的内存rgb_buffer
    // 用来存放从jpg_buffer解压出来的图像数据
    unsigned char *rgb_buffer = calloc(1, row_stride*cinfo.output_height);
    // 循环地将图片的每一行读出并解压到rgb_buffer中
    int line = 0;
    while(cinfo.output_scanline < cinfo.output_height)
    {
        unsigned char *buffer_array[1];
        buffer_array[0] = rgb_buffer +
                (cinfo.output_scanline) * row_stride;
        jpeg_read_scanlines(&cinfo, buffer_array, 1);
    }
    // 解压完了，将jpeg相关的资源释放掉
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    free(jpg_buffer); 
    //现在我有了一个rgb_buffer,当然是要将这个rgb_buffer放入节点中
    return rgb_buffer;
}