#include "mainwindow.h"
#include "ui_mainwindow.h"
template<class O, class V>
int Value(O& o, V v)
{
    o = v;
    return sizeof(O);
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    style();
    udpSocket=new QUdpSocket(this);
    udpSocket->bind(port);

//    unsigned int hRealStream = TMCC_Init( TMCC_INITTYPE_REALSTREAM );QLabel{border:10px groove #999999;}
//    TMCC_SetAutoReConnect(hRealStream, true);
//    tmPlayRealStreamCfg_t stuRealStream;
//    memset(&stuRealStream, 0, sizeof(tmPlayRealStreamCfg_t));
//    stuRealStream.dwSize = sizeof(tmPlayRealStreamCfg_t);
//    sprintf(stuRealStream.szAddress, "192.168.1.4");
//    sprintf(stuRealStream.szUser, "system");
//    sprintf(stuRealStream.szPass, "system");
//    stuRealStream.iPort = 6002;
//    stuRealStream.byChannel = 0;		// NVR等设备会有多通道，通道编号从0开始
//    stuRealStream.byStream = 0;		// 码流号，0为主码流，1为从码流，2为第三码流，依次类推		stuRealStream.byForceDecode = 0;	// byForceDecode=1表示强制解码
//    stuRealStream.byConnectType = 0;	// 连接类型，设备会根据这个标记启用对应的传输协议		stuRealStream.byMultiStream = 0;	// 此值有效忽略byStream，同时取得多码流数据，用于连接鱼眼全景设备
//    if( 1  !=  TMCC_ConnectStream( hRealStream, &stuRealStream, NULL ) )
//    {
//            //连接视频失败....
//        }


}




MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_track_clicked()     //引导跟踪
{
    FLAG = 1;
    if(ui->lineEdit_3->text()==""||ui->lineEdit_4->text()==""||ui->lineEdit_5->text()=="")
        ui->textEdit->append("<font color=red>未设置引导值（水平角度：0~360度，垂直角度：0~90度）。</font>");
        else {
        QString i = ui->lineEdit_3->text();
        double a = i.toDouble();
        i = ui->lineEdit_4->text();
        double b = i.toDouble();
        i = ui->lineEdit_5->text();
        double c = i.toDouble();
        CProtocal(a,c,b);
    }

}

void MainWindow::on_pushButton_release_clicked()     //释放
{
    FLAG = 3;
    unsigned char num[]={0x88,0x89,0x80,0x8A,0x2A,0x23,0x00,0x00,0x38,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x90,0x3C,0xFE,0x0F,0x38,0x3C,0xFE,0x0F,0x01,0x0A,0x4F,0x00,0x03,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x90,0x3C,0xFE,0x0F,0x00,0x00,0x00,0x00,0x64,0xF6,0x4F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x07,0x00,0x00,0x89,0x80,0x8A,0x8B};
    udpSocket->writeDatagram(QByteArray(reinterpret_cast<char *>(num),sizeof(num)),QHostAddress(ip),port);
    ui->textEdit->append("<font color=white>成功释放跟踪！</font>");
}

