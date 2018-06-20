#ifndef JSTESTWINDOW_H
#define JSTESTWINDOW_H

#include <QMainWindow>
#include "logitechg29.h"
#include <QTimer>// we will use timer later


using namespace std;


const int BUFFSIZE = 128;
const int QLEN = 10 ;
//for distribute the frame
struct PackageHeader
{
    //包头大小(sizeof(PackageHeader))
    unsigned int uTransPackageHdrSize;
    //当前包头的大小(sizeof(PackageHeader)+当前数据包长度)
    unsigned int uTransPackageSize;
    //数据的总大小
    unsigned int uDataSize;
    //数据被分成包的个数
    unsigned int uDataPackageNum;
    //数据包当前的帧号
    unsigned int uDataPackageCurrIndex;
    //数据包在整个数据中的偏移
    unsigned int uDataPackageOffset;
};

namespace Ui {
class JSTestWindow;
}

class JSTestWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit JSTestWindow(QWidget *parent = 0);
    void displayVideo(QImage Qimage);

    ~JSTestWindow();
     QUdpSocket *sender;//Udp send
     QUdpSocket *ImageReceiver;//UDP recv
     QByteArray imageData;
     int num = 1;
     uint size = 0;

private slots:
    void on_Init_clicked();
    void onTimerOut_cs();//timer to activ per T
    void onUDPOut_vs(void);//trigered by UDP data
    void on_Start_clicked();

private:
    Ui::JSTestWindow *ui;
    QTimer *timer_cs;//for control signal
    QTimer *timer_vs;//for video signal
    LogitechG29 G29driver;


};

#endif // JSTESTWINDOW_H
