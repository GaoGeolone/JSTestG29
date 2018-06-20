#ifndef LOGITECHG29_H
#define LOGITECHG29_H


#define SUCESS  1
#define Fail   -1

#include "logitechg29_global.h"
struct JoyStick//only for series communication
{
    JoyStick() {}
    int Wheel;//wheel
    int Acc;//acc
    int brake;//brake
    int clutch;//seperation and reunion
    bool buttom_up;
    bool buttom_down;
    bool buttom_left;
    bool buttom_right;
    int  shiftgears;//0x00 mid  0x04forward 0x08 backward
};
struct Actual_JoyStick_CrlData//this data is used for controling
{
    Actual_JoyStick_CrlData() {}
    float Wheel;//wheel
    int Acc;//acc
    int brake;//brake
    int clutch;//seperation and reunion
    bool buttom_up;
    bool buttom_down;
    bool buttom_left;
    bool buttom_right;
    int shiftgears;//forward:1  Null: 0    backward:-1
};
class LOGITECHG29SHARED_EXPORT LogitechG29
{

public:
    //function
    LogitechG29();//we will init the G29 in this construct function
    int Init();
    ~LogitechG29(){hid_close(handle);}//close the IO file
    int ReadDate();//return < 0 fail read from G29 handle
    //data and struct
    JoyStick StickData;//use it to get the data from G29
    int res;
    unsigned char buf[256];
    #define MAX_STR 255
    wchar_t wstr[MAX_STR];
    hid_device *handle;
    int i;
    struct hid_device_info *devs, *cur_dev;

};

#endif // LOGITECHG29_H