void MainWindow::on_pushButton_uav_clicked()     //只跟踪无人机
{
    FLAG=3;
    unsigned char num[]={0x88,0x89,0x80,0x8A,0x2A,0x23,0x00,0x00,0x38,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x90,0x3C,0xFE,0x0F,0x38,0x3C,0xFE,0x0F,0x01,0x0A,0x4F,0x00,0x02,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x90,0x3C,0xFE,0x0F,0x00,0x00,0x00,0x00,0x64,0xF6,0x4F,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x79,0x07,0x00,0x00,0x89,0x80,0x8A,0x8B};
    udpSocket->writeDatagram(QByteArray(reinterpret_cast<char *>(num),sizeof(num)),QHostAddress(ip),port);
    ui->textEdit->append("<font color=white>正在自动扫描、跟踪无人机。</font>");

}
void MainWindow::on_pushButton_uav_2_clicked()     //初始化
{
    FLAG=3;
    unsigned char num[]={0x88,0x89,0x80,0x8A,0x2A,0x23,0x00,0x00,0x38,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x90,0x3C,0xFE,0x0F,0x38,0x3C,0xFE,0x0F,0x01,0x0A,0x4F,0x00,0x03,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x90,0x3C,0xFE,0x0F,0x00,0x00,0x00,0x00,0x64,0xF6,0x4F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x07,0x00,0x00,0x89,0x80,0x8A,0x8B};
    udpSocket->writeDatagram(QByteArray(reinterpret_cast<char *>(num),sizeof(num)),QHostAddress(ip),port);
    Sleep(1000);
    unsigned char num1[]={0x88,0x89,0x80,0x8A,0x2A,0x23,0x00,0x00,0x58,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x56,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x71,0x01,0x00,0x00,0x89,0x80,0x8A,0x8B};
    udpSocket->writeDatagram(QByteArray(reinterpret_cast<char *>(num1),sizeof(num1)),QHostAddress(ip),port);
    ui->textEdit->append("<font color=white>正在初始化，请稍等。</font>");
    Sleep(4000);
    unsigned char num2[] = {0x88,0x89,0x80,0x8A,0x2A,0x23,0x00,0x00,0x38,0x00,0x00,0x00,0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x44,0x00,0x00,0x00,0x89,0x80,0x8A,0x8B};
    udpSocket->writeDatagram(QByteArray(reinterpret_cast<char *>(num2),sizeof(num2)),QHostAddress(ip),port);
    Sleep(1000);
    ui->textEdit->append("<font color=white>初始化成功。</font>");
}


void MainWindow::Sleep(int time)     //系统休眠函数
{
    QTime Time = QTime::currentTime().addMSecs(time);
    while (QTime::currentTime() < Time)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}


void MainWindow::CProtocal(double a,double b,double c)//引导
{
    std::array<BYTE, 1024> buf;
    Text pro;
    pro.setDistance(a*1.0);
    pro.setVerAngle(b);
    pro.setHorAngle(c);
    int len = pro.construct(buf.data(), buf.max_size());
    if (len <= 0)
    {
        ui->textEdit->append("<font color=red>引导命令发送失败。</font>");
    }
    int ret = udpSocket->writeDatagram((const char*)buf.data(),len,QHostAddress(ip),port);
    qDebug()<<(const char*)buf.data();
    if (ret == len)
    {
        ui->textEdit->append("<font color=white>引导命令发送成功。</font>");
//        Sleep(6000);
        if(FLAG==1)
        {
            unsigned char num[]={0x88,0x89,0x80,0x8A,0x2A,0x23,0x00,0x00,0x38,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x90,0x3C,0xFE,0x0F,0x38,0x3C,0xFE,0x0F,0x01,0x0A,0x4F,0x00,0x02,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x90,0x3C,0xFE,0x0F,0x00,0x00,0x00,0x00,0x64,0xF6,0x4F,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x79,0x07,0x00,0x00,0x89,0x80,0x8A,0x8B};
            udpSocket->writeDatagram(QByteArray(reinterpret_cast<char *>(num),sizeof(num)),QHostAddress(ip),port);
            ui->textEdit->append("<font color=white>正在自动扫描、跟踪无人机。</font>");
        }
    }
    else
    {
        ui->textEdit->append("<font color=red>引导命令发送失败。</font>");
    }

}
int  Text::construct(BYTE* buff, int len)//信息内容赋值函数
{

    memset(reserved_, 0, sizeof(reserved_));//清零。
    Head H;
    H.setCmd(UAV_CTRL_PRO_CMD::UAV_CTRL_PRO_CMD_TARGET_ADDR);
    H.setAttachDataLen(protocal_head_len);
    BYTE* ptrBuf = NULL;
    int iDataLen = H.getData(ptrBuf);
    int proc_len = 0;
    proc_len += H.append(ptrBuf + proc_len, (BYTE*)&number_, sizeof(number_));
    proc_len += H.append(ptrBuf + proc_len, (BYTE*)&sys_number_, sizeof(sys_number_));
    proc_len += H.append(ptrBuf + proc_len, (BYTE*)&timestamp_, sizeof(timestamp_));
    proc_len += H.append(ptrBuf + proc_len, (BYTE*)&lng_, sizeof(lng_));
    proc_len += H.append(ptrBuf + proc_len, (BYTE*)&lat_, sizeof(lat_));
    proc_len += H.append(ptrBuf + proc_len, (BYTE*)&height_, sizeof(height_));
    proc_len += H.append(ptrBuf + proc_len, (BYTE*)&distance_, sizeof(distance_));
    proc_len += H.append(ptrBuf + proc_len, (BYTE*)&hor_angle_, sizeof(hor_angle_));
    proc_len += H.append(ptrBuf + proc_len, (BYTE*)&ver_angle_, sizeof(ver_angle_));
    proc_len += H.append(ptrBuf + proc_len, (BYTE*)reserved_, sizeof(reserved_));
    return H.construct(buff, len);
}

