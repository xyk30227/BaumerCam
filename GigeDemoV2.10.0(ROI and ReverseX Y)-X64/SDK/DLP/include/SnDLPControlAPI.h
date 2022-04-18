//---------------------------------------------------------------//
//-------------------2020.02.19张翔宇修改------------------------//
//新版1080光机控制与老版存在差异 部分函数出现了720与1080不通用的情况 请注意

#pragma once
#include <vector>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <mstcpip.h>

using namespace std;

#ifndef API_SNDLPCONTROL_H
#define API_SNDLPCONTROL_H

#ifdef API_SNDLPCONTROL_H
#define SN_DLPCONTROL_API __declspec(dllexport)
#else
#define SN_DLPCONTROL_API __declspec(dllimport)
#endif
/*
---------------------------------TestDemo--------------------
bool m_bNetDLP = false;//默认U口光机
if (!sn3DDLPdev::sn3DInitHidDev(m_HandleDlpDev))
{
m_HandleDlpDev = NULL;
//return false;
if (!snInitDLPDevices(m_SocketDev))
{
return false;
}
else
{
//fprintf(pTestFile, "Init Ok\n");
m_bNetDLP = true;
}
}

if (m_HandleDlpDev != NULL && !m_bNetDLP)
{   //2020-1-8张翔宇使用新版1080光机 与720完全不同的新控制逻辑
if (!sn3DDLPdev::sn3DOpenProject(m_HandleDlpDev))
{
return false;
}
SetLedLight(3);
//全新的触发设置模式 Splash（十字和散斑） Stripe(序列光栅 正交光栅 白图 黑图 光栅图) 具体参看光机控制工具
if (!sn3DDLPdev::sn3DSetTriggerWidth(m_HandleDlpDev, 10, true))
{
return false;
}

if (!sn3DDLPdev::sn3DSetTriggerMode(m_HandleDlpDev, false, true))
{
return false;
}
//首先Splash 注意设置顺序不可更改！！！
if (!sn3DDLPdev::sn3DProjectSetTriggerTimerParam(m_HandleDlpDev, sn3DDLPdev::DLP_SPLASH_MODE, sn3DDLPdev::TRIGGER_ILLUMATION, m_iDLPFreshLight))
{
return false;
}
if (!sn3DDLPdev::sn3DProjectSetTriggerTimerParam(m_HandleDlpDev, sn3DDLPdev::DLP_SPLASH_MODE, sn3DDLPdev::TRIGGER_PRE, m_iDLPFreshPre))
{
return false;
}
if (!sn3DDLPdev::sn3DProjectSetTriggerTimerParam(m_HandleDlpDev, sn3DDLPdev::DLP_SPLASH_MODE, sn3DDLPdev::TRIGGER_POST, m_iDLPFreshPost))
{
return false;
}
//接着设置Stripe
if (!sn3DDLPdev::sn3DProjectSetTriggerTimerParam(m_HandleDlpDev, sn3DDLPdev::DLP_STRIP_MODE, sn3DDLPdev::TRIGGER_ILLUMATION, m_iDLPFreshLight))
{
return false;
}
if (!sn3DDLPdev::sn3DProjectSetTriggerTimerParam(m_HandleDlpDev, sn3DDLPdev::DLP_STRIP_MODE, sn3DDLPdev::TRIGGER_PRE, m_iDLPFreshPre))
{
return false;
}
if (!sn3DDLPdev::sn3DProjectSetTriggerTimerParam(m_HandleDlpDev, sn3DDLPdev::DLP_STRIP_MODE, sn3DDLPdev::TRIGGER_POST, m_iDLPFreshPost))
{
return false;
}
// 设置降频参数 在白光 十字线 光栅等状态下的外触发信号将根据该比例从光机刷新频率降频 如上部分将光机刷新频率设置为60hz 降频6则外触发频率为10hz
if (!sn3DDLPdev::sn3DProjectSetTriggerDiv(m_HandleDlpDev, m_iTrigerDivParam))
{
return false;
}
//完成设置投白光
ProjectWhiteImage();
return true;
}
else if (m_bNetDLP)
{
if (!sn3DOpenProject(m_SocketDev))
{
return false;
}
SetLedLight(3);
//全新的触发设置模式 Splash（十字和散斑） Stripe(序列光栅 正交光栅 白图 黑图 光栅图) 具体参看光机控制工具
if (!sn3DSetTriggerMode(m_SocketDev, false, true)) //低电平触发
{
return false;
}
//首先Splash 注意设置顺序不可更改！！！
if (!sn3DProjectSetTriggerTimerParam(m_SocketDev, DLP_SPLASH_MODE, TRIGGER_ILLUMATION, m_iDLPFreshLight))
{
return false;
}
if (!sn3DProjectSetTriggerTimerParam(m_SocketDev, DLP_SPLASH_MODE, TRIGGER_PRE, m_iDLPFreshPre))
{
return false;
}
if (!sn3DProjectSetTriggerTimerParam(m_SocketDev, DLP_SPLASH_MODE, TRIGGER_POST, m_iDLPFreshPost))
{
return false;
}
//接着设置Stripe
if (!sn3DProjectSetTriggerTimerParam(m_SocketDev, DLP_STRIP_MODE, TRIGGER_ILLUMATION, m_iDLPFreshLight))
{
return false;
}
if (!sn3DProjectSetTriggerTimerParam(m_SocketDev, DLP_STRIP_MODE, TRIGGER_PRE, m_iDLPFreshPre))
{
return false;
}
if (!sn3DProjectSetTriggerTimerParam(m_SocketDev, DLP_STRIP_MODE, TRIGGER_POST, m_iDLPFreshPost))
{
return false;
}
// 设置降频参数 在白光 十字线 光栅等状态下的外触发信号将根据该比例从光机刷新频率降频 如上部分将光机刷新频率设置为60hz 降频6则外触发频率为10hz
if (!sn3DProjectSetTriggerDiv(m_SocketDev, m_iTrigerDivParam))
{
return false;
}
//完成设置投白光
ProjectWhiteImage();
return true;
}
return false;
*/
//接口设计模仿先临的API （具体可对照sn3DDLPDev.h中说明）
//采用与sn3DDLPdevDefine.h中相同的几个枚举值 注意两处定义要同步修改
typedef enum
{
	TRIGGER_PRE = 0x11,
	TRIGGER_ILLUMATION = 0x10,
	TRIGGER_POST = 0x12,
}eTriggerTimeType;
typedef enum
{
	DLP_STRIP_MODE = 0x01,
	DLP_SPLASH_MODE = 0x02,
}eDlpWorkingMode;
typedef enum
{  /*根据协议定义确定这些枚举值*/
	DLP_STRIP_BLACK = 0x19,
	DLP_STRIP_RED = 0x0d,
	DLP_STRIP_GREEN = 0x0e,
	DLP_STRIP_BLUE = 0x0f,
	DLP_STRIP_WHITE = 0x03,
}eDlpStripColor_e;

