 #include "common.h"
//放大n倍
char *big(char *rgb_buffer,int *w,int *h,int *b,int n)
{
int img_line_size = (*w)*(*b);
//放大n倍
(*w)*=n;
(*h)*=n;
int buffer_size = (*w)*(*h)*(*b);
char *buffer = calloc(1,buffer_size);
for(int j=0; j<(*h)/n; j++)
{
for(int m = 0;m<n;m++)
for(int i=0; i<(*w)/n; i++)
{
for(int k = 0;k<n;k++)
memcpy(buffer+(j*n+m)*(n*img_line_size)+3*i*n+3*k,rgb_buffer+j*img_line_size+3*i, 3);
}
} 
return buffer;
}
// char *big(char *rgb_buffer,int *w,int *h,int *b,int n)
// {
// int img_line_size = (*w)*(*b);
// //放大n倍
// (*h)*=n;
// int buffer_size = (*w)*(*h)*(*b);
// char *buffer = calloc(1,buffer_size);
// for(int j=0; j<(*h)/n; j++)
// {
// for(int m = 0;m<n;m++)
// for(int i=0; i<(*w); i++)
// {
// memcpy(buffer+(j*n+m)*(img_line_size)+3*i,rgb_buffer+j*img_line_size+3*i, 3);
// }
// } 
// return buffer;
// }