#include "jstestwindow.h"
#include "ui_jstestwindow.h"
#include <pthread.h>//open a thread to read the Video

pthread_t pthread_joy;

void JSTestWindow::onTimerOut_cs(void)
{
    Actual_JoyStick_CrlData Actual_data;//used for UDP sending
    G29driver.ReadDate();
    Actual_data.Wheel = float((G29driver.StickData.Wheel-32768))/32768*180;
    Actual_data.Acc = G29driver.StickData.Acc;
    Actual_data.brake= G29driver.StickData.brake;
    Actual_data.clutch = G29driver.StickData.clutch;
    Actual_data.buttom_up = G29driver.StickData.buttom_up;
    Actual_data.buttom_down = G29driver.StickData.buttom_down;
    Actual_data.buttom_left = G29driver.StickData.buttom_left;
    Actual_data.buttom_right = G29driver.StickData.buttom_right;

    //Actual_data.shiftgears = G29driver.StickData.shiftgears;
    //show the button up is pressed
    if (G29driver.StickData.buttom_up == 1)
        ui->pushButton_UP->setChecked(1);
    else
        ui->pushButton_UP->setChecked(0);
    //show the button down is pressed
    if (G29driver.StickData.buttom_down == 1)
        ui->pushButton_DOWN->setChecked(1);
    else
        ui->pushButton_DOWN->setChecked(0);
    //show the button left is pressed
    if (G29driver.StickData.buttom_left == 1)
        ui->pushButton_LEFT->setChecked(1);
    else
        ui->pushButton_LEFT->setChecked(0);
    //show the button right is pressed
    if (G29driver.StickData.buttom_right == 1)
        ui->pushButton_RIGHT->setChecked(1);
    else
        ui->pushButton_RIGHT->setChecked(0);
    //null
    if(G29driver.StickData.shiftgears == 0x00)
    {
        ui->NULL_Gear->setChecked(1);//no respond
        Actual_data.shiftgears = 0;
    }
    else
        ui->NULL_Gear->setChecked(0);
    //straight forward
    if(G29driver.StickData.shiftgears == 0x04)
    {
        ui->Straightforward->setChecked(1);//forward
        Actual_data.shiftgears = 1;
    }
    else
        ui->Straightforward->setChecked(0);
     //backforward
    if(G29driver.StickData.shiftgears == 0x08)
    {
        ui->RETURNBackforward->setChecked(1);//return
        Actual_data.shiftgears = -1;
    }
    else
        ui->RETURNBackforward->setChecked(0);
    //end of if judge

    ui->WheelAngle->display(Actual_data.Wheel);
    ui->Acc->setValue(Actual_data.Acc);
    ui->Brake->setValue(Actual_data.brake);
    ui->Clutch->setValue(Actual_data.clutch);
    QByteArray temp;
    temp.resize(sizeof(Actual_JoyStick_CrlData));//fit the QByteArray to the struct size
    memcpy(temp.data(),&Actual_data,sizeof(Actual_JoyStick_CrlData));
    sender->writeDatagram(temp.data(),temp.size(),QHostAddress::Broadcast,6665);
}

JSTestWindow::JSTestWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JSTestWindow)
{//init the window plugin
    ui->setupUi(this);
    ui->WheelAngle->setDigitCount(4);//show 4 digit
    ui->WheelAngle->setSmallDecimalPoint(1);

    ui->Acc->setMinimum(0);
    ui->Acc->setMaximum(255);
    ui->Brake->setMinimum(0);
    ui->Brake->setMaximum(255);
    ui->Clutch->setMinimum(0);
    ui->Clutch->setMaximum(255);
}

JSTestWindow::~JSTestWindow()
{

    delete ui;
}

void JSTestWindow::on_Init_clicked()
{
    G29driver.Init();
    //control stick
    timer_cs = new QTimer();
    timer_cs->setInterval(5);


    ui->pushButton_UP->setCheckable(1);
    ui->pushButton_DOWN->setCheckable(1);
    ui->pushButton_LEFT->setCheckable(1);
    ui->pushButton_RIGHT->setCheckable(1);
    ui->Straightforward->setCheckable(1);
    ui->NULL_Gear->setCheckable(1);
    ui->RETURNBackforward->setCheckable(1);
    //Init the net
    sender = new QUdpSocket(this);//its port will be defined in use 6665(ctl)
    sender->bind(6665);
}

void JSTestWindow::on_Start_clicked()
{
    ui->Start->setCheckable(1);

    timer_cs->start();
    //input control signalfrom stick as timer
    connect(timer_cs, SIGNAL(timeout()), this, SLOT(onTimerOut_cs()));

    ImageReceiver = new QUdpSocket(this);
    ImageReceiver->bind(6666);//receive port number to be bound 6666(video)
    //video show as UDP get
    connect(ImageReceiver, SIGNAL(readyRead()),this, SLOT(onUDPOut_vs()));
}
void JSTestWindow::onUDPOut_vs(void)
{//transmit the QImage in 1/5 size
    QByteArray datagram;
    datagram.resize(ImageReceiver->pendingDatagramSize());
    ImageReceiver->readDatagram(datagram.data(),datagram.size());
    //make up all the partions
    PackageHeader *packageHead = (PackageHeader *)datagram.data();
    //expand the imageData
    imageData.resize(packageHead->uDataSize);
    if (packageHead->uDataPackageCurrIndex == num)
    {
        num++;
        size += packageHead->uTransPackageSize-packageHead->uTransPackageHdrSize;
        if (size > 1024*1000)
        {
            qDebug()<<"image too big";
            num = 1;
            size = 0;
            return;
        }
        if (packageHead->uDataPackageOffset > 1024*1000)
        {
            qDebug()<<"image too big";
            packageHead->uDataPackageOffset = 0;
            num = 1;
            size = 0;
            return;
        }
        //error
        memcpy(imageData.data()+packageHead->uDataPackageOffset, datagram.data()+packageHead->uTransPackageHdrSize,
               packageHead->uTransPackageSize-packageHead->uTransPackageHdrSize);
        if ((packageHead->uDataPackageNum == packageHead->uDataPackageCurrIndex)
                && (size == packageHead->uDataSize))
        {
            imageData.resize(packageHead->uDataSize);
            QImage image;
            image.loadFromData((uchar *)imageData.data(),imageData.length(),"JPG");
            displayVideo(image);
            memset(imageData.data(),0,imageData.size());//UdpUnpackData
            //imageData.clear();
            num = 1;
            size = 0;
        }
    }
    else
    {
        num = 1;
        size = 0;
        memset(imageData.data(),0,sizeof(imageData));//UdpUnpackData
    }

}
void JSTestWindow::displayVideo(QImage QImage_disp)
{
    ui->OpenCVlabel->clear();
    ui->OpenCVlabel->setPixmap(QPixmap::fromImage(QImage_disp));
    ui->OpenCVlabel->resize(ui->OpenCVlabel->pixmap()->size());
    ui->OpenCVlabel->show();//display
}
