//获取用户动作返回相应动作的整形值
#include "common.h"
int get_motion(int tp)
    {
    int x,y,x1,x2,y1,y2;
    struct input_event buf;
    int flag;
    while(1)
    {
        read(tp,&buf,sizeof(buf));
        if(buf.type == EV_ABS)
        {
            if(buf.code == ABS_X)
                x = buf.value;
            if(buf.code == ABS_Y)
                y = buf.value;
        }
        if(buf.type == EV_KEY &&
                    buf.code == BTN_TOUCH &&
                    buf.value == 1)//按下瞬间
            {
                x1 = x;
                y1 = y;
                flag = 1;
            }
        if(buf.type == EV_KEY &&
                buf.code == BTN_TOUCH &&
                buf.value == 0&&flag == 1)//松开瞬间
            {
                x2 = x;
                y2 = y;
                flag = 2;
            }
            if(flag == 2)
                break;
    }
    int delta_x = x1-x2 > 0 ? x1-x2 : x2-x1;
    int delta_y = y1-y2 > 0 ? y1-y2 : y2-y1;

    if(x1 == 0 || x2 == 0)
        return -1;

    if(x1>x2 && delta_x > delta_y)
        return LEFT;
    else if(x2>x1 && delta_x > delta_y)
        return RIGHT;
    else if(y1>y2 && delta_y > delta_x)
        return UP;
    else if(y2>y1 && delta_y > delta_x)
        return DOWN;
    else
        return -1;
    }