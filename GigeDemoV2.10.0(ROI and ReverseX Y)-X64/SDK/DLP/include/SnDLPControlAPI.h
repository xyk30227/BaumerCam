//---------------------------------------------------------------//
//-------------------2020.02.19�������޸�------------------------//
//�°�1080����������ϰ���ڲ��� ���ֺ���������720��1080��ͨ�õ���� ��ע��

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
bool m_bNetDLP = false;//Ĭ��U�ڹ��
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
else if (m_bNetDLP)
{
if (!sn3DOpenProject(m_SocketDev))
{
return false;
}
SetLedLight(3);
//ȫ�µĴ�������ģʽ Splash��ʮ�ֺ�ɢ�ߣ� Stripe(���й�դ ������դ ��ͼ ��ͼ ��դͼ) ����ο�������ƹ���
if (!sn3DSetTriggerMode(m_SocketDev, false, true)) //�͵�ƽ����
{
return false;
}
//����Splash ע������˳�򲻿ɸ��ģ�����
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
//��������Stripe
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
// ���ý�Ƶ���� �ڰ׹� ʮ���� ��դ��״̬�µ��ⴥ���źŽ����ݸñ����ӹ��ˢ��Ƶ�ʽ�Ƶ ���ϲ��ֽ����ˢ��Ƶ������Ϊ60hz ��Ƶ6���ⴥ��Ƶ��Ϊ10hz
if (!sn3DProjectSetTriggerDiv(m_SocketDev, m_iTrigerDivParam))
{
return false;
}
//�������Ͷ�׹�
ProjectWhiteImage();
return true;
}
return false;
*/
//�ӿ����ģ�����ٵ�API ������ɶ���sn3DDLPDev.h��˵����
//������sn3DDLPdevDefine.h����ͬ�ļ���ö��ֵ ע����������Ҫͬ���޸�
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
{  /*����Э�鶨��ȷ����Щö��ֵ*/
	DLP_STRIP_BLACK = 0x19,
	DLP_STRIP_RED = 0x0d,
	DLP_STRIP_GREEN = 0x0e,
	DLP_STRIP_BLUE = 0x0f,
	DLP_STRIP_WHITE = 0x03,
}eDlpStripColor_e;

//720�����1080�����ͨ������
//����/�Ͽ�API 
SN_DLPCONTROL_API bool snInitDLPDevices(SOCKET &devSocket);//�򿪵����
SN_DLPCONTROL_API bool snInitDLPDevices(SOCKET &devSocket, CString str_SN);//�������кŴ򿪵������ �ݲ�֧��
SN_DLPCONTROL_API bool snInitDLPDevices(vector<SOCKET> &devSocket, vector<CString> &str_SN);//�򿪶����� ��Ҫ���·���IP �ݲ�֧��
SN_DLPCONTROL_API bool snExitDLPDevices();//�Ͽ����
//ɨ�蹦�ܺ���
SN_DLPCONTROL_API bool sn3DStartScan(SOCKET devSocket);
SN_DLPCONTROL_API bool sn3DStartScanStrip(SOCKET devSocket);
SN_DLPCONTROL_API bool sn3DOpenProject(SOCKET devSocket);
SN_DLPCONTROL_API bool sn3DCloseProject(SOCKET devSocket);
SN_DLPCONTROL_API bool sn3DProjectCross(SOCKET devSocket); //720����Ĭ�ϴ����� ��1080��������

//�������ú���
SN_DLPCONTROL_API bool sn3DSetWaitTimeScan(SOCKET devSocket, int wtTime, bool saveflash = false);
SN_DLPCONTROL_API bool sn3DSetLEDBrightness(SOCKET devSocket, int brightnessR, int brightnessG, int brightnessB, bool saveflash = false);
SN_DLPCONTROL_API bool sn3DSetTriggerWidth(SOCKET devSocket, int triggerwidth, bool saveflash = false);
SN_DLPCONTROL_API bool sn3DSetTriggerMode(SOCKET devSocket, bool hightrigger, bool saveflash = false); /*���ô����źż���*/

//��ѯ״̬����
SN_DLPCONTROL_API bool sn3DGetWaitTimeScan(SOCKET devSocket, int *wtTime);      /*��ѯ�����ź�����,��λms*/
SN_DLPCONTROL_API bool sn3DGetTriggerMode(SOCKET devSocket, bool *hightrigger); /*��ѯ�����źż���*/
SN_DLPCONTROL_API bool sn3DGetTriggerWidth(SOCKET devSocket, int *triggerwidth);/*��ѯ�����źſ��,��λms*/
SN_DLPCONTROL_API bool sn3DGetLEDBrightness(SOCKET devSocket, int *brightnessR, int *brightnessG, int *brightnessB);/*��ѯ�������(0-255)������ɫ��Ч*/

//�°�1080������ýӿ�
SN_DLPCONTROL_API bool sn3DProjectCrossTrigger(SOCKET devSocket);//Ͷʮ�֣����������ź�
SN_DLPCONTROL_API bool sn3DStartScanTrigger(SOCKET devSocket); //Ͷ���й�դ,���������ź�
SN_DLPCONTROL_API bool sn3DStartScanStripTrigger(SOCKET devSocket);//Ͷ������դ,���������ź�

SN_DLPCONTROL_API bool sn3DSetScanStepSetIndex(SOCKET devSocket, int Setindex, bool saveflash);/*���õ���ͶӰ��Set���*/
SN_DLPCONTROL_API bool sn3DScanStep(SOCKET devSocket);/*����Ͷͼ*/
SN_DLPCONTROL_API bool sn3DShowSplashByIndex(SOCKET devSocket, BYTE index, bool trigger);//Ͷָ����ŵ�splashͼ
SN_DLPCONTROL_API bool sn3DProjectStripShowSingleColor(SOCKET devSocket, eDlpStripColor_e color, bool trigger_on);/*Ͷָ����ɫ������ͼ*/
SN_DLPCONTROL_API bool sn3DProjectSetTriggerOn_Off(SOCKET devSocket, bool on);/*�����Ƿ���������ź�,true:���������ź� false:�����������ź�*/
SN_DLPCONTROL_API bool sn3DProjectSetTriggerDiv(SOCKET devSocket, BYTE div_val);/*���ù�������źŷ�Ƶϵ��*/
SN_DLPCONTROL_API bool sn3DProjectSetTriggerTimerParam(SOCKET devSocket, eDlpWorkingMode mode, eTriggerTimeType type, UINT time_us);/*�°汾�����ӵ����ù�������ź�ʱ�����*/

//SN_DLPCONTROL_API bool sn3DGetHIDDEVVersion(SOCKET devSocket, int *version);    /*��ȡ����̼��汾*/ δ���� ��ʱ�������ڹ���
//SN_DLPCONTROL_API bool sn3DGetHIDDEVVersionEX(SOCKET devSocket, BYTE version[16]);/*��ȡ����̼��汾*/
SN_DLPCONTROL_API bool sn3DProjectGetTriggerOn_Off(SOCKET devSocket, BYTE *on_off);/*��ѯ�Ƿ���������ź�,true:���������ź� false:�����������ź�*/
SN_DLPCONTROL_API bool sn3DProjectGetTriggerDiv(SOCKET devSocket, BYTE *div_val);/*��ȡ��������źŷ�Ƶϵ��*/
SN_DLPCONTROL_API bool sn3DProjectGetTriggerTimerParam(SOCKET devSocket, eDlpWorkingMode mode, eTriggerTimeType type, UINT *time_us);/*�°汾�����ӵĶ�ȡ��������ź�ʱ�����*/

//720��������ϰ�1080��������ýӿ�
SN_DLPCONTROL_API bool sn3DRunCamera(SOCKET devSocket, bool bStart = true);
SN_DLPCONTROL_API bool sn3DProjectWhite(SOCKET devSocket);//1080����
SN_DLPCONTROL_API bool sn3DProjectStrip(SOCKET devSocket, int frameID);
SN_DLPCONTROL_API bool sn3DProjectStripTrig(SOCKET devSocket, int frameID);//
SN_DLPCONTROL_API bool sn3DProjectBlue(SOCKET devSocket);

SN_DLPCONTROL_API bool sn3DSetWaitTime(SOCKET devSocket, int wtTime, bool saveflash = false);
SN_DLPCONTROL_API bool sn3DSetProjectVedioPeriod(SOCKET devSocket, int wtTime, bool saveflash = false);
SN_DLPCONTROL_API bool sn3DWriteStrip(SOCKET devSocket, unsigned char stripId, int datasize, unsigned char* data);
SN_DLPCONTROL_API bool sn3DWriteUserData(SOCKET devSocket, int datasize, unsigned char* data);
SN_DLPCONTROL_API bool sn3DSetStrippleInfo(SOCKET devSocket, int horzstripAddr, int vertstripleAddr, int stripNumber);
SN_DLPCONTROL_API bool sn3DResetRunTime(SOCKET devSocket);
//������ȡ����
SN_DLPCONTROL_API bool sn3DReadStrip(SOCKET devSocket, unsigned char stripId, int datasize, unsigned char *data);
SN_DLPCONTROL_API bool sn3DReadUserDataLength(SOCKET devSocket, int *datasize);
SN_DLPCONTROL_API bool sn3DReadUserData(SOCKET devSocket, int datasize, unsigned char* &data);
SN_DLPCONTROL_API bool sn3DGetRunTime(SOCKET devSocket, int *iTime); //��ѯ�������ʱ��
SN_DLPCONTROL_API bool sn3DGetTurnOffReason(SOCKET devSocket, int *iReason); //��ѯ�������ʱ��

//Ӳ������ͨ�Ų��������ٹ������
//�������� ������  
SN_DLPCONTROL_API bool LaserControl(SOCKET devSocket, bool bOpen);//���Ƽ�������������
// ����ά��
SN_DLPCONTROL_API bool SendHeartBeat(SOCKET devSocket);
#endif // API_SNDLPCONTROL_H