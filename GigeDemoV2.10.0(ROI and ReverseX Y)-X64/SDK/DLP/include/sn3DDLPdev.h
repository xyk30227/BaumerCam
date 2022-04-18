// File: sn3DDLPdev.h

#ifndef _sn3DDLPdev_H
#define _sn3DDLPdev_H

#include "sn3DDLPdevDefine.h"
#include "sn3DDLPdev_export.h"
#include <vector>
/*示例demo
HANDLE m_HandleDlpDev;

UINT m_iDLPFreshPre = 1300;
UINT m_iDLPFreshLight = 14000;
UINT m_iDLPFreshPost = 1366; //注意该三个参数之和必须等于m_dDLPRefreshCycle!!!! 新光机将该参数拆分为三部分
UINT m_iTrigerDivParam = 8; //光机外触发分频参数 外触发频率按此等比例降低
void SetLedLight(int iProjectLed)
{
	//将0-100转换为0-245 //新光机最大灰度就到245 
	
	int iLight = (int)(iProjectLed / 100.0f * 245);
	if (m_HandleDlpDev != NULL && !false)
	{
		bool bRes = sn3DDLPdev::sn3DSetLEDBrightness(m_HandleDlpDev, 0, 0, iLight, true);
	}
}
void ProjectWhiteImage()
{
	if (m_HandleDlpDev != NULL && !false)
	{
		// 1080光机在默认状态下投纯白光 带触发
		sn3DDLPdev::sn3DProjectStripShowSingleColor(m_HandleDlpDev, sn3DDLPdev::DLP_STRIP_WHITE, true);
	}
}
int TestShiningDLP()
{
	bool m_bNetDLP = false;//默认U口光机
	if (!sn3DDLPdev::sn3DInitHidDev(m_HandleDlpDev))
	{
		m_HandleDlpDev = NULL;

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
}
*/
namespace sn3DDLPdev
{
	/*****************************************720与1080光机通用部分*************************************/
    SN3DDLPDEV_EXPORT bool sn3DInitHidDev(HANDLE &devhandle);
    SN3DDLPDEV_EXPORT bool sn3DInitHidDev(HANDLE &devhandle, char* SerialNumber);//根据指定序列号打开端口
	SN3DDLPDEV_EXPORT bool sn3DInitHidDev(std::vector<HANDLE> &devhandle, std::vector<std::string> &SerialNumber);
	SN3DDLPDEV_EXPORT bool sn3DExitHidDev(HANDLE devhangle);
	SN3DDLPDEV_EXPORT bool sn3DExitHidDev(std::vector<HANDLE> devhandle);
	
	//////////////////////////////////////////////////////////////////////////
	//数据发送接口 //天远程序中未调用该部分函数
	//////////////////////////////////////////////////////////////////////////
	SN3DDLPDEV_EXPORT bool sn3DSendCommand(HANDLE devhandle, UCHAR hdCmd, UCHAR subCmd, BYTE *pParam, UCHAR paramSize);
	SN3DDLPDEV_EXPORT bool sn3DReadStatus(HANDLE devhandle, BYTE* status);
	SN3DDLPDEV_EXPORT bool sn3DSendPacketSS(HANDLE devhandle, BYTE *SendData, USHORT Size);
	SN3DDLPDEV_EXPORT bool sn3DReadPacketSS(HANDLE devhandle, BYTE* packet);
	
	//////////////////////////////////////////////////////////////////////////
	//扫描功能函数
	//////////////////////////////////////////////////////////////////////////
	SN3DDLPDEV_EXPORT bool sn3DOpenProject(HANDLE devhandle);//打开投影
	SN3DDLPDEV_EXPORT bool sn3DCloseProject(HANDLE devhandle);//关闭投影或投黑图
	SN3DDLPDEV_EXPORT bool sn3DProjectCross(HANDLE devhandle); //投十字，不产生触发信号 720默认带触发 1080不带触发（若需要触发请调用下方1080对应函数）
	SN3DDLPDEV_EXPORT bool sn3DStartScan(HANDLE devhandle);        //投序列光栅,不产生触发信号 720默认带触发 1080不带触发（若需要触发请调用下方1080对应函数）
	SN3DDLPDEV_EXPORT bool sn3DStartScanStrip(HANDLE devhandle);   //投正交光栅,不产生触发信号 720默认带触发 1080不带触发（若需要触发请调用下方1080对应函数）