//720光机与1080光机可通用命令
//连接/断开API 
SN_DLPCONTROL_API bool snInitDLPDevices(SOCKET &devSocket);//打开单光机
SN_DLPCONTROL_API bool snInitDLPDevices(SOCKET &devSocket, CString str_SN);//按照序列号打开单个光机 暂不支持
SN_DLPCONTROL_API bool snInitDLPDevices(vector<SOCKET> &devSocket, vector<CString> &str_SN);//打开多个光机 需要重新分配IP 暂不支持
SN_DLPCONTROL_API bool snExitDLPDevices();//断开光机
//扫描功能函数
SN_DLPCONTROL_API bool sn3DStartScan(SOCKET devSocket);
SN_DLPCONTROL_API bool sn3DStartScanStrip(SOCKET devSocket);
SN_DLPCONTROL_API bool sn3DOpenProject(SOCKET devSocket);
SN_DLPCONTROL_API bool sn3DCloseProject(SOCKET devSocket);
SN_DLPCONTROL_API bool sn3DProjectCross(SOCKET devSocket); //720调用默认带触发 新1080不带触发

//参数设置函数
SN_DLPCONTROL_API bool sn3DSetWaitTimeScan(SOCKET devSocket, int wtTime, bool saveflash = false);
SN_DLPCONTROL_API bool sn3DSetLEDBrightness(SOCKET devSocket, int brightnessR, int brightnessG, int brightnessB, bool saveflash = false);
SN_DLPCONTROL_API bool sn3DSetTriggerWidth(SOCKET devSocket, int triggerwidth, bool saveflash = false);
SN_DLPCONTROL_API bool sn3DSetTriggerMode(SOCKET devSocket, bool hightrigger, bool saveflash = false); /*设置触发信号极性*/

//查询状态函数
SN_DLPCONTROL_API bool sn3DGetWaitTimeScan(SOCKET devSocket, int *wtTime);      /*查询触发信号周期,单位ms*/
SN_DLPCONTROL_API bool sn3DGetTriggerMode(SOCKET devSocket, bool *hightrigger); /*查询触发信号极性*/
SN_DLPCONTROL_API bool sn3DGetTriggerWidth(SOCKET devSocket, int *triggerwidth);/*查询触发信号宽度,单位ms*/
SN_DLPCONTROL_API bool sn3DGetLEDBrightness(SOCKET devSocket, int *brightnessR, int *brightnessG, int *brightnessB);/*查询光机亮度(0-255)，仅蓝色有效*/

//新版1080光机可用接口
SN_DLPCONTROL_API bool sn3DProjectCrossTrigger(SOCKET devSocket);//投十字，产生触发信号
SN_DLPCONTROL_API bool sn3DStartScanTrigger(SOCKET devSocket); //投序列光栅,产生触发信号
SN_DLPCONTROL_API bool sn3DStartScanStripTrigger(SOCKET devSocket);//投正交光栅,产生触发信号

