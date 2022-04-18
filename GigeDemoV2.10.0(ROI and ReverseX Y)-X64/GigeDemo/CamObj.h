#pragma once
#include "stdafx.h"
class CCamObj
{
public:
	CCamObj();
	~CCamObj();

public:
	virtual	bool InitDevice(CString strCamID, int iWidth, int iHeight);
	virtual bool SetGain(double dGain);
	virtual bool SetExposureTime(double iExposureTime);
	virtual bool UninitDevice();
	virtual bool Start();
	virtual bool Stop();
	virtual bool SetTriggerSource(CString strSource);
	virtual bool SetTriggerActivation(CString strActivation);
	virtual bool SetTriggerEnable(bool bEnable);
	virtual bool SetTriggerDelay(int iTime);
	virtual bool SoftWareTriggerOnce();
};