	/**********************参数设置函数**************************************/
	SN3DDLPDEV_EXPORT bool sn3DSetTriggerWidth(HANDLE devhandle, int triggerwidth, bool saveflash = false);/*设置触发信号宽度，单位ms*/
	SN3DDLPDEV_EXPORT bool sn3DSetWaitTimeScan(HANDLE devhandle, int wtTime, bool saveflash = false);      /*设置触发信号周期,单位ms*/
	SN3DDLPDEV_EXPORT bool sn3DSetTriggerMode(HANDLE devhandle, bool hightrigger, bool saveflash = false); /*设置触发信号极性*/
	SN3DDLPDEV_EXPORT bool sn3DSetLEDBrightness(HANDLE devhandle, int brightnessR, int brightnessG, int brightnessB, bool saveflash = false);/*设置光机亮度(0-255)，仅蓝色有效*/
	
	///////////////////查询状态函数////////////////////////////////////////
	SN3DDLPDEV_EXPORT bool sn3DGetWaitTimeScan(HANDLE devhandle, int *wtTime);      /*查询触发信号周期,单位ms*/
	SN3DDLPDEV_EXPORT bool sn3DGetTriggerMode(HANDLE devhandle, bool *hightrigger); /*查询触发信号极性*/
	SN3DDLPDEV_EXPORT bool sn3DGetTriggerWidth(HANDLE devhandle, int *triggerwidth);/*查询触发信号宽度,单位ms*/
	SN3DDLPDEV_EXPORT bool sn3DGetLEDBrightness(HANDLE devhandle, int *brightnessR, int *brightnessG, int *brightnessB);/*查询光机亮度(0-255)，仅蓝色有效*/

	/************************以下接口仅新版1080光机可调用************************************/
	SN3DDLPDEV_EXPORT bool sn3DProjectCrossTrigger(HANDLE devhandle);//投十字，产生触发信号
	SN3DDLPDEV_EXPORT bool sn3DStartScanTrigger(HANDLE devhandle); //投序列光栅,产生触发信号
	SN3DDLPDEV_EXPORT bool sn3DStartScanStripTrigger(HANDLE devhandle);//投正交光栅,产生触发信号
	SN3DDLPDEV_EXPORT bool sn3DProjectSpeckle(HANDLE devhandle);    //投散斑,不产生触发信号
	SN3DDLPDEV_EXPORT bool sn3DProjectSpeckleTrig(HANDLE devhandle); //投散斑,产生触发信号
	
	SN3DDLPDEV_EXPORT bool sn3DSetScanStepSetIndex(HANDLE devhandle, int Setindex, bool saveflash);/*设置单步投影的Set编号*/
	SN3DDLPDEV_EXPORT bool sn3DScanStep(HANDLE devhandle);/*单步投图*/
	SN3DDLPDEV_EXPORT bool sn3DShowSplashByIndex(HANDLE devhandle, BYTE index, bool trigger);//投指定编号的splash图
	SN3DDLPDEV_EXPORT bool sn3DProjectStripShowSingleColor(HANDLE devhandle, eDlpStripColor_e color, bool trigger_on);/*投指定颜色的条纹图*/
	SN3DDLPDEV_EXPORT bool sn3DProjectSetTriggerOn_Off(HANDLE devhandle, bool on);/*控制是否产生触发信号,true:产生触发信号 false:不产生触发信号*/
	SN3DDLPDEV_EXPORT bool sn3DProjectSetTriggerDiv(HANDLE devhandle, BYTE div_val);/*设置光机触发信号分频系数*/
	SN3DDLPDEV_EXPORT bool sn3DProjectSetTriggerTimerParam(HANDLE devhandle, eDlpWorkingMode mode, eTriggerTimeType type, UINT time_us);/*新版本库增加的设置光机触发信号时间参数*/

	SN3DDLPDEV_EXPORT bool sn3DGetHIDDEVVersion(HANDLE devhandel, int *version);    /*获取光机固件版本*/
	SN3DDLPDEV_EXPORT bool sn3DGetHIDDEVVersionEX(HANDLE devhandel, BYTE version[16]);/*获取光机固件版本*/
	SN3DDLPDEV_EXPORT bool sn3DProjectGetTriggerOn_Off(HANDLE devhandle, BYTE *on_off);/*查询是否产生触发信号,true:产生触发信号 false:不产生触发信号*/
	SN3DDLPDEV_EXPORT bool sn3DProjectGetTriggerDiv(HANDLE devhandle, BYTE *div_val);/*读取光机触发信号分频系数*/
	SN3DDLPDEV_EXPORT bool sn3DProjectGetTriggerTimerParam(HANDLE devhandle, eDlpWorkingMode mode, eTriggerTimeType type, UINT *time_us);/*新版本库增加的读取光机触发信号时间参数*/