int Head::getData(BYTE*& buff)
{
    buff = data_.buff.data();
    return data_.data_len;
}
int Head::append(BYTE* buff, const BYTE* data, int len)
{
    assert((NULL != buff) && (NULL != data) && (len >= 0));
    memcpy(buff, data, len);
    return len;
}
int Head::construct(BYTE* buff, int len)//数据包赋值函数
{

    assert(NULL != buff);//条件返回错误，终止程序。

    packet_len_ = data_.data_len + 20;

    if (len < packet_len_ + 16)
    {
        //LOG_TRACE << "buffer too small.";
        return -1;
    }

    BYTE* lpBit = (BYTE*)&start_bit_; //给起始位赋值
    lpBit[0] = 0x88;
    lpBit[1] = 0x89;
    lpBit[2] = 0x80;
    lpBit[3] = 0x8A;

    lpBit = (BYTE*)&stop_bit_; //给终止位赋值
    lpBit[0] = 0x89;
    lpBit[1] = 0x80;
    lpBit[2] = 0x8A;
    lpBit[3] = 0x8B;
    pro_number_ = 9002;
    timestamp_ = 0;// GetTickCount64();

    int iDiff = 0;
    iDiff += Value(*(unsigned int*)(buff + iDiff), start_bit_);
    iDiff += Value(*(unsigned int*)(buff + iDiff), pro_number_);
    iDiff += Value(*(unsigned int*)(buff + iDiff), packet_len_);
    iDiff += Value(*(unsigned int*)(buff + iDiff), cmd_);
    iDiff += Value(*(unsigned long long*)(buff + iDiff), timestamp_);

    memcpy(buff+iDiff, data_.buff.data(), data_.data_len); //从data_.buff.data()赋值data_.data_len个字节到buff+iDiff
    iDiff += data_.data_len;
    iDiff += Value(*(unsigned int*)(buff + iDiff), message_index_);

    // 错误校验
    /*
    * 错误校验码采用校验和方法。
    * 协议体中从“包长度”到“信息序列号” （包括“包长度”、 “信息序列号”）这部分数据。
    */
    int verify = 0;
    for (int i = 8; i < iDiff; i++)
    {
        verify += buff[i];
    }
    verify_ = verify;

    iDiff += Value(*(unsigned int*)(buff + iDiff), verify_);
    iDiff += Value(*(unsigned int*)(buff + iDiff), stop_bit_);
    valid(true);
    return iDiff;
}

void MainWindow::on_pushButton_track_2_clicked()    //引导
{
    FLAG = 2;
    if(ui->lineEdit_3->text()==""||ui->lineEdit_4->text()==""||ui->lineEdit_5->text()=="")
        ui->textEdit->append("<font color=red>未设置引导值（水平角度：0~360度，垂直角度：0~90度）。</font>");
        else {
        QString i = ui->lineEdit_3->text();
        double a = i.toDouble();
        i = ui->lineEdit_4->text();
        double b = i.toDouble();
        i = ui->lineEdit_5->text();
        double c = i.toDouble();
        CProtocal(a,c,b);
    }
}



void MainWindow::on_pushButton_track_3_clicked()//自动搜索跟踪
{
    FLAG=4;
    while (1) {
        if(FLAG!=4)
            break;
        else
        {
            unsigned char num[]={0x88,0x89,0x80,0x8A,0x2A,0x23,0x00,0x00,0x38,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x90,0x3C,0x18,0x67,0x38,0x3C,0x18,0x67,0x01,0x0A,0xD5,0x00,0x01,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x90,0x3C,0x18,0x67,0x00,0x00,0x00,0x00,0x9C,0xFA,0xD5,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1A,0x07,0x00,0x00,0x89,0x80,0x8A,0x8B};
            udpSocket->writeDatagram(QByteArray(reinterpret_cast<char *>(num),sizeof(num)),QHostAddress(ip),port);
            ui->textEdit->append("<font color=white>正在自动扫描、跟踪无人机。</font>");
            Sleep(4000);
        }
    }
}

void MainWindow::on_pushButton_track_4_clicked()//仅搜索
{
    FLAG=5;
    while (1) {
        if(FLAG!=5)
            break;
        else
        {
            unsigned char num[]={0x88,0x89,0x80,0x8A,0x2A,0x23,0x00,0x00,0x38,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x90,0x3C,0x18,0x67,0x38,0x3C,0x18,0x67,0x01,0x0A,0xD5,0x00,0x04,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x90,0x3C,0x18,0x67,0x00,0x00,0x00,0x00,0x9C,0xFA,0xD5,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x07,0x00,0x00,0x89,0x80,0x8A,0x8B};
            udpSocket->writeDatagram(QByteArray(reinterpret_cast<char *>(num),sizeof(num)),QHostAddress(ip),port);
            ui->textEdit->append("<font color=white>正在搜索。</font>");
            Sleep(4000);
        }
    }
}

void MainWindow::style()     //样式
{
    setWindowIcon(QIcon(":/image/100.png"));
    setWindowTitle(tr("小型目标识别跟踪光电伺服云台控制系统"));
    this->setFixedSize( this->width (),this->height ());
    ui->pushButton_uav->setStyleSheet("QPushButton{border-image:url(:/image/10.png);border:8px;color:red;}"
                                      "QPushButton:hover{border-image:url(:/image/11.png);border:8px}"
                                      "QPushButton:pressed{border-image:url(:/image/11.png);border:8px;color:white;}");
    ui->pushButton_track->setStyleSheet("QPushButton{border-image:url(:/image/10.png);border:8px;color:red;}"
                                        "QPushButton:hover{border-image:url(:/image/11.png);border:8px}"
                                        "QPushButton:pressed{border-image:url(:/image/11.png);border:8px;color:white;}");
    ui->pushButton_uav_2->setStyleSheet("QPushButton{border-image:url(:/image/10.png);border:8px;color:red;}"
                                        "QPushButton:hover{border-image:url(:/image/11.png);border:8px}"
                                        "QPushButton:pressed{border-image:url(:/image/11.png);border:8px;color:white;}");
    ui->pushButton_release->setStyleSheet("QPushButton{border-image:url(:/image/10.png);border:8px;color:red;}"
                                          "QPushButton:hover{border-image:url(:/image/11.png);border:8px}"
                                          "QPushButton:pressed{border-image:url(:/image/11.png);border:8px;color:white;}");
    ui->pushButton_track_2->setStyleSheet("QPushButton{border-image:url(:/image/10.png);border:8px;color:red;}"
                                          "QPushButton:hover{border-image:url(:/image/11.png);border:8px}"
                                          "QPushButton:pressed{border-image:url(:/image/11.png);border:8px;color:white;}");
    ui->pushButton_track_3->setStyleSheet("QPushButton{border-image:url(:/image/10.png);border:8px;color:red;}"
                                          "QPushButton:hover{border-image:url(:/image/11.png);border:8px}"
                                          "QPushButton:pressed{border-image:url(:/image/11.png);border:8px;color:white;}");
    ui->pushButton_track_4->setStyleSheet("QPushButton{border-image:url(:/image/10.png);border:8px;color:red;}"
                                          "QPushButton:hover{border-image:url(:/image/11.png);border:8px}"
                                          "QPushButton:pressed{border-image:url(:/image/11.png);border:8px;color:white;}");
}


