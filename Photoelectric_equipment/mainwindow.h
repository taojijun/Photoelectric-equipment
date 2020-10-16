#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define BYTE unsigned char
#include <QMainWindow>
#include <QUdpSocket>
#include <QTime>
//#include <QMoveEvent>
//#define TMCC_INITTYPE_CONTROL			0x00		// 初始化成设备控制SDK句柄
//#define TMCC_INITTYPE_ENUM				0x01		// 初始化成枚举SDK句柄
//#define TMCC_INITTYPE_UPGRADE			0x02		// 初始化成升级SDK句柄
//#define TMCC_INITTYPE_TALK				0x03		// 初始化成语音对讲SDK句柄
//#define TMCC_INITTYPE_STREAM			0x04		// 初始化成播放数据流SDK句柄
//#define TMCC_INITTYPE_REALSTREAM		0x05		// 初始化成播放实时数据流SDK句柄
//#define TMCC_INITTYPE_LISTEN			0x06		// 状态接收和报警接收SDK句柄
//#define TMCC_INITTYPE_VIDEORENDER		0x07		// 初始化为视频显示SDK句柄
//#define TMCC_INITTYPE_VOICERENDER		0x08		// 初始化为语音对讲数据解码SDK句柄
//#define TMCC_INITTYPE_LISTENDEVICE		0x09		// 初始化为主动监听设备上传SDK句柄
//#define TMCC_INITTYPE_AVDECODER		0x0A		// 初始化为音视频解码SDK句柄
//#define TMCC_INITTYPE_PLAYREMOTEFILE 	0x0B		// 播放远程文件句柄(通过回调读取数据)
//#define TMCC_INITTYPE_MASK				0xFF		// 初始化为SDK句柄掩码
//#ifdef _LIB
//    #define TMCC_API
//    #define TMCC_CALL
//#else
//    #ifdef WIN32
//        #define TMCC_API	extern "C" __declspec(dllexport)
//        #define TMCC_CALL	__cdecl//__stdcall//
//    #else
//        #define TMCC_API	extern "C"
//        #define TMCC_CALL
//    #endif //WIN32
//#endif //_LIB
//#ifdef __cplusplus
//typedef struct tmPlayRealStreamCfg_t
//{
//    unsigned int			dwSize;
//    char					szAddress[32];		/*连接服务器的IP地址*/
//    char					szTurnAddress[32];	/*转发器地址*/
//    int						iPort;				/*服务器连接的端口*/
//    char					szUser[32];			/*登录用户名*/
//    char					szPass[32];			/*登录用户口令*/
//    unsigned char			byChannel;			/*通道*/
//    unsigned char			byStream;			/*码流号*/
//    unsigned char			byTranstType;		/*传输类型*/
//    unsigned char			byReConnectNum;		/*从连次数	*/
//    int						iTranstPackSize;	/*传输包大小*/
//    int						iReConnectTime;		/*重连的时间间隔*/
//    unsigned char			byTransProtocol;	/*传输协议0-内部自定,1-SONY,2-RTSP	*/
//    unsigned char			byForceDecode;		/*当现实窗口为空时是否需要强制解码输出*/
//    unsigned char			byDecoderType;		/*解码方式*/
//    unsigned char			byConnectType;		/*连接类型0-TcpIp,1-Udp,2-Dialing,3-TcpMulti,4-UdpMulti*/
//    char					szParameter[128];	/*连接参数*/
//    unsigned char			byMultiStream;		/*多码流列表，第一位标示第1码流，第二位标示第2码流...*/
//    unsigned char			byTemp[3];
//}tmPlayRealStreamCfg_t;
//extern "C" {
//#endif
//TMCC_API int TMCC_CALL TMCC_SetAutoReConnect( unsigned int hTmCC, bool bAutoConnect );
//TMCC_API int TMCC_CALL TMCC_ConnectStream( unsigned int hClient, tmPlayRealStreamCfg_t* pPlayInfo, HWND hPlayWnd );
//TMCC_API unsigned int TMCC_CALL TMCC_Init( unsigned int dwFlags );
//}

enum UAV_CTRL_PRO_CMD
{
    UAV_CTRL_PRO_CMD_NONE = 0,
    // 光电设备状态信息包
    UAV_CTRL_PRO_CMD_STATUS = 0x01,
    // 光电设备方位、俯仰信息包
    UAV_CTRL_PRO_CMD_POSITION = 0x02,
    // 设置光电目址信息包
    UAV_CTRL_PRO_CMD_TARGET_ADDR = 0x03,
    // 设置光电搜索跟踪信息包
    UAV_CTRL_PRO_CMD_TRACK = 0x04,
    // 光电转发干扰查询
    UAV_CTRL_PRO_CMD_INTERFERE_QUERY = 0x05,
    // 光电转发干扰控制
    UAV_CTRL_PRO_CMD_INTERFERE_CTRL = 0x06,
    // 光电转发干扰状态
    UAV_CTRL_PRO_CMD_INTERFERE_STATUS = 0x07,
    // 光电设备状态扩展信息包
    UAV_CTRL_PRO_CMD_STATUS_EXTEND = 0x08,
    // 光电镜头控制信息包
    UAV_CTRL_PRO_CMD_CAMERA_LENS = 0x09,
};
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString ip = "192.168.1.4";
    int port = 9966;
    int FLAG;
    QUdpSocket *udpSocket;
    void read();
    void Sleep(int);
    void CProtocal(double,double,double);
    void style();

private slots:
    void on_pushButton_track_clicked();

    void on_pushButton_release_clicked();

    void on_pushButton_uav_clicked();

    void on_pushButton_track_2_clicked();

    void on_pushButton_uav_2_clicked();

    void on_pushButton_track_3_clicked();

    void on_pushButton_track_4_clicked();

private:
    Ui::MainWindow *ui;
};

class Head
{
public:
    bool isValid();

    int getDataLen(){ return data_.data_len; }
    int getDataTotalLen();

    int getCmd(){ return cmd_; }
    void setCmd(int v){ cmd_ = v; }

    int parse(const BYTE* lpData, int len);
    int construct(BYTE* buff, int len);
public:
    void setAttachDataLen(int len) { data_.data_len = len; }
    int append(BYTE* buff, const BYTE* data, int len);

    int getData(BYTE*&);
    void valid(bool v) { valid_ = v; }

public:
    /**
    * @brief 协议头
    */
    // 起始位 1
    unsigned int start_bit_ =0;
    // 协议号 2
    unsigned int pro_number_ = 0;
    // 包长度 3
    // =命令字+时间戳+信息内容+信息序列号+错误校验
    unsigned int packet_len_ = 0;
    // 命令字 4
    unsigned int cmd_ = 0;
    // 时间戳 5
    unsigned long long timestamp_ = 0;
    // 信息内容
    struct
    {
        int data_len;
        std::array<BYTE,1024*8> buff;
    }data_;
    // 信息序列号 7
    // 第一条 1,每次累加
    unsigned int message_index_ = 0;
    // 错误校验 8
    unsigned int verify_ = 0;
    // 停止位
    unsigned int stop_bit_ = 0;

    bool valid_ =false;
};

class Text
{
public:



    bool isValid();
    int parse(const BYTE* lpData, int len);
    int construct(BYTE* buff, int len);

    unsigned int getNumber() { return number_; }
    unsigned int getSysNumber() { return sys_number_; }
    unsigned long long getTimestamp() { return timestamp_; }
    double getLng() { return lng_; }
    double getLat() { return lat_; }
    double getHeight() { return height_; }
    double getDistance() { return distance_; }
    double getHorAngle() { return hor_angle_; }
    double getVerAngle() { return ver_angle_; }

    void setNumber(int v){ number_ = v; }
    void setSysNumber(int v) { sys_number_ = v; }
    void setTimestamp(unsigned long long v) { timestamp_ = v; }
    void setLng(double v) { lng_ = v; }
    void setLat(double v){ lat_ = v; }
    void setHeight(double v){ height_ = v; }
    void setDistance(double v){ distance_ = v; }
    void setHorAngle(double v){ hor_angle_ = v; }
    void setVerAngle(double v){ ver_angle_ = v; }

public:
    // 光电编号 1
    unsigned int number_ =0;
    // 系统编号 2
    unsigned int sys_number_ = 0;
    // 系统下发 时间戳 3
    unsigned long long timestamp_ = 0;
    // 目标经度 4
    double lng_ = 0;
    // 目标纬度 5
    double lat_ = 0;
    // 目标高度 6
    double height_ = 0;
    // 目标距离 7
    double distance_ = 0;
    // 水平角度 7
    double hor_angle_ = 0;
    // 俯仰角度 8
    double ver_angle_ = 0;
    // 预留
    BYTE reserved_[4];
    const int protocal_head_len = 68;
};
#endif // MAINWINDOW_H

