#include "stdafx.h"
#include "CamBaumer_12M.h"


CCamBaumer_12M::CCamBaumer_12M()
{
}


CCamBaumer_12M::~CCamBaumer_12M()
{
}


bool CCamBaumer_12M::InitDevice(BGAPI2::DeviceList *m_pDeviceList, CString strCamID, int iWidth, int iHeight, BGAPI2::Device *&pDevice)
{
	USES_CONVERSION;
	try
	{
		for (BGAPI2::DeviceList::iterator devIterator = m_pDeviceList->begin(); devIterator != m_pDeviceList->end(); devIterator++)
		{
			try
			{
				//Debug part********************
				CString strDevID = A2W(devIterator->second->GetID());

				CString strDevModel = A2W(devIterator->second->GetModel());
				CString strDevType = A2W(devIterator->second->GetTLType());
				CString strDevVendor = A2W(devIterator->second->GetVendor());
				CString strDevAccessStatus = A2W(devIterator->second->GetAccessStatus());
				CString strDevSN = A2W(devIterator->second->GetSerialNumber());
				CString strDevUserID = A2W(devIterator->second->GetDisplayName());
				//******************************
				devIterator->second->Open();
				m_sDeviceID = devIterator->first;

			}
			catch (BGAPI2::Exceptions::ResourceInUseException& ex)
			{
				CString str8;
				str8.Format(_T("Interface %s already opened!ResourceInUseException:%s"), devIterator->first, ex.GetErrorDescription());
				AfxMessageBox(str8);
				return false;
			}
		}
	}
	catch (BGAPI2::Exceptions::IException& ex)
	{
		CString str9;
		str9.Format(_T("ExceptionType:%s! ErrorDescription:%s in function:%s"), ex.GetType(), ex.GetErrorDescription(), ex.GetFunctionName());
		AfxMessageBox(str9);
		return false;
	}

	if (m_sDeviceID == "")
	{
		AfxMessageBox(_T("No Device found!"));
// 		m_pInterface->Close();
// 		m_pSystem->Close();
// 		BGAPI2::SystemList::ReleaseInstance();
		return false;
	}
	else
	{
		m_pDevice = (*m_pDeviceList)[m_sDeviceID];
		pDevice = m_pDevice;
	}

	//*****************************************Í£ÏÂSEQUENCE
	m_pDevice->GetRemoteNode("AcquisitionStop")->Execute();

	if (m_pDevice->GetRemoteNode("SequencerMode")->GetString() == "On")
	{
		m_pDevice->GetRemoteNode("SequencerMode")->SetString("Off");

	}

	//*****************************************
	//SET TRIGGER MODE OFF (FreeRun)
	try
	{
		USES_CONVERSION;
		CString strUserID = A2W(m_pDevice->GetRemoteNode("DeviceUserID")->GetString());
		m_pDevice->GetRemoteNode("TriggerMode")->SetString("Off");
		//Debug part*************************
		CString strTMode = A2W(m_pDevice->GetRemoteNode("TriggerMode")->GetValue());
		//***********************************
	}
	catch (BGAPI2::Exceptions::IException& ex)
	{
		CString str10;
		str10.Format(_T("ExceptionType:%s! ErrorDescription:%s in function:%s"), ex.GetType(), ex.GetErrorDescription(), ex.GetFunctionName());
		AfxMessageBox(str10);
		return false;
	}

	//COUNTING AVAILABLE DATASTREAMS
	try
	{
		m_pDatastreamList = m_pDevice->GetDataStreams();
		m_pDatastreamList->Refresh();
		//Debug part ****************************
		int iDscount = (int)m_pDatastreamList->size();
		int x = 0;
		//***************************************
	}
	catch (BGAPI2::Exceptions::IException& ex)
	{
		CString str11;
		str11.Format(_T("ExceptionType:%s! ErrorDescription:%s in function:%s"), ex.GetType(), ex.GetErrorDescription(), ex.GetFunctionName());
		AfxMessageBox(str11);
		return false;
	}

	//OPEN THE FIRST DATASTREAM IN THE LIST
	try
	{
		for (BGAPI2::DataStreamList::iterator dstIterator = m_pDatastreamList->begin(); dstIterator != m_pDatastreamList->end(); dstIterator++)
		{
			dstIterator->second->Open();
			m_sDataStreamID = dstIterator->first;
			//Debug part****************************
			CString strDsminBuffer = A2W(dstIterator->second->GetNode("StreamAnnounceBufferMinimum")->GetValue());
			if (dstIterator->second->GetTLType() == "GEV")
			{
				CString strDriver = A2W(dstIterator->second->GetNode("StreamDriverModel")->GetValue());
			}
			//**************************************
			break;
		}
	}
	catch (BGAPI2::Exceptions::IException& ex)
	{
		CString str12;
		str12.Format(_T("ExceptionType:%s! ErrorDescription:%s in function:%s"), ex.GetType(), ex.GetErrorDescription(), ex.GetFunctionName());
		AfxMessageBox(str12);
		return false;
	}
	if (m_sDataStreamID == "")
	{
		AfxMessageBox(_T("No DataStream found!"));
		m_pDevice->Close();
// 		m_pInterface->Close();
// 		m_pSystem->Close();
// 		BGAPI2::SystemList::ReleaseInstance();
		return false;
	}
	else
	{
		m_pDataStream = (*m_pDatastreamList)[m_sDataStreamID];
	}
	//BufferList
	try
	{
		m_pBufferList = m_pDataStream->GetBufferList();
		// 4 buffers using internal buffer mode
		for (int i = 0; i<4; i++)
		{
			m_pBuffer = new BGAPI2::Buffer();
			m_pBufferList->Add(m_pBuffer);
		}
		CString strBuffersize;
		strBuffersize.Format(_T("%d Buffers using %ld bytes!"), m_pBufferList->GetAnnouncedCount(), m_pBuffer->GetMemSize()*m_pBufferList->GetAnnouncedCount());
	}
	catch (BGAPI2::Exceptions::IException& ex)
	{
		CString str13;
		str13.Format(_T("ExceptionType:%s! ErrorDescription:%s in function:%s"), ex.GetType(), ex.GetErrorDescription(), ex.GetFunctionName());
		AfxMessageBox(str13);
		return false;
	}

	//
	try
	{
		for (BGAPI2::BufferList::iterator bfIterator = m_pBufferList->begin(); bfIterator != m_pBufferList->end(); bfIterator++)
		{
			bfIterator->second->QueueBuffer();
		}
		int iQBuffer = (int)m_pBufferList->GetQueuedCount();
		int x = 0;
	}
	catch (BGAPI2::Exceptions::IException& ex)
	{
		CString str14;
		str14.Format(_T("ExceptionType:%s! ErrorDescription:%s in function:%s"), ex.GetType(), ex.GetErrorDescription(), ex.GetFunctionName());
		AfxMessageBox(str14);
		return false;
	}

	//EVENTMODE IMAGE HANDLER
	try
	{
		m_pDataStream->RegisterNewBufferEvent(BGAPI2::Events::EVENTMODE_EVENT_HANDLER);
		m_pDataStream->RegisterNewBufferEventHandler(this, (Events::NewBufferEventHandler) &BufferHandler);
	}
	catch (BGAPI2::Exceptions::IException& ex)
	{
		CString str15;
		str15.Format(_T("ExceptionType:%s! ErrorDescription:%s in function:%s"), ex.GetType(), ex.GetErrorDescription(), ex.GetFunctionName());
		AfxMessageBox(str15);
		return false;
	}



	//START DataStream acquisition
	try
	{
		//m_pDataStream->StopAcquisition();
		m_pDataStream->StartAcquisitionContinuous();
	}
	catch (BGAPI2::Exceptions::IException& ex)
	{
		CString str16;
		str16.Format(_T("ExceptionType:%s! ErrorDescription:%s in function:%s"), ex.GetType(), ex.GetErrorDescription(), ex.GetFunctionName());
		AfxMessageBox(str16);
		return false;
	}
}

bool CCamBaumer_12M::Start()
{
	USES_CONVERSION;
	if (m_pDevice != NULL)
	{
		try
		{

			m_pDevice->GetRemoteNode("AcquisitionStart")->Execute();
		}
		catch (BGAPI2::Exceptions::IException& ex)
		{
			CString str1;
			str1.Format(_T("ExceptionType:%s! ErrorDescription:%s in function:%s"), ex.GetType(), ex.GetErrorDescription(), ex.GetFunctionName());
			AfxMessageBox(str1);
			return false;
		}
	}
	return true;
}

bool CCamBaumer_12M::Stop()
{
	if (m_pDevice != NULL)
	{
		try
		{
			//m_pDataStream->StopAcquisition();
			m_pDevice->GetRemoteNode("AcquisitionStop")->Execute();
// 			if (m_pBitmap != NULL)
// 			{
// 				delete m_pBitmap;
// 				m_pBitmap = NULL;
// 			}
		}
		catch (BGAPI2::Exceptions::IException& ex)
		{
			CString str1;
			str1.Format(_T("ExceptionType:%s! ErrorDescription:%s in function:%s"), ex.GetType(), ex.GetErrorDescription(), ex.GetFunctionName());
			AfxMessageBox(str1);
		}
	}
}

bool CCamBaumer_12M::UninitDevice()
{

	USES_CONVERSION;
	try
	{
		if (m_pDevice->GetRemoteNodeList()->GetNodePresent("AcquisitionAbort"))
		{
			m_pDevice->GetRemoteNode("AcquisitionAbort")->Execute();
		}
		m_pDevice->GetRemoteNode("AcquisitionStop")->Execute();
	}
	catch (BGAPI2::Exceptions::IException& ex)
	{
		CString str1;
		str1.Format(_T("ExceptionType:%s! ErrorDescription:%s in function:%s"), ex.GetType(), ex.GetErrorDescription(), ex.GetFunctionName());
		AfxMessageBox(str1);
		return false;
	}

	//STOP DataStream acquisition
	try
	{
		m_pDataStream->StopAcquisition();
		m_pBufferList->DiscardAllBuffers();
	}
	catch (BGAPI2::Exceptions::IException& ex)
	{
		CString str2;
		str2.Format(_T("ExceptionType:%s! ErrorDescription:%s in function:%s"), ex.GetType(), ex.GetErrorDescription(), ex.GetFunctionName());
		AfxMessageBox(str2);
		return false;
	}
	//Release buffers
	try
	{
		while (m_pBufferList->size() > 0)
		{
			m_pBuffer = m_pBufferList->begin()->second;
			m_pBufferList->RevokeBuffer(m_pBuffer);
			delete m_pBuffer;
		}

		m_pDataStream->Close();
		m_pDevice->Close();
// 		m_pInterface->Close();
// 		m_pSystem->Close();
// 		BGAPI2::SystemList::ReleaseInstance();
	}
	catch (BGAPI2::Exceptions::IException& ex)
	{
		CString str3;
		str3.Format(_T("ExceptionType:%s! ErrorDescription:%s in function:%s"), ex.GetType(), ex.GetErrorDescription(), ex.GetFunctionName());
		AfxMessageBox(str3);
		return false;
	}
	return true;
}

bool CCamBaumer_12M::SetExposureTime(double iExposureTime)
{
	if (m_pDevice != NULL)
	{
		if (m_pDevice->GetRemoteNodeList()->GetNodePresent("ExposureTime"))
		{
			m_pDevice->GetRemoteNode("ExposureTime")->SetDouble(iExposureTime);
		}
		else if (m_pDevice->GetRemoteNodeList()->GetNodePresent("ExposureTimeAbs"))
		{
			m_pDevice->GetRemoteNode("ExposureTimeAbs")->SetDouble(iExposureTime);
		}
	}

	return true;
}

bool CCamBaumer_12M::SetGain(double dGain)
{
	if (m_pDevice != NULL)
	{
		if (m_pDevice->GetRemoteNodeList()->GetNodePresent("Gain"))
		{
			m_pDevice->GetRemoteNode("Gain")->SetDouble(dGain);
		}
		else if (m_pDevice->GetRemoteNodeList()->GetNodePresent("GainAbs"))
		{
			m_pDevice->GetRemoteNode("GainAbs")->SetDouble(dGain);
		}
		return true;
	}
	return false;
}


bool CCamBaumer_12M::SetTriggerSource(CString strText)
{
 	if(m_pDevice != NULL)
 	{
 	 	char szChar[256] = {0};
 	 	wcstombs(szChar,strText,strText.GetLength());
 	 	BGAPI2::String strBau = szChar;
 	 	m_pDevice->GetRemoteNode("TriggerSource")->SetString(szChar);
		return true;
 	}
	return false;
}
bool CCamBaumer_12M::SetTriggerActivation(CString strText)
{
	USES_CONVERSION;
	if(m_pDevice != NULL)
	{
	 	m_pDevice->GetRemoteNode("TriggerActivation")->SetString(W2A(strText));
	}
	return false;
}
bool CCamBaumer_12M::SetTriggerEnable(bool bEnable)
{
	if (m_pDevice != NULL)
	{
		if (bEnable)
		{
			m_pDevice->GetRemoteNode("TriggerMode")->SetString("On");
			//m_bEnabled = true;
		}
		else
		{
			m_pDevice->GetRemoteNode("TriggerMode")->SetString("Off");
			//m_bEnabled = false;
		}
	}
	return false;
}

bool CCamBaumer_12M::SetTriggerDelay(int iTime)
{
	if (m_pDevice != NULL)
	{
		m_pDevice->GetRemoteNode("TriggerDelay")->SetDouble(iTime);
		return true;
	}
	return false;
}

bool CCamBaumer_12M::SoftWareTriggerOnce()
{
	if (m_pDevice != NULL)
	{
		if (m_pDevice->GetRemoteNode("TriggerSource")->GetString() == "Software")
		{
			m_pDevice->GetRemoteNode("TriggerSoftware")->Execute();
		}
		else if (m_pDevice->GetRemoteNode("TriggerSource")->GetString() == "SoftwareTrigger")
		{
			m_pDevice->GetRemoteNode("TriggerSoftware")->Execute();
		}
		return true;
	}
	return false;
}