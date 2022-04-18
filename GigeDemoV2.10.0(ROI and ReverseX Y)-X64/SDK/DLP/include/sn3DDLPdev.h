// File: sn3DDLPdev.h

#ifndef _sn3DDLPdev_H
#define _sn3DDLPdev_H

#include "sn3DDLPdevDefine.h"
#include "sn3DDLPdev_export.h"
#include <vector>
/*ʾ��demo
HANDLE m_HandleDlpDev;

UINT m_iDLPFreshPre = 1300;
UINT m_iDLPFreshLight = 14000;
UINT m_iDLPFreshPost = 1366; //ע�����������֮�ͱ������m_dDLPRefreshCycle!!!! �¹�����ò������Ϊ������
UINT m_iTrigerDivParam = 8; //����ⴥ����Ƶ���� �ⴥ��Ƶ�ʰ��˵ȱ�������
void SetLedLight(int iProjectLed)
{
	//��0-100ת��Ϊ0-245 //�¹�����ҶȾ͵�245 
	
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
		// 1080�����Ĭ��״̬��Ͷ���׹� ������
		sn3DDLPdev::sn3DProjectStripShowSingleColor(m_HandleDlpDev, sn3DDLPdev::DLP_STRIP_WHITE, true);
	}
}
int TestShiningDLP()
{
	bool m_bNetDLP = false;//Ĭ��U�ڹ��
	if (!sn3DDLPdev::sn3DInitHidDev(m_HandleDlpDev))
	{
		m_HandleDlpDev = NULL;

	}

	if (m_HandleDlpDev != NULL && !m_bNetDLP)
	{   //2020-1-8������ʹ���°�1080��� ��720��ȫ��ͬ���¿����߼�
		if (!sn3DDLPdev::sn3DOpenProject(m_HandleDlpDev))
		{
			return false;
		}
		SetLedLight(3);
		//ȫ�µĴ�������ģʽ Splash��ʮ�ֺ�ɢ�ߣ� Stripe(���й�դ ������դ ��ͼ ��ͼ ��դͼ) ����ο�������ƹ���
		if (!sn3DDLPdev::sn3DSetTriggerWidth(m_HandleDlpDev, 10, true))
		{
			return false;
		}

		if (!sn3DDLPdev::sn3DSetTriggerMode(m_HandleDlpDev, false, true))
		{
			return false;
		}
		//����Splash ע������˳�򲻿ɸ��ģ�����
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
		//��������Stripe
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
		// ���ý�Ƶ���� �ڰ׹� ʮ���� ��դ��״̬�µ��ⴥ���źŽ����ݸñ����ӹ��ˢ��Ƶ�ʽ�Ƶ ���ϲ��ֽ����ˢ��Ƶ������Ϊ60hz ��Ƶ6���ⴥ��Ƶ��Ϊ10hz
		if (!sn3DDLPdev::sn3DProjectSetTriggerDiv(m_HandleDlpDev, m_iTrigerDivParam))
		{
			return false;
		}
		//�������Ͷ�׹�
		ProjectWhiteImage();
		return true;
	}
}
*/
namespace sn3DDLPdev
{
	/*****************************************720��1080���ͨ�ò���*************************************/
    SN3DDLPDEV_EXPORT bool sn3DInitHidDev(HANDLE &devhandle);
    SN3DDLPDEV_EXPORT bool sn3DInitHidDev(HANDLE &devhandle, char* SerialNumber);//����ָ�����кŴ򿪶˿�
	SN3DDLPDEV_EXPORT bool sn3DInitHidDev(std::vector<HANDLE> &devhandle, std::vector<std::string> &SerialNumber);
	SN3DDLPDEV_EXPORT bool sn3DExitHidDev(HANDLE devhangle);
	SN3DDLPDEV_EXPORT bool sn3DExitHidDev(std::vector<HANDLE> devhandle);
	
	//////////////////////////////////////////////////////////////////////////
	//���ݷ��ͽӿ� //��Զ������δ���øò��ֺ���
	//////////////////////////////////////////////////////////////////////////
	SN3DDLPDEV_EXPORT bool sn3DSendCommand(HANDLE devhandle, UCHAR hdCmd, UCHAR subCmd, BYTE *pParam, UCHAR paramSize);
	SN3DDLPDEV_EXPORT bool sn3DReadStatus(HANDLE devhandle, BYTE* status);
	SN3DDLPDEV_EXPORT bool sn3DSendPacketSS(HANDLE devhandle, BYTE *SendData, USHORT Size);
	SN3DDLPDEV_EXPORT bool sn3DReadPacketSS(HANDLE devhandle, BYTE* packet);
	
	//////////////////////////////////////////////////////////////////////////
	//ɨ�蹦�ܺ���
	//////////////////////////////////////////////////////////////////////////
	SN3DDLPDEV_EXPORT bool sn3DOpenProject(HANDLE devhandle);//��ͶӰ
	SN3DDLPDEV_EXPORT bool sn3DCloseProject(HANDLE devhandle);//�ر�ͶӰ��Ͷ��ͼ
	SN3DDLPDEV_EXPORT bool sn3DProjectCross(HANDLE devhandle); //Ͷʮ�֣������������ź� 720Ĭ�ϴ����� 1080��������������Ҫ����������·�1080��Ӧ������
	SN3DDLPDEV_EXPORT bool sn3DStartScan(HANDLE devhandle);        //Ͷ���й�դ,�����������ź� 720Ĭ�ϴ����� 1080��������������Ҫ����������·�1080��Ӧ������
	SN3DDLPDEV_EXPORT bool sn3DStartScanStrip(HANDLE devhandle);   //Ͷ������դ,�����������ź� 720Ĭ�ϴ����� 1080��������������Ҫ����������·�1080��Ӧ������

	/**********************�������ú���**************************************/
	SN3DDLPDEV_EXPORT bool sn3DSetTriggerWidth(HANDLE devhandle, int triggerwidth, bool saveflash = false);/*���ô����źſ�ȣ���λms*/
	SN3DDLPDEV_EXPORT bool sn3DSetWaitTimeScan(HANDLE devhandle, int wtTime, bool saveflash = false);      /*���ô����ź�����,��λms*/
	SN3DDLPDEV_EXPORT bool sn3DSetTriggerMode(HANDLE devhandle, bool hightrigger, bool saveflash = false); /*���ô����źż���*/
	SN3DDLPDEV_EXPORT bool sn3DSetLEDBrightness(HANDLE devhandle, int brightnessR, int brightnessG, int brightnessB, bool saveflash = false);/*���ù������(0-255)������ɫ��Ч*/
	
	///////////////////��ѯ״̬����////////////////////////////////////////
	SN3DDLPDEV_EXPORT bool sn3DGetWaitTimeScan(HANDLE devhandle, int *wtTime);      /*��ѯ�����ź�����,��λms*/
	SN3DDLPDEV_EXPORT bool sn3DGetTriggerMode(HANDLE devhandle, bool *hightrigger); /*��ѯ�����źż���*/
	SN3DDLPDEV_EXPORT bool sn3DGetTriggerWidth(HANDLE devhandle, int *triggerwidth);/*��ѯ�����źſ��,��λms*/
	SN3DDLPDEV_EXPORT bool sn3DGetLEDBrightness(HANDLE devhandle, int *brightnessR, int *brightnessG, int *brightnessB);/*��ѯ�������(0-255)������ɫ��Ч*/

	/************************���½ӿڽ��°�1080����ɵ���************************************/
	SN3DDLPDEV_EXPORT bool sn3DProjectCrossTrigger(HANDLE devhandle);//Ͷʮ�֣����������ź�
	SN3DDLPDEV_EXPORT bool sn3DStartScanTrigger(HANDLE devhandle); //Ͷ���й�դ,���������ź�
	SN3DDLPDEV_EXPORT bool sn3DStartScanStripTrigger(HANDLE devhandle);//Ͷ������դ,���������ź�
	SN3DDLPDEV_EXPORT bool sn3DProjectSpeckle(HANDLE devhandle);    //Ͷɢ��,�����������ź�
	SN3DDLPDEV_EXPORT bool sn3DProjectSpeckleTrig(HANDLE devhandle); //Ͷɢ��,���������ź�
	
	SN3DDLPDEV_EXPORT bool sn3DSetScanStepSetIndex(HANDLE devhandle, int Setindex, bool saveflash);/*���õ���ͶӰ��Set���*/
	SN3DDLPDEV_EXPORT bool sn3DScanStep(HANDLE devhandle);/*����Ͷͼ*/
	SN3DDLPDEV_EXPORT bool sn3DShowSplashByIndex(HANDLE devhandle, BYTE index, bool trigger);//Ͷָ����ŵ�splashͼ
	SN3DDLPDEV_EXPORT bool sn3DProjectStripShowSingleColor(HANDLE devhandle, eDlpStripColor_e color, bool trigger_on);/*Ͷָ����ɫ������ͼ*/
	SN3DDLPDEV_EXPORT bool sn3DProjectSetTriggerOn_Off(HANDLE devhandle, bool on);/*�����Ƿ���������ź�,true:���������ź� false:�����������ź�*/
	SN3DDLPDEV_EXPORT bool sn3DProjectSetTriggerDiv(HANDLE devhandle, BYTE div_val);/*���ù�������źŷ�Ƶϵ��*/
	SN3DDLPDEV_EXPORT bool sn3DProjectSetTriggerTimerParam(HANDLE devhandle, eDlpWorkingMode mode, eTriggerTimeType type, UINT time_us);/*�°汾�����ӵ����ù�������ź�ʱ�����*/

	SN3DDLPDEV_EXPORT bool sn3DGetHIDDEVVersion(HANDLE devhandel, int *version);    /*��ȡ����̼��汾*/
	SN3DDLPDEV_EXPORT bool sn3DGetHIDDEVVersionEX(HANDLE devhandel, BYTE version[16]);/*��ȡ����̼��汾*/
	SN3DDLPDEV_EXPORT bool sn3DProjectGetTriggerOn_Off(HANDLE devhandle, BYTE *on_off);/*��ѯ�Ƿ���������ź�,true:���������ź� false:�����������ź�*/
	SN3DDLPDEV_EXPORT bool sn3DProjectGetTriggerDiv(HANDLE devhandle, BYTE *div_val);/*��ȡ��������źŷ�Ƶϵ��*/
	SN3DDLPDEV_EXPORT bool sn3DProjectGetTriggerTimerParam(HANDLE devhandle, eDlpWorkingMode mode, eTriggerTimeType type, UINT *time_us);/*�°汾�����ӵĶ�ȡ��������ź�ʱ�����*/

	/************************���½ӿڽ�720����ɵ���*************************/
	SN3DDLPDEV_EXPORT bool sn3DRunCamera(HANDLE devhandle, bool bStart = true);//bStart=true ��ʾvedioģʽ bStart=false��ʾ�ⴥ��ģʽ
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