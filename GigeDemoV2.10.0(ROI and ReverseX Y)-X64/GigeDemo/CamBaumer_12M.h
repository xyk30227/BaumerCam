#pragma once
#include "camobj.h"
class CCamBaumer_12M :
	public CCamObj
{
public:
	CCamBaumer_12M();
	~CCamBaumer_12M();
public:
	BGAPI2::Device *          m_pDevice;
	BGAPI2::String            m_sDeviceID;

	//variables for Datastreamlist and datastream
	BGAPI2::DataStreamList*   m_pDatastreamList;
	BGAPI2::DataStream*       m_pDataStream;
	BGAPI2::String            m_sDataStreamID;

	//variables for Bufferlist and buffer
	BGAPI2::BufferList*       m_pBufferList;
	BGAPI2::Buffer*           m_pBuffer;
	BGAPI2::String            m_sBufferID;
public:
	bool InitDevice(BGAPI2::DeviceList *pDeviceList, CString strCamID, int iWidth, int iHeight, BGAPI2::Device *&pDevice);
	bool SetGain(double dGain);
	bool SetExposureTime(double iExposureTime);
	bool UninitDevice();
	bool Start();
	bool Stop();
	bool SetTriggerSource(CString strSource);
	bool SetTriggerActivation(CString strActivation);
	bool SetTriggerEnable(bool bEnable);
	bool SetTriggerDelay(int iTime);
	bool SoftWareTriggerOnce();
public:
	
};