SN_DLPCONTROL_API bool sn3DSetScanStepSetIndex(SOCKET devSocket, int Setindex, bool saveflash);/*设置单步投影的Set编号*/
SN_DLPCONTROL_API bool sn3DScanStep(SOCKET devSocket);/*单步投图*/
SN_DLPCONTROL_API bool sn3DShowSplashByIndex(SOCKET devSocket, BYTE index, bool trigger);//投指定编号的splash图
SN_DLPCONTROL_API bool sn3DProjectStripShowSingleColor(SOCKET devSocket, eDlpStripColor_e color, bool trigger_on);/*投指定颜色的条纹图*/
SN_DLPCONTROL_API bool sn3DProjectSetTriggerOn_Off(SOCKET devSocket, bool on);/*控制是否产生触发信号,true:产生触发信号 false:不产生触发信号*/
SN_DLPCONTROL_API bool sn3DProjectSetTriggerDiv(SOCKET devSocket, BYTE div_val);/*设置光机触发信号分频系数*/
SN_DLPCONTROL_API bool sn3DProjectSetTriggerTimerParam(SOCKET devSocket, eDlpWorkingMode mode, eTriggerTimeType type, UINT time_us);/*新版本库增加的设置光机触发信号时间参数*/

//SN_DLPCONTROL_API bool sn3DGetHIDDEVVersion(SOCKET devSocket, int *version);    /*获取光机固件版本*/ 未调用 暂时不做网口功能
//SN_DLPCONTROL_API bool sn3DGetHIDDEVVersionEX(SOCKET devSocket, BYTE version[16]);/*获取光机固件版本*/
SN_DLPCONTROL_API bool sn3DProjectGetTriggerOn_Off(SOCKET devSocket, BYTE *on_off);/*查询是否产生触发信号,true:产生触发信号 false:不产生触发信号*/
SN_DLPCONTROL_API bool sn3DProjectGetTriggerDiv(SOCKET devSocket, BYTE *div_val);/*读取光机触发信号分频系数*/
SN_DLPCONTROL_API bool sn3DProjectGetTriggerTimerParam(SOCKET devSocket, eDlpWorkingMode mode, eTriggerTimeType type, UINT *time_us);/*新版本库增加的读取光机触发信号时间参数*/

//720光机（或老版1080）光机可用接口
SN_DLPCONTROL_API bool sn3DRunCamera(SOCKET devSocket, bool bStart = true);
SN_DLPCONTROL_API bool sn3DProjectWhite(SOCKET devSocket);//1080禁用
SN_DLPCONTROL_API bool sn3DProjectStrip(SOCKET devSocket, int frameID);
SN_DLPCONTROL_API bool sn3DProjectStripTrig(SOCKET devSocket, int frameID);//
SN_DLPCONTROL_API bool sn3DProjectBlue(SOCKET devSocket);

SN_DLPCONTROL_API bool sn3DSetWaitTime(SOCKET devSocket, int wtTime, bool saveflash = false);
SN_DLPCONTROL_API bool sn3DSetProjectVedioPeriod(SOCKET devSocket, int wtTime, bool saveflash = false);
SN_DLPCONTROL_API bool sn3DWriteStrip(SOCKET devSocket, unsigned char stripId, int datasize, unsigned char* data);
SN_DLPCONTROL_API bool sn3DWriteUserData(SOCKET devSocket, int datasize, unsigned char* data);
SN_DLPCONTROL_API bool sn3DSetStrippleInfo(SOCKET devSocket, int horzstripAddr, int vertstripleAddr, int stripNumber);
SN_DLPCONTROL_API bool sn3DResetRunTime(SOCKET devSocket);
//参数读取函数
SN_DLPCONTROL_API bool sn3DReadStrip(SOCKET devSocket, unsigned char stripId, int datasize, unsigned char *data);
SN_DLPCONTROL_API bool sn3DReadUserDataLength(SOCKET devSocket, int *datasize);
SN_DLPCONTROL_API bool sn3DReadUserData(SOCKET devSocket, int datasize, unsigned char* &data);
SN_DLPCONTROL_API bool sn3DGetRunTime(SOCKET devSocket, int *iTime); //查询光机运行时间
SN_DLPCONTROL_API bool sn3DGetTurnOffReason(SOCKET devSocket, int *iReason); //查询光机运行时间

//硬件主板通信不属于先临光机部分
//附件控制 激光器  
SN_DLPCONTROL_API bool LaserControl(SOCKET devSocket, bool bOpen);//控制激光器附件开闭
// 心跳维持
SN_DLPCONTROL_API bool SendHeartBeat(SOCKET devSocket);
#endif // API_SNDLPCONTROL_H