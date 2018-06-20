#ifndef SOCKETUDP_H
#define SOCKETUDP_H

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


using namespace cv;
//待传输图像默认大小为 320*240，可修改
#define IMG_WIDTH 240   // 需传输图像的宽
#define IMG_HEIGHT  180 // 需传输图像的高
#define PACKAGE_NUM 1

//默认格式为CV_8UC1
#define BUFFER_SIZE IMG_WIDTH*IMG_HEIGHT/PACKAGE_NUM
//#define image_type CV_8UC3

struct sentbuf
{
    char buf[BUFFER_SIZE];
    int flag;
};

class SocketMatTransmissionClient
{
public:
    SocketMatTransmissionClient(void);
    ~SocketMatTransmissionClient(void);

private:
    int sockClient;
    struct sentbuf data;

public:

    // 打开socket连接
    // params : IP      服务器的ip地址
    //          PORT    传输端口
    // return : -1      连接失败
    //          1       连接成功
    int socketConnect(const char* IP, int PORT);


    // 传输图像
    // params : image 待传输图像
    // return : -1      传输失败
    //          1       传输成功
    int transmit(cv::Mat image);


    // 断开socket连接
    void socketDisconnect(void);
};

#endif // SOCKETUDP_H