	/************************以下接口仅720光机可调用*************************/
	SN3DDLPDEV_EXPORT bool sn3DRunCamera(HANDLE devhandle, bool bStart = true);//bStart=true 表示vedio模式 bStart=false表示外触发模式
	SN3DDLPDEV_EXPORT bool sn3DProjectWhite(HANDLE devhandle);
	SN3DDLPDEV_EXPORT bool sn3DStartScanBinary(HANDLE devhandle, char startId, char endId);
	SN3DDLPDEV_EXPORT bool sn3DProjectStrip(HANDLE devhandle, int frameID);
	SN3DDLPDEV_EXPORT bool sn3DProjectStripTrig(HANDLE devhandle, int frameID);
	SN3DDLPDEV_EXPORT bool sn3DProjectGrayWhite(HANDLE devhandle, int grayvalue);
	SN3DDLPDEV_EXPORT bool sn3DProjectGrayWhiteTrig(HANDLE devhandle, int grayvalue);
	SN3DDLPDEV_EXPORT bool sn3DProjectWhiteTrig(HANDLE devhandle);
	SN3DDLPDEV_EXPORT bool sn3DProjectRed(HANDLE devhandle);
	SN3DDLPDEV_EXPORT bool sn3DProjectGreen(HANDLE devhandle);
	SN3DDLPDEV_EXPORT bool sn3DProjectBlue(HANDLE devhandle);
	SN3DDLPDEV_EXPORT bool sn3DProjectRedTrig(HANDLE devhandle);
	SN3DDLPDEV_EXPORT bool sn3DProjectGreenTrig(HANDLE devhandle);
	SN3DDLPDEV_EXPORT bool sn3DProjectBlueTrig(HANDLE devhandle);
    /////////////////////////////////////////////////////////////////////////////////
	SN3DDLPDEV_EXPORT bool sn3DSetWaitTime(HANDLE devhandle, int wtTime, bool saveflash=false);
	SN3DDLPDEV_EXPORT bool sn3DSetCameraNumber(HANDLE devhandle, int cameranumber, bool saveflash=false);
	SN3DDLPDEV_EXPORT bool sn3DSetCameraType(HANDLE devhandle, int cameratype=0x02, bool saveflash=false);
	SN3DDLPDEV_EXPORT bool sn3DSetProjectVedioPeriod(HANDLE devhandle, int period, bool saveflash=false);
	SN3DDLPDEV_EXPORT bool sn3DSetLEDStatus(HANDLE devhandle, int status, bool saveflash=false);
    SN3DDLPDEV_EXPORT bool sn3DWriteStrip(HANDLE devhandle, unsigned  char stripId, int datasize, unsigned char *data);
	SN3DDLPDEV_EXPORT bool sn3DWriteUserData(HANDLE devhandle, int datasize, unsigned char*data);
	SN3DDLPDEV_EXPORT bool sn3DWriteUserData(HANDLE devhandle, int datasize, unsigned char*data,int index);
	SN3DDLPDEV_EXPORT bool sn3DSetStrippleInfo(HANDLE devhandle, int horzstripAddr, int vertstripleAddr, int stripNumber);
	SN3DDLPDEV_EXPORT bool sn3DSetFanRunTemp(HANDLE devhandle, int fanRunTemp);
	SN3DDLPDEV_EXPORT bool sn3DSetCutPara(HANDLE devhandle, BYTE leftcut, BYTE rightcut, bool saveflash = false);
	SN3DDLPDEV_EXPORT bool sn3DGetWaitTime(HANDLE devhandle, int *wtTime);
	SN3DDLPDEV_EXPORT bool sn3DGetCameraNumber(HANDLE devhandle, int *cameranumber);
	SN3DDLPDEV_EXPORT bool sn3DGetCameraType(HANDLE devhandle, int *cameratype);
	SN3DDLPDEV_EXPORT bool sn3DGetVideoPeriod(HANDLE devhandle, int *period);
	SN3DDLPDEV_EXPORT bool sn3DReadStrip(HANDLE devhandle, unsigned char stripId, int datasize, unsigned char *data);
	SN3DDLPDEV_EXPORT bool sn3DReadUserData(HANDLE devhandle, int *datasize, unsigned char* &data);
	SN3DDLPDEV_EXPORT bool sn3DReadUserData(HANDLE devhandle, int datasize, unsigned char* data,int index);
	SN3DDLPDEV_EXPORT bool sn3DGetProjectorTemp(HANDLE devhandle, int *currentTemp);
	SN3DDLPDEV_EXPORT bool sn3DGetFanRunTemp(HANDLE devhandle, int *fanRunTemp);
}

#endif //_sn3DHiddev_H