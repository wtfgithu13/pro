 #include "common.h"
//缩小n倍
char *small(char *rgb_buffer,int *w,int *h,int *b,int n)
{
	int img_line_size = (*w)*(*b);
	//缩小n倍
	(*w)/=n;
	(*h)/=n;
	int buffer_size = (*w)*(*h)*(*b);
	char *buffer = calloc(1,buffer_size);
	for(int j=0; j<(*h); j++)
	{
		for(int i=0; i<(*w); i++)
		{
			memcpy(buffer+j*img_line_size/n+3*i,rgb_buffer+j*img_line_size*n+3*i*n, 3);
		}
	}
	return buffer;
}