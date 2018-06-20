#include "logitechg29.h"

#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


LogitechG29::LogitechG29()
{

}
int LogitechG29::Init()
{
    handle = hid_open(0x46d, 0xc24f, NULL);//thd add of the G29
    hid_set_nonblocking(handle, 1);//set to be nonblock mod
    if (!handle) {
        printf("unable to open device\n");
        return Fail;
    }
    else
    {
        printf("Success to open device\n");
        return SUCESS;
    }
}
int LogitechG29::ReadDate()
{
    res = hid_read(handle, buf, 12);//G29 only sent 12Bytes Bata and data will be stored in Buf
    if (res >= 0)
    {
        uchar * p1,*p2,*p3;
        p1=buf;
        p2=buf+4;
        p3=buf+8;
        StickData.Wheel = ((*(p1+4))+(*(p1+5)*0x100));//wheel
        StickData.Acc   = 255-*(p2+2);
        StickData.brake = 255-*(p2+3);
        StickData.clutch= 255-*(p3);// wait to be test latter
        StickData.buttom_up   = (((*p1)==0x00));
        StickData.buttom_down = (((*p1)==0x04));
        StickData.buttom_left = (((*p1)==0x06));
        StickData.buttom_right= (((*p1)==0x02));
        StickData.shiftgears = (((*(p1+2))&0xff));//add new function //0x00 mid  0x08forward 0x0f backward
        return SUCESS;
    }
    else
        return Fail;
}
