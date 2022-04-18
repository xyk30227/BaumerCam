
// GigeDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GigeDemo.h"
#include "GigeDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGigeDemoDlg 对话框




CGigeDemoDlg::CGigeDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGigeDemoDlg::IDD, pParent)
	,m_pSystemList(NULL)
	,m_pSystem(NULL)
	,m_pInterfaceList(NULL)
	,m_pInterface(NULL)
	,m_pDeviceList(NULL)
	,m_bSaveImage(false)
	,m_pBitmap(NULL)
	,m_bEnabled(false)
	,m_bSwTrigger(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGigeDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDTTYPE, m_edtCameraType);
	DDX_Control(pDX, IDC_SLDEXPOSURE, m_sldShutter);
	DDX_Control(pDX, IDC_EDTEXPOSURE, m_edtShutter);
	DDX_Control(pDX, IDC_STCMAXEXPOSURE, m_stcMaxShutter);
	DDX_Control(pDX, IDC_STCMINEXPOSURE, m_stcMinShutter);
	DDX_Control(pDX, IDC_SLDGAIN, m_sldGain);
	DDX_Control(pDX, IDC_EDTGAIN, m_edtGain);
	DDX_Control(pDX, IDC_STCMAXGAIN, m_stcMaxGain);
	DDX_Control(pDX, IDC_STCMINGAIN, m_stcMinGain);
	DDX_Control(pDX, IDC_EDTPATH, m_edtPath);
	DDX_Control(pDX, IDC_SPNEXPOSURE, m_spnShutter);
	DDX_Control(pDX, IDC_CHKTRIGGERENABLED, m_chkTrgEnabled);
	DDX_Control(pDX, IDC_CMBTSOURCE, m_cmbTrgSource);
	DDX_Control(pDX, IDC_CMBTACTIVATION, m_cmbTrgMode);
	DDX_Control(pDX, IDC_SPNDELAY, m_spnDelay);
	DDX_Control(pDX, IDC_EDTTDELAY, m_edtDelay);
	DDX_Control(pDX, IDC_STCPICTURE, m_stcPicture);
	DDX_Control(pDX, IDC_EDTWIDTH, m_edtWidth);
	DDX_Control(pDX, IDC_EDTHEIGHT, m_edtHeight);
	DDX_Control(pDX, IDC_EDTOFFSETX, m_edtOffsetX);
	DDX_Control(pDX, IDC_EDTOFFSETY, m_edtOffsetY);
	DDX_Control(pDX, IDC_STCWMIN, m_stcWMin);
	DDX_Control(pDX, IDC_STCWMAX, m_stcWMax);
	DDX_Control(pDX, IDC_STCHMIN, m_stcHMin);
	DDX_Control(pDX, IDC_STCHMAX, m_stcHMax);
	DDX_Control(pDX, IDC_STCOXMIN, m_stcOXMin);
	DDX_Control(pDX, IDC_STCOXMAX, m_stcOXMax);
	DDX_Control(pDX, IDC_STCOYMIN, m_stcOYMin);
	DDX_Control(pDX, IDC_STCOYMAX, m_stcOYMax);
}

BEGIN_MESSAGE_MAP(CGigeDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNPATH, &CGigeDemoDlg::OnBnClickedBtnpath)
	//ON_BN_CLICKED(IDOK, &CGigeDemoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTNPLAY, &CGigeDemoDlg::OnBnClickedBtnplay)
	ON_BN_CLICKED(IDC_BTNPAUSE, &CGigeDemoDlg::OnBnClickedBtnpause)
	ON_BN_CLICKED(IDC_BTNSNAP, &CGigeDemoDlg::OnBnClickedBtnsnap)
	ON_BN_CLICKED(IDCANCEL, &CGigeDemoDlg::OnBnClickedCancel)
	ON_BN_CLICKED(ID_BTNINITIALIZE, &CGigeDemoDlg::OnBnClickedBtninitialize)
	ON_BN_CLICKED(IDC_BTNSWTEXCUTE, &CGigeDemoDlg::OnBnClickedBtnswtexcute)
	ON_BN_CLICKED(IDC_BTNEXPOSURE, &CGigeDemoDlg::OnBnClickedBtnexposure)
	ON_BN_CLICKED(IDC_BTNGAIN, &CGigeDemoDlg::OnBnClickedBtngain)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLDEXPOSURE, &CGigeDemoDlg::OnNMCustomdrawSldexposure)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLDGAIN, &CGigeDemoDlg::OnNMCustomdrawSldgain)
	ON_CBN_SELCHANGE(IDC_CMBTSOURCE, &CGigeDemoDlg::OnCbnSelchangeCmbtsource)
	ON_CBN_SELCHANGE(IDC_CMBTACTIVATION, &CGigeDemoDlg::OnCbnSelchangeCmbtactivation)
	ON_BN_CLICKED(IDC_BTNDELAY, &CGigeDemoDlg::OnBnClickedBtndelay)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPNEXPOSURE, &CGigeDemoDlg::OnDeltaposSpnexposure)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPNDELAY, &CGigeDemoDlg::OnDeltaposSpndelay)
	ON_BN_CLICKED(IDC_CHKTRIGGERENABLED, &CGigeDemoDlg::OnBnClickedChktriggerenabled)
// 	ON_BN_CLICKED(IDC_BUTTON1, &CGigeDemoDlg::OnBnClickedButton1)
// 	ON_BN_CLICKED(IDC_BUTTON2, &CGigeDemoDlg::OnBnClickedButton2)
// 	ON_BN_CLICKED(IDC_BUTTON3, &CGigeDemoDlg::OnBnClickedButton3)
// 	ON_BN_CLICKED(IDC_BUTTON5, &CGigeDemoDlg::OnBnClickedButton5)
// 	ON_BN_CLICKED(IDC_BUTTON6, &CGigeDemoDlg::OnBnClickedButton6)
// 	ON_BN_CLICKED(IDC_BUTTON7, &CGigeDemoDlg::OnBnClickedButton7)
// 	ON_BN_CLICKED(IDC_BUTTON8, &CGigeDemoDlg::OnBnClickedButton8)
// 	ON_BN_CLICKED(IDC_BUTTON9, &CGigeDemoDlg::OnBnClickedButton9)
// 
// 	ON_BN_CLICKED(IDC_BUTTON10, &CGigeDemoDlg::OnBnClickedButton10)
// 	
// 	
// 	ON_BN_CLICKED(IDC_BUTTON12, &CGigeDemoDlg::OnBnClickedButton12)
// 	ON_BN_CLICKED(IDC_BUTTON13, &CGigeDemoDlg::OnBnClickedButton13)
// 	ON_BN_CLICKED(IDC_BUTTON14, &CGigeDemoDlg::OnBnClickedButton14)

	ON_BN_CLICKED(IDC_BUTTON_INIT_SYS, &CGigeDemoDlg::OnBnClickedButtonInitSys)
	ON_BN_CLICKED(IDC_BUTTON_INIT_DLP, &CGigeDemoDlg::OnBnClickedButtonInitDlp)
END_MESSAGE_MAP()




void chr2wch(const char* buffer, CString wBuf)
{
	//wBuf = new wchar_t[wlen + 1];

	//MultiByteToWideChar(CP_ACP, 0, (const char*)buffer, int(len), wBuf, int(wlen));

	int len = (int)MultiByteToWideChar(CP_ACP,0,buffer,strlen(buffer),0,0);
	len = (int)MultiByteToWideChar(CP_ACP,0,buffer,strlen(buffer) ,wBuf.GetBuffer(len+1),len+1);
	//wBuf.ReleaseBuffer(len);
	//m_edtCameraType.SetWindowTextW(camType);

} 
//CALLBACK FUNCTION
//==================
void BGAPI2CALL BufferHandler( void * callBackOwner, Buffer * pBufferFilled )
{
	CGigeDemoDlg* pDlg = (CGigeDemoDlg*)callBackOwner;
	unsigned char* imagebuffer = NULL;
	USES_CONVERSION;
	try
	{
		if(pBufferFilled == NULL)
		{
			
		}
		else if(pBufferFilled->GetIsIncomplete() == true)
		{
			// queue buffer again
			pBufferFilled->QueueBuffer();
		}
		else
		{
			//std::cout << " Image " << std::setw(5) << pBufferFilled->GetFrameID() << " received in memory address " << pBufferFilled->GetMemPtr() << std::endl;
			int width = 0, height = 0;
			width = (int)pBufferFilled->GetWidth();
			height = (int)pBufferFilled->GetHeight();


			imagebuffer = (BYTE*)((bo_int64)pBufferFilled->GetMemPtr()+pBufferFilled->GetImageOffset());

			if(pDlg->m_bSaveImage &&!pDlg->m_strDirectory.IsEmpty())
			{
				CTime time = CTime::GetCurrentTime(); 
		        CString strtime;
		        strtime.Format(_T("\\%4d%2d%2d%2d%2d%2d"),time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
		        CString  strpath = pDlg->m_strDirectory+strtime+".bmp";
		        pDlg->SaveImage(strpath, imagebuffer,width,height);
		        pDlg->m_bSaveImage = false;
			}

			Gdiplus::Rect rc = Gdiplus::Rect(0,0,width,height);
			if(pDlg->m_pBitmap == NULL)
			{
					pDlg->m_pBitmap = new Gdiplus::Bitmap(width,height,PixelFormat8bppIndexed);
			}
			Gdiplus::BitmapData lockedbits;
			Gdiplus::ColorPalette * pal = (Gdiplus::ColorPalette*)new BYTE[sizeof(Gdiplus::ColorPalette)+255*sizeof(Gdiplus::ARGB)];
			pal->Count=256;
			for(UINT i=0;i<256;i++)
			{
				UINT color=i*65536+i*256+i;
				color= color|0xFF000000;
				pal->Entries[i]=color;
			}
			pDlg->m_pBitmap->SetPalette(pal);
			Gdiplus::Status ret = pDlg->m_pBitmap->LockBits(&rc,Gdiplus::ImageLockModeWrite,PixelFormat8bppIndexed,&lockedbits);
			BYTE* pixels = (BYTE*)lockedbits.Scan0;
			BYTE* src = (BYTE*)imagebuffer;
			for (int row = 0; row < height; ++row) 
			{
				CopyMemory(pixels, src, lockedbits.Stride);
				pixels += width;
				src += width;
			}
			pDlg->m_pBitmap->UnlockBits(&lockedbits);
		
			HDC hDC = ::GetDC(pDlg->m_stcPicture.m_hWnd);
			
			//	//
			Gdiplus::Graphics GdiplusDC(hDC);
			//
			//	// 
			CRect rcControl;
			pDlg->m_stcPicture.GetWindowRect(&rcControl);
			Gdiplus::Rect rtImage(0,0,rcControl.Width(),rcControl.Height());
			GdiplusDC.DrawImage(pDlg->m_pBitmap,rtImage,0,0,width,height, Gdiplus::UnitPixel);
			
			delete []pal;
				
			
			::ReleaseDC(pDlg->m_stcPicture.m_hWnd,hDC);
				
			delete pDlg->m_pBitmap ;
			pDlg->m_pBitmap =NULL;

			// queue buffer again
			pBufferFilled->QueueBuffer();
		}
	}
	catch (BGAPI2::Exceptions::IException& ex)
	{
		CString str;
		str.Format(_T("ExceptionType:%s! ErrorDescription:%s in function:%s"),ex.GetType(),ex.GetErrorDescription(),ex.GetFunctionName());
		//MessageBox(str);
	}
	//return;
}
BOOL CGigeDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//设置所用相机
	SetCamMode(CAM_BAUMER_12M);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGigeDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGigeDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGigeDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGigeDemoDlg::OnBnClickedBtnpath()
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_FileDir;  
	BROWSEINFO bi;  
	ZeroMemory(&bi, sizeof(BROWSEINFO));  
	bi.hwndOwner = m_hWnd;  
	bi.ulFlags   = BIF_RETURNONLYFSDIRS;  
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);  
	BOOL bRet = FALSE;  
	wchar_t szFolder[MAX_PATH*2];  
	szFolder[0] =_T( '/0');  
	if (pidl)  
	{  
		if (SHGetPathFromIDList(pidl, szFolder))    
			bRet = TRUE;  
		IMalloc *pMalloc = NULL;  
		if (SUCCEEDED(SHGetMalloc(&pMalloc)) && pMalloc)  
		{   
			pMalloc->Free(pidl);   
			pMalloc->Release();  
		}  
	}  
	m_FileDir = szFolder; 
	TRACE(_T("/n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&/n"));  
	TRACE(m_FileDir);  
	TRACE(_T("/n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&/n"));  
	if(!m_FileDir.IsEmpty())
	{
		m_edtPath.SetWindowText(m_FileDir);
	}
}




void CGigeDemoDlg::OnBnClickedBtnplay()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_iOnlineCamNum; i++)
	{
		m_pBaumerCam[i]->Start();
	}	
}


void CGigeDemoDlg::OnBnClickedBtnpause()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_iOnlineCamNum; i++)
	{
		m_pBaumerCam[i]->Stop();
	}
}


void CGigeDemoDlg::OnBnClickedBtnsnap()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_bSaveImage)
	{
		m_bSaveImage = true;
		//CString strPath;
		m_edtPath.GetWindowText(m_strDirectory);
	}	
}


void CGigeDemoDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_iOnlineCamNum; i++)
	{
		m_pBaumerCam[i]->UninitDevice();
	}
	
	CDialogEx::OnCancel();
}


void CGigeDemoDlg::OnBnClickedBtninitialize()
{
	USES_CONVERSION;
	//OPEN THE FIRST CAMERA(Device) IN THE LIST	
	CString strID;
	int iHeight, iWidth;

	BGAPI2::Device *m_pDevice;
	
	for (int i = 0; i < m_iOnlineCamNum; i++)
	{
		if (i==0)
			m_bCamReady = m_pBaumerCam[i]->InitDevice(m_pDeviceList, strID, iWidth, iHeight, m_pDevice);
		else
		{
			BGAPI2::Device *pDevice;
			m_pBaumerCam[i]->InitDevice(m_pDeviceList, strID, iWidth, iHeight, pDevice);
			pDevice->Close();
		}			
	}

	if (!m_bCamReady)
	{
		m_pInterface->Close();
		m_pSystem->Close();
		BGAPI2::SystemList::ReleaseInstance();
	}

	CString strType;
	strType.Format(_T("GigEDemo %s Initialized successfully!"), A2W(m_pDevice->second->GetModel()));
	this->SetWindowTextW(strType);
	m_edtCameraType.SetWindowTextW(A2W(m_pDevice->second->GetModel()));

	//Shutter Control Initial
	long iShutter, iMaxShutter, iMinShutter;
	CString strShutter, strMaxShutter, strMinShutter;

	if (m_pDevice->GetRemoteNodeList()->GetNodePresent("ExposureTime"))
	{
		iShutter = (long)m_pDevice->GetRemoteNode("ExposureTime")->GetDouble();
		iMinShutter = (long)m_pDevice->GetRemoteNode("ExposureTime")->GetDoubleMin();
		iMaxShutter = (long)m_pDevice->GetRemoteNode("ExposureTime")->GetDoubleMax();
	}
	else if (m_pDevice->GetRemoteNodeList()->GetNodePresent("ExposureTimeAbs"))
	{
		iShutter = (long)m_pDevice->GetRemoteNode("ExposureTimeAbs")->GetDouble();
		iMinShutter = (long)m_pDevice->GetRemoteNode("ExposureTimeAbs")->GetDoubleMin();
		iMaxShutter = (long)m_pDevice->GetRemoteNode("ExposureTimeAbs")->GetDoubleMax();
	}

	strMinShutter.Format(_T("%ld"), iMinShutter);
	strMaxShutter.Format(_T("%ld"), iMaxShutter);
	strShutter.Format(_T("%ld"), iShutter);
	m_sldShutter.SetRange(iMinShutter, iMaxShutter);
	m_sldShutter.SetPos(iShutter);
	m_edtShutter.SetWindowTextW(strShutter);
	m_stcMaxShutter.SetWindowTextW(strMaxShutter);
	m_stcMinShutter.SetWindowTextW(strMinShutter);


	//Gain Control Initial
	float fGain, fMinGain, fMaxGain;
	long nMax, nMin, nCur;
	CString strGain, strMinGain, strMaxGain;
	if (m_pDevice->GetRemoteNodeList()->GetNodePresent("Gain"))
	{
		fGain = (float)m_pDevice->GetRemoteNode("Gain")->GetDouble();
		fMinGain = (float)m_pDevice->GetRemoteNode("Gain")->GetDoubleMin();
		fMaxGain = (float)m_pDevice->GetRemoteNode("Gain")->GetDoubleMax();
	}
	else if (m_pDevice->GetRemoteNodeList()->GetNodePresent("GainAbs"))
	{
		fGain = (float)m_pDevice->GetRemoteNode("GainAbs")->GetDouble();
		fMinGain = (float)m_pDevice->GetRemoteNode("GainAbs")->GetDoubleMin();
		fMaxGain = (float)m_pDevice->GetRemoteNode("GainAbs")->GetDoubleMax();
	}
	nMax = int(fMaxGain * 100);
	nMin = int(fMinGain * 100);
	nCur = int(fGain * 100);

	m_sldGain.SetRange(nMin, nMax);
	m_sldGain.SetPos(nCur);
	strGain.Format(_T("%.2f"), fGain);
	strMinGain.Format(_T("%.2f"), fMinGain);
	strMaxGain.Format(_T("%.2f"), fMaxGain);

	m_stcMinGain.SetWindowText(strMinGain);
	m_stcMaxGain.SetWindowText(strMaxGain);
	m_edtGain.SetWindowText(strGain);

	//
	////
	//Trigger Control Initial
	//Trigger Source
	String strTrgStatus;
	strTrgStatus = m_pDevice->GetRemoteNode("TriggerMode")->GetString();
	if (strTrgStatus == "On")
	{
		m_chkTrgEnabled.SetCheck(1);
		m_bEnabled = true;
		m_pDevice->GetRemoteNode("TriggerMode")->SetString("On");
	}
	else
	{
		m_chkTrgEnabled.SetCheck(0);
		m_bEnabled = false;
		m_pDevice->GetRemoteNode("TriggerMode")->SetString("Off");
	}

	BGAPI2::Node * pNodeTrgSource = NULL;
	for (bo_uint64 i = 0; i < m_pDevice->GetRemoteNode("TriggerSource")->GetEnumNodeList()->GetNodeCount(); i++)
	{
		pNodeTrgSource = m_pDevice->GetRemoteNode("TriggerSource")->GetEnumNodeList()->GetNodeByIndex(i);
		if ((pNodeTrgSource->GetImplemented() == true))
		{
			m_cmbTrgSource.AddString(A2W(pNodeTrgSource->GetValue()));
			if ((m_pDevice->GetRemoteNode("TriggerSource")->GetString() == "Software")
				|| (m_pDevice->GetRemoteNode("TriggerSource")->GetString() == "All")
				|| (m_pDevice->GetRemoteNode("TriggerSource")->GetString() == "Off")
				|| (m_pDevice->GetRemoteNode("TriggerSource")->GetString() == "Action1")
				|| (m_pDevice->GetRemoteNode("TriggerSource")->GetString() == "SoftwareTrigger"))
			{
				m_bSwTrigger = true;
			}
			else
			{
				m_bSwTrigger = false;
			}
			if (pNodeTrgSource->GetValue() == m_pDevice->GetRemoteNode("TriggerSource")->GetString())
			{
				m_cmbTrgSource.SelectString(0, A2W(pNodeTrgSource->GetValue()));
			}
		}
	}

	//TriggerActivation 
	BGAPI2::Node * pNodeTrgActivation = NULL;
	bo_uint64 x = m_pDevice->GetRemoteNode("TriggerActivation")->GetEnumNodeList()->GetNodeCount();
	for (bo_uint64 i = 0; i < m_pDevice->GetRemoteNode("TriggerActivation")->GetEnumNodeList()->GetNodeCount(); i++)
	{
		pNodeTrgActivation = m_pDevice->GetRemoteNode("TriggerActivation")->GetEnumNodeList()->GetNodeByIndex(i);
		if (!m_bSwTrigger && (pNodeTrgActivation->GetImplemented() == true))
		{
			m_cmbTrgMode.AddString(A2W(pNodeTrgActivation->GetValue()));
			if (pNodeTrgActivation->GetValue() == m_pDevice->GetRemoteNode("TriggerActivation")->GetString())
			{
				m_cmbTrgMode.SelectString(0, A2W(pNodeTrgActivation->GetValue()));
				//m_cmbTrgMode.GetWindowTextW();
			}
		}
		else
			m_cmbTrgMode.EnableWindow(false);
	}
	//TriggerDelay

	int iMaxTrgDelay, iMinTrgDelay, iTrgDelay;
	if (m_pDevice->GetRemoteNodeList()->GetNodePresent("TriggerDelay"))
	{
		iTrgDelay = (int)m_pDevice->GetRemoteNode("TriggerDelay")->GetDouble();
		iMaxTrgDelay = (int)m_pDevice->GetRemoteNode("TriggerDelay")->GetDoubleMax();
		iMinTrgDelay = (int)m_pDevice->GetRemoteNode("TriggerDelay")->GetDoubleMin();

		m_spnDelay.SetRange(iMinTrgDelay, iMaxTrgDelay);
		m_spnDelay.SetBuddy(&m_edtDelay);
		CString strDelay;
		strDelay.Format(_T("%d"), iTrgDelay);
		m_edtDelay.SetWindowText(strDelay);
		m_spnDelay.SetPos(iTrgDelay);
	}
	else
	{
		m_spnDelay.EnableWindow(FALSE);
		this->GetDlgItem(IDC_BTNDELAY)->EnableWindow(FALSE);
	}

	//ROI
	int width, height, offsetX, offsetY = 0;
	width = m_pDevice->GetRemoteNode("Width")->GetInt();
	CString strW, strH, strOX, strOY, strWMin, strWMax, strHMin, strHMax, strOXMin, strOXMax, strOYMin, strOYMax;
	strW.Format(_T("%d"), width);
	m_edtWidth.SetWindowTextW(strW);
	strWMin.Format(_T("%d"), m_pDevice->GetRemoteNode("Width")->GetIntMin());
	m_stcWMin.SetWindowTextW(strWMin);
	strWMax.Format(_T("%d"), m_pDevice->GetRemoteNode("Width")->GetIntMax());
	m_stcWMax.SetWindowTextW(strWMax);

	height = m_pDevice->GetRemoteNode("Height")->GetInt();
	strH.Format(_T("%d"), height);
	m_edtHeight.SetWindowTextW(strH);
	strHMin.Format(_T("%d"), m_pDevice->GetRemoteNode("Height")->GetIntMin());
	m_stcHMin.SetWindowTextW(strHMin);
	strHMax.Format(_T("%d"), m_pDevice->GetRemoteNode("Height")->GetIntMax());
	m_stcHMax.SetWindowTextW(strHMax);

	offsetX = m_pDevice->GetRemoteNode("OffsetX")->GetInt();
	strOX.Format(_T("%d"), offsetX);
	m_edtOffsetX.SetWindowTextW(strOX);
	strOXMin.Format(_T("%d"), m_pDevice->GetRemoteNode("OffsetX")->GetIntMin());
	m_stcOXMin.SetWindowTextW(strOXMin);
	strOXMax.Format(_T("%d"), m_pDevice->GetRemoteNode("OffsetX")->GetIntMax());
	m_stcOXMax.SetWindowTextW(strOXMax);

	offsetY = m_pDevice->GetRemoteNode("OffsetY")->GetInt();
	strOY.Format(_T("%d"), offsetY);
	m_edtOffsetY.SetWindowTextW(strOY);
	strOYMin.Format(_T("%d"), m_pDevice->GetRemoteNode("OffsetY")->GetIntMin());
	m_stcOYMin.SetWindowTextW(strOYMin);
	strOYMax.Format(_T("%d"), m_pDevice->GetRemoteNode("OffsetY")->GetIntMax());
	m_stcOYMax.SetWindowTextW(strOYMax);
}


void CGigeDemoDlg::OnBnClickedBtnswtexcute()
{
	// TODO: 在此添加控件通知处理程序代码
// 	if(m_pDevice->GetRemoteNode("TriggerSource")->GetString() == "Software" && m_bEnabled)
// 	{
// 		m_pDevice->GetRemoteNode("TriggerSoftware")->Execute();
// 	}
// 	else if(m_pDevice->GetRemoteNode("TriggerSource")->GetString() == "SoftwareTrigger" && m_bEnabled)
// 	{
// 		m_pDevice->GetRemoteNode("TriggerSoftware")->Execute();
// 	}
	if (m_bEnabled)
	{
		for (int i = 0; i < m_iOnlineCamNum; i++)
		{
			m_pBaumerCam[i]->SoftWareTriggerOnce();
		}
	}
}


void CGigeDemoDlg::OnBnClickedBtnexposure()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strShutter;
	m_edtShutter.GetWindowText(strShutter);
	int nShutter = _wtol(strShutter);
	m_sldShutter.SetPos(nShutter);

// 	if(m_pDevice != NULL)
// 	{
// 		if(m_pDevice->GetRemoteNodeList()->GetNodePresent("ExposureTime"))
// 		{
// 			m_pDevice->GetRemoteNode("ExposureTime")->SetDouble(nShutter);
// 		}
// 		else if(m_pDevice->GetRemoteNodeList()->GetNodePresent("ExposureTimeAbs"))
// 		{
// 			m_pDevice->GetRemoteNode("ExposureTimeAbs")->SetDouble(nShutter);
// 		}
// 		
// 	}
	for (int i = 0; i < m_iOnlineCamNum; i++)
	{
		m_pBaumerCam[i]->SetExposureTime(nShutter);
	}
	
}


void CGigeDemoDlg::OnBnClickedBtngain()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strGain;
	double   fGain;
	m_edtGain.GetWindowText(strGain);
	fGain= _wtof(strGain);
	m_sldGain.SetPos(int(100*fGain));
// 	if(m_pDevice != NULL)
// 	{
// 		if(m_pDevice->GetRemoteNodeList()->GetNodePresent("Gain"))
// 		{
// 			m_pDevice->GetRemoteNode("Gain")->SetDouble(fGain);
// 		}
// 		else if(m_pDevice->GetRemoteNodeList()->GetNodePresent("GainAbs"))
// 		{
// 			m_pDevice->GetRemoteNode("GainAbs")->SetDouble(fGain);
// 		}
// 	}
	for (int i = 0; i < m_iOnlineCamNum; i++)
	{
		m_pBaumerCam[i]->SetGain(fGain);
	}

}


void CGigeDemoDlg::OnNMCustomdrawSldexposure(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nPos = m_sldShutter.GetPos();
	CString strPos;
	strPos.Format(_T("%d"),nPos);
	m_edtShutter.SetWindowText(strPos);
// 	if(m_pDevice != NULL)
// 	{
// 		if(m_pDevice->GetRemoteNodeList()->GetNodePresent("ExposureTime"))
// 		{
// 			m_pDevice->GetRemoteNode("ExposureTime")->SetDouble(nPos);
// 		}
// 		else if(m_pDevice->GetRemoteNodeList()->GetNodePresent("ExposureTimeAbs"))
// 		{
// 			m_pDevice->GetRemoteNode("ExposureTimeAbs")->SetDouble(nPos);
// 		}
// 	}
	for (int i = 0; i < m_iOnlineCamNum; i++)
	{
		m_pBaumerCam[i]->SetExposureTime(nPos);
	}
	*pResult = 0;
}


void CGigeDemoDlg::OnNMCustomdrawSldgain(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nPos = m_sldGain.GetPos();
	float fGain = (float)nPos/100;
	CString strPos;
	strPos.Format(_T("%.2f"),(float)nPos/100);
	m_edtGain.SetWindowText(strPos);
// 	if(m_pDevice != NULL)
// 	{
// 		if(m_pDevice->GetRemoteNodeList()->GetNodePresent("Gain"))
// 		{
// 			m_pDevice->GetRemoteNode("Gain")->SetDouble(fGain);
// 		}
// 	    else if(m_pDevice->GetRemoteNodeList()->GetNodePresent("GainAbs"))
// 		{
// 			m_pDevice->GetRemoteNode("Gain")->SetDouble(fGain);
// 	    }
// 	}
	for (int i = 0; i < m_iOnlineCamNum; i++)
	{
		m_pBaumerCam[i]->SetGain(fGain);
	}
	*pResult = 0;;
}


void CGigeDemoDlg::OnCbnSelchangeCmbtsource()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	int  nPos = m_cmbTrgSource.GetCurSel();
	CString strText;
	m_cmbTrgSource.GetLBText(nPos,strText);
	if((strText == _T("Software"))||(strText == _T("SoftwareTrigger")))
	{
		m_bSwTrigger = true;
	}
// 	if(m_pDevice != NULL)
// 	{
// 		char szChar[256] = {0};
// 		wcstombs(szChar,strText,strText.GetLength());
// 		BGAPI2::String strBau = szChar;
// 		m_pDevice->GetRemoteNode("TriggerSource")->SetString(szChar);		
// 	}
	for (int i = 0; i < m_iOnlineCamNum; i++)
	{
		m_pBaumerCam[i]->SetTriggerSource(strText);
	}
}


void CGigeDemoDlg::OnCbnSelchangeCmbtactivation()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	int  nPos = m_cmbTrgSource.GetCurSel();
	CString strText;
	m_cmbTrgSource.GetLBText(nPos,strText);
// 	if(m_pDevice != NULL)
// 	{
// 		m_pDevice->GetRemoteNode("TriggerActivation")->SetString(W2A(strText));
// 	}
	for (int i = 0; i < m_iOnlineCamNum; i++)
	{
		m_pBaumerCam[i]->SetTriggerActivation(strText);
	}
}


void CGigeDemoDlg::OnBnClickedBtndelay()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strDelay;
	m_edtDelay.GetWindowText(strDelay);
	int nDelay = _wtol(strDelay);
// 	if(m_pDevice != NULL)
// 	{
// 		m_pDevice->GetRemoteNode("TriggerDelay")->SetDouble(nDelay);
// 	}

	for (int i = 0; i < m_iOnlineCamNum; i++)
	{
		m_pBaumerCam[i]->SetTriggerDelay(nDelay);
	}
}


void CGigeDemoDlg::OnDeltaposSpnexposure(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CString strShutter;
	m_edtShutter.GetWindowText(strShutter);

	if(pNMUpDown->iDelta > 0)
	{
		if(!strShutter.IsEmpty())
		{
			int nvalue = _wtol(strShutter);
			nvalue += 1;
			CString  strspn;
			strspn.Format(_T("%d"),nvalue);
			m_edtShutter.SetWindowText(strspn);
		}
	}
	else if(pNMUpDown->iDelta < 0)
	{
		if(!strShutter.IsEmpty())
		{
			int nvalue = _wtol(strShutter);
			nvalue -= 1;
			if(nvalue <= 0)
			{
				nvalue = 0;
			}
			CString  strspn;
			strspn.Format(_T("%d"),nvalue);
			m_edtShutter.SetWindowText(strspn);
		}
	}
	*pResult = 0;
}


void CGigeDemoDlg::OnDeltaposSpndelay(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CString strDelay;
	m_edtDelay.GetWindowText(strDelay);

	if(pNMUpDown->iDelta > 0)
	{
		if(!strDelay.IsEmpty())
		{
			int nvalue = _wtol(strDelay);
			nvalue += 1;
			CString  strspn;
			strspn.Format(_T("%d"),nvalue);
			m_edtDelay.SetWindowText(strspn);
		}
	}
	else if(pNMUpDown->iDelta < 0)
	{
		if(!strDelay.IsEmpty())
		{
			int nvalue = _wtol(strDelay);
			nvalue -= 1;
			if(nvalue <= 0)
			{
				nvalue = 0;
			}
			CString  strspn;
			strspn.Format(_T("%d"),nvalue);
			m_edtDelay.SetWindowText(strspn);
		}
	}
	*pResult = 0;
}
bool    CGigeDemoDlg::SaveImage(CString str,BYTE* bdata,int width,int height)
{
		//if(!m_Camera) return 0;
	if (str.IsEmpty()) return false;
	/*long x = 0, y = 0, width = 0, height = 0;
	m_Camera->GetProperty()->GetROI(x, y, width, height);*/
	//m_Camera->GetProperty()->
	//if (m_Width <= 0 || m_Height <= 0) return 0;

	HANDLE hFile = CreateFile(str,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	//DWORD dwError = GetLastError();
	if (!hFile || hFile == INVALID_HANDLE_VALUE) 
		return false;
	
	// 
	BITMAPFILEHEADER	FileHeader;
	BITMAPINFOHEADER	InfoHeader;
	RGBQUAD rgbQuad[256];

	DWORD dwImageSize				= width*height;
	FileHeader.bfType				= 0x4D42; // "BM"
	FileHeader.bfSize				= sizeof(FileHeader) + sizeof(InfoHeader) + dwImageSize;
	FileHeader.bfReserved1			= FileHeader.bfReserved2 = 0;
	FileHeader.bfOffBits			= sizeof(FileHeader) + sizeof(InfoHeader);
	
	ZeroMemory(&InfoHeader, sizeof(InfoHeader));
	InfoHeader.biWidth				= width;
	InfoHeader.biHeight				= -height;
	InfoHeader.biSizeImage			= dwImageSize;
	InfoHeader.biBitCount			= 8;
	InfoHeader.biCompression		= BI_RGB;
	InfoHeader.biPlanes				= 1;
	InfoHeader.biSize				= sizeof(BITMAPINFOHEADER);
	InfoHeader.biXPelsPerMeter		= 0xEC4;
	InfoHeader.biYPelsPerMeter		= 0xEC4;

	for ( int i=0;i<256; i++ )
	{
		rgbQuad[i].rgbBlue = (BYTE)i;
		rgbQuad[i].rgbGreen = (BYTE)i;
		rgbQuad[i].rgbRed = (BYTE)i;
		rgbQuad[i].rgbReserved = 0;
	}

	DWORD Written;
	WriteFile(hFile, (LPVOID)&FileHeader,sizeof(BITMAPFILEHEADER),&Written, NULL);
	WriteFile(hFile, (LPVOID)&InfoHeader,sizeof(BITMAPINFOHEADER),&Written, NULL);
	WriteFile(hFile, (LPVOID)rgbQuad,256*sizeof(RGBQUAD),&Written,NULL);
	BYTE* src = bdata;
	//int stride = m_Width*4;
	

	//DWORD bytes = m_Width * 4;
	//for (unsigned long y = 0; y < NHEIGHT; y++) {
	WriteFile(hFile, (LPVOID)src,dwImageSize,&Written,NULL);
	//}
	CloseHandle(hFile);
	return true;
}

void CGigeDemoDlg::OnBnClickedChktriggerenabled()
{
	// TODO: 在此添加控件通知处理程序代码
// 	if(m_pDevice != NULL)
// 	{
// 		if( m_chkTrgEnabled.GetCheck()== 1)
// 		{
// 			m_pDevice->GetRemoteNode("TriggerMode")->SetString("On"); 
// 			m_bEnabled = true;
// 		}
// 		else
// 		{
// 			m_pDevice->GetRemoteNode("TriggerMode")->SetString("Off");
// 			m_bEnabled = false;
// 		}
// 	}

	if (m_chkTrgEnabled.GetCheck() == 1)
	{
		//m_pDevice->GetRemoteNode("TriggerMode")->SetString("On");
		m_bEnabled = true;
	}
	else
	{
		//m_pDevice->GetRemoteNode("TriggerMode")->SetString("Off");
		m_bEnabled = false;
	}

	for (int i = 0; i < m_iOnlineCamNum; i++)
	{
		m_pBaumerCam[i]->SetTriggerEnable(m_bEnabled);
	}

}


// void CGigeDemoDlg::OnBnClickedButton1()
// {
// 	// TODO: 在此添加控件通知处理程序代码
// 	CString strWidth;
// 	m_edtWidth.GetWindowTextW(strWidth);
// 	int nROIW = 0;
// 	
// 	if(m_pDevice != NULL)
// 	{
// 		m_pDataStream->StopAcquisition();
// 		m_pDevice->GetRemoteNode("AcquisitionStop")->Execute();
// 		if(m_pBitmap != NULL)
// 		{
// 			delete m_pBitmap;
// 			m_pBitmap = NULL;
// 		}
// 	}
// 	else
// 		return;
// 
// 	int ntextW = _wtoi(strWidth);
// 
// 	int nWidthMin = m_pDevice->GetRemoteNode("Width")->GetIntMin();
// 	int nWidthMax = m_pDevice->GetRemoteNode("Width")->GetIntMax();
// 	int nWidthInc = m_pDevice->GetRemoteNode("Width")->GetIntInc();
// 
// 	if(ntextW < nWidthMin)
// 		nROIW = nWidthMin;
// 	else if(ntextW > nWidthMax)
// 		nROIW = nWidthMax;
// 	else
// 		nROIW = ntextW;
// 
// 	if(nROIW % nWidthInc != 0)
// 		nROIW = ((int)(nROIW/nWidthInc) + 1) * nWidthInc;
// 	CString strW;
// 	strW.Format(_T("%d"),nROIW);
// 	m_edtWidth.SetWindowTextW(strW);
// 
// 	m_pDevice->GetRemoteNode("Width")->SetInt(nROIW);
// 
// 	int offsetX,offsetY = 0;
// 	CString strOX,strOXMin,strOXMax;
// 	offsetX = m_pDevice->GetRemoteNode("OffsetX")->GetInt();
// 	strOX.Format(_T("%d"),offsetX);
// 	m_edtOffsetX.SetWindowTextW(strOX);
// 	strOXMin.Format(_T("%d"),m_pDevice->GetRemoteNode("OffsetX")->GetIntMin());
// 	m_stcOXMin.SetWindowTextW(strOXMin);
// 	strOXMax.Format(_T("%d"),m_pDevice->GetRemoteNode("OffsetX")->GetIntMax());
// 	m_stcOXMax.SetWindowTextW(strOXMax);
// 		
// 
// 	m_pDataStream->StartAcquisitionContinuous();
// 	m_pDevice->GetRemoteNode("AcquisitionStart")->Execute();
// 	
// }
// 
// 
// void CGigeDemoDlg::OnBnClickedButton2()
// {
// 	// TODO: 在此添加控件通知处理程序代码
// 	CString strHeight;
// 	m_edtHeight.GetWindowTextW(strHeight);
// 	int nROIH = 0;
// 	
// 	if(m_pDevice != NULL)
// 	{
// 		m_pDataStream->StopAcquisition();
// 		m_pDevice->GetRemoteNode("AcquisitionStop")->Execute();
// 		if(m_pBitmap != NULL)
// 		{
// 			delete m_pBitmap;
// 			m_pBitmap = NULL;
// 		}
// 	}
// 	else
// 		return;
// 
// 	int ntextH = _wtoi(strHeight);
// 
// 	int nHeightMin = m_pDevice->GetRemoteNode("Height")->GetIntMin();
// 	int nHeightMax = m_pDevice->GetRemoteNode("Height")->GetIntMax();
// 	int nHeightInc = m_pDevice->GetRemoteNode("Height")->GetIntInc();
// 
// 	if(ntextH < nHeightMin)
// 		nROIH = nHeightMin;
// 	else if(ntextH > nHeightMax)
// 		nROIH = nHeightMax;
// 	else
// 		nROIH = ntextH;
// 
// 	if(nROIH % nHeightInc != 0)
// 		nROIH = ((int)(nROIH/nHeightInc) + 1) * nHeightInc;
// 	CString strH;
// 	strH.Format(_T("%d"),nROIH);
// 	m_edtHeight.SetWindowTextW(strH);
// 	m_pDevice->GetRemoteNode("Height")->SetInt(nROIH);
// 
// 	int offsetY= 0;
// 	CString strOY,strOYMin,strOYMax;
// 	offsetY = m_pDevice->GetRemoteNode("OffsetY")->GetInt();
// 	strOY.Format(_T("%d"),offsetY);
// 	m_edtOffsetY.SetWindowTextW(strOY);
// 	strOYMin.Format(_T("%d"),m_pDevice->GetRemoteNode("OffsetY")->GetIntMin());
// 	m_stcOYMin.SetWindowTextW(strOYMin);
// 	strOYMax.Format(_T("%d"),m_pDevice->GetRemoteNode("OffsetY")->GetIntMax());
// 	m_stcOYMax.SetWindowTextW(strOYMax);
// 		
// 
// 	m_pDataStream->StartAcquisitionContinuous();
// 	m_pDevice->GetRemoteNode("AcquisitionStart")->Execute();
// }
// 
// 
// void CGigeDemoDlg::OnBnClickedButton3()
// {
// 	// TODO: 在此添加控件通知处理程序代码
// 	CString strOffsetX;
// 	m_edtOffsetX.GetWindowTextW(strOffsetX);
// 	int nROIOffsetX = 0;
// 	
// 	if(m_pDevice != NULL)
// 	{
// 		m_pDataStream->StopAcquisition();
// 		m_pDevice->GetRemoteNode("AcquisitionStop")->Execute();
// 		if(m_pBitmap != NULL)
// 		{
// 			delete m_pBitmap;
// 			m_pBitmap = NULL;
// 		}
// 	}
// 	else
// 		return;
// 
// 	int ntextOffsetX = _wtoi(strOffsetX);
// 
// 	int nOffsetXMin = m_pDevice->GetRemoteNode("OffsetX")->GetIntMin();
// 	int nOffsetXMax = m_pDevice->GetRemoteNode("OffsetX")->GetIntMax();
// 	int nOffsetXInc = m_pDevice->GetRemoteNode("OffsetX")->GetIntInc();
// 
// 	if(ntextOffsetX < nOffsetXMin)
// 		nROIOffsetX = nOffsetXMin;
// 	else if(ntextOffsetX > nOffsetXMax)
// 		nROIOffsetX = nOffsetXMax;
// 	else
// 		nROIOffsetX = ntextOffsetX;
// 
// 	if(nROIOffsetX % nOffsetXInc != 0)
// 		nROIOffsetX = ((int)(nROIOffsetX/nOffsetXInc) + 1) * nOffsetXInc;
// 	CString strOX;
// 	strOX.Format(_T("%d"),nROIOffsetX);
// 	m_edtOffsetX.SetWindowTextW(strOX);
// 	m_pDevice->GetRemoteNode("OffsetX")->SetInt(nROIOffsetX);
// 
// 	int width= 0;
// 	CString strWidth,strWidthMin,strWidthMax;
// 	width = m_pDevice->GetRemoteNode("Width")->GetInt();
// 	strWidth.Format(_T("%d"),width);
// 	m_edtWidth.SetWindowTextW(strWidth);
// 	strWidthMin.Format(_T("%d"),m_pDevice->GetRemoteNode("Width")->GetIntMin());
// 	m_stcWMin.SetWindowTextW(strWidthMin);
// 	strWidthMax.Format(_T("%d"),m_pDevice->GetRemoteNode("Width")->GetIntMax());
// 	m_stcWMax.SetWindowTextW(strWidthMax);
// 		
// 
// 	m_pDataStream->StartAcquisitionContinuous();
// 	m_pDevice->GetRemoteNode("AcquisitionStart")->Execute();
// }
// 
// 
// void CGigeDemoDlg::OnBnClickedButton5()
// {
// 	// TODO: 在此添加控件通知处理程序代码
// 	CString strOffsetY;
// 	m_edtOffsetY.GetWindowTextW(strOffsetY);
// 	int nROIOffsetY = 0;
// 	
// 	if(m_pDevice != NULL)
// 	{
// 		m_pDataStream->StopAcquisition();
// 		m_pDevice->GetRemoteNode("AcquisitionStop")->Execute();
// 		if(m_pBitmap != NULL)
// 		{
// 			delete m_pBitmap;
// 			m_pBitmap = NULL;
// 		}
// 	}
// 	else
// 		return;
// 
// 	int ntextOffsetY = _wtoi(strOffsetY);
// 
// 	int nOffsetYMin = m_pDevice->GetRemoteNode("OffsetY")->GetIntMin();
// 	int nOffsetYMax = m_pDevice->GetRemoteNode("OffsetY")->GetIntMax();
// 	int nOffsetYInc = m_pDevice->GetRemoteNode("OffsetY")->GetIntInc();
// 
// 	if(ntextOffsetY < nOffsetYMin)
// 		nROIOffsetY = nOffsetYMin;
// 	else if(ntextOffsetY > nOffsetYMax)
// 		nROIOffsetY = nOffsetYMax;
// 	else
// 		nROIOffsetY = ntextOffsetY;
// 
// 	if(nROIOffsetY % nOffsetYInc != 0)
// 		nROIOffsetY = ((int)(nROIOffsetY/nOffsetYInc) + 1) * nOffsetYInc;
// 	CString strOY;
// 	strOY.Format(_T("%d"),nROIOffsetY);
// 	m_edtOffsetY.SetWindowTextW(strOY);
// 	m_pDevice->GetRemoteNode("OffsetY")->SetInt(nROIOffsetY);
// 
// 	int height= 0;
// 	CString strHeight,strHeightMin,strHeightMax;
// 	height = m_pDevice->GetRemoteNode("Height")->GetInt();
// 	strHeight.Format(_T("%d"),height);
// 	m_edtHeight.SetWindowTextW(strHeight);
// 	strHeightMin.Format(_T("%d"),m_pDevice->GetRemoteNode("Height")->GetIntMin());
// 	m_stcHMin.SetWindowTextW(strHeightMin);
// 	strHeightMax.Format(_T("%d"),m_pDevice->GetRemoteNode("Height")->GetIntMax());
// 	m_stcHMax.SetWindowTextW(strHeightMax);
// 		
// 
// 	m_pDataStream->StartAcquisitionContinuous();
// 	m_pDevice->GetRemoteNode("AcquisitionStart")->Execute();
// 
// }
// 
// 
// void CGigeDemoDlg::OnBnClickedButton6()
// {
// 	// TODO: 在此添加控件通知处理程序代码
// 		if(m_pDevice != NULL)
// 	{
// 		m_pDataStream->StopAcquisition();
// 		m_pDevice->GetRemoteNode("AcquisitionStop")->Execute();
// 		if(m_pBitmap != NULL)
// 		{
// 			delete m_pBitmap;
// 			m_pBitmap = NULL;
// 		}
// 	}
// 	else
// 		return;
// 	m_pDevice->GetRemoteNode("ReverseX")->SetBool(true);
// 	m_pDataStream->StartAcquisitionContinuous();
// 	m_pDevice->GetRemoteNode("AcquisitionStart")->Execute();
// }
// 
// 
// void CGigeDemoDlg::OnBnClickedButton7()
// {
// 	// TODO: 在此添加控件通知处理程序代码
// 			if(m_pDevice != NULL)
// 	{
// 		m_pDataStream->StopAcquisition();
// 		m_pDevice->GetRemoteNode("AcquisitionStop")->Execute();
// 		if(m_pBitmap != NULL)
// 		{
// 			delete m_pBitmap;
// 			m_pBitmap = NULL;
// 		}
// 	}
// 	else
// 		return;
// 	m_pDevice->GetRemoteNode("ReverseX")->SetBool(false);
// 	m_pDataStream->StartAcquisitionContinuous();
// 	m_pDevice->GetRemoteNode("AcquisitionStart")->Execute();
// 	
// }
// 
// 
// void CGigeDemoDlg::OnBnClickedButton8()
// {
// 	// TODO: 在此添加控件通知处理程序代码
// 			if(m_pDevice != NULL)
// 	{
// 		m_pDataStream->StopAcquisition();
// 		m_pDevice->GetRemoteNode("AcquisitionStop")->Execute();
// 		if(m_pBitmap != NULL)
// 		{
// 			delete m_pBitmap;
// 			m_pBitmap = NULL;
// 		}
// 	}
// 	else
// 		return;
// 	m_pDevice->GetRemoteNode("ReverseY")->SetBool(true);
// 	m_pDataStream->StartAcquisitionContinuous();
// 	m_pDevice->GetRemoteNode("AcquisitionStart")->Execute();
// }
// 
// 
// void CGigeDemoDlg::OnBnClickedButton9()
// {
// 	// TODO: 在此添加控件通知处理程序代码
// 			if(m_pDevice != NULL)
// 	{
// 		m_pDataStream->StopAcquisition();
// 		m_pDevice->GetRemoteNode("AcquisitionStop")->Execute();
// 		if(m_pBitmap != NULL)
// 		{
// 			delete m_pBitmap;
// 			m_pBitmap = NULL;
// 		}
// 	}
// 	else
// 		return;
// 	m_pDevice->GetRemoteNode("ReverseY")->SetBool(false);
// 	m_pDataStream->StartAcquisitionContinuous();
// 	m_pDevice->GetRemoteNode("AcquisitionStart")->Execute();
// }
// 
// 
// void CGigeDemoDlg::OnBnClickedButton10()
// {
// 	// TODO: 在此添加控件通知处理程序代码
// 	//***************需要在初始相机时先判断相机是否是处于SEQUENCE，如果是的话需在初始化时先停下，以防出错；
// 	//***************设置SEQUENCE时，需先停下数据流，然后停下相机，设完后再重新打开数据流，启动相机；
// 	
// 	if(m_pDevice != NULL)
// 	{
// 		try
// 		{	
// 		m_pDevice->GetRemoteNode("AcquisitionStop")->Execute();
//     	m_pDataStream->StopAcquisition();
// 		
// 		if(m_pBitmap != NULL)
// 		{
// 			delete m_pBitmap;
// 			m_pBitmap = NULL;
// 		}
// 
// 		}
// 		catch (BGAPI2::Exceptions::IException& ex)
// 		{
// 			CString str1;
// 			str1.Format(_T("ExceptionType:%s! ErrorDescription:%s in function:%s"),ex.GetType(),ex.GetErrorDescription(),ex.GetFunctionName());
// 			MessageBox(str1);
// 		}
// 	}
// 
// 
// 		//********************************************************
// 			if (m_pDevice->GetRemoteNode("SequencerMode")->GetString() == "On")
// 			{
// 				m_pDevice->GetRemoteNode("SequencerMode")->SetString("Off");
// 			}
// 		//********************************************************
// 			if (m_pDevice->GetRemoteNode("SequencerConfigurationMode")->GetString() == "Off")
// 			{
// 				m_pDevice->GetRemoteNode("SequencerConfigurationMode")->SetString("On");
// 			}
// 		//********************************************************
// 			//SET0
// 			m_pDevice->GetRemoteNode("SequencerSetSelector")->SetInt(0);
// 			m_pDevice->GetRemoteNode("SequencerSetLoad")->Execute();
// 			m_pDevice->GetRemoteNode("SequencerFeatureSelector")->SetString("ExposureTime");
// 			m_pDevice->GetRemoteNode("ExposureTime")->SetDouble(8000.0);
// 			//*****************设ROI为图像的一半
// 			m_pDevice->GetRemoteNode("OffsetX")->SetInt(0);
// 			m_pDevice->GetRemoteNode("OffsetY")->SetInt(0);
// 			m_pDevice->GetRemoteNode("Width")->SetInt(m_pDevice->GetRemoteNode("Width")->GetIntMax() / 2 / m_pDevice->GetRemoteNode("Width")->GetIntInc() * m_pDevice->GetRemoteNode("Width")->GetIntInc());
// 			m_pDevice->GetRemoteNode("Height")->SetInt(m_pDevice->GetRemoteNode("Height")->GetIntMax() / 2 / m_pDevice->GetRemoteNode("Height")->GetIntInc() * m_pDevice->GetRemoteNode("Height")->GetIntInc());
// 			m_pDevice->GetRemoteNode("OffsetX")->SetInt(m_pDevice->GetRemoteNode("OffsetX")->GetIntMax() / 2 / m_pDevice->GetRemoteNode("OffsetX")->GetIntInc() * m_pDevice->GetRemoteNode("OffsetX")->GetIntInc());
// 			m_pDevice->GetRemoteNode("OffsetY")->SetInt(m_pDevice->GetRemoteNode("OffsetY")->GetIntMax() / 2 / m_pDevice->GetRemoteNode("OffsetY")->GetIntInc() * m_pDevice->GetRemoteNode("OffsetY")->GetIntInc());
// 			//***********************************
// 			m_pDevice->GetRemoteNode("TriggerMode")->SetString("On");
// 			m_pDevice->GetRemoteNode("TriggerSource")->SetString("Software");
// 			m_pDevice->GetRemoteNode("SequencerPathSelector")->SetInt(0);
// 			m_pDevice->GetRemoteNode("SequencerTriggerSource")->SetString("ExposureActive");
// 			m_pDevice->GetRemoteNode("SequencerTriggerActivation")->SetString("RisingEdge");
// 			m_pDevice->GetRemoteNode("SequencerSetNext")->SetInt(1);
// 			m_pDevice->GetRemoteNode("SequencerSetSave")->Execute();
// 			//SET 1
// 			m_pDevice->GetRemoteNode("SequencerSetSelector")->SetInt(1);
// 			m_pDevice->GetRemoteNode("SequencerSetLoad")->Execute();
// 			m_pDevice->GetRemoteNode("SequencerFeatureSelector")->SetString("ExposureTime");
// 			m_pDevice->GetRemoteNode("ExposureTime")->SetDouble(5000.0); 
// 			//*****************设ROI为图像的一半
// 			m_pDevice->GetRemoteNode("OffsetX")->SetInt(0);
// 			m_pDevice->GetRemoteNode("OffsetY")->SetInt(0);
// 			m_pDevice->GetRemoteNode("Width")->SetInt(m_pDevice->GetRemoteNode("Width")->GetIntMax() / 2 / m_pDevice->GetRemoteNode("Width")->GetIntInc() * m_pDevice->GetRemoteNode("Width")->GetIntInc());
// 			m_pDevice->GetRemoteNode("Height")->SetInt(m_pDevice->GetRemoteNode("Height")->GetIntMax() / 2 / m_pDevice->GetRemoteNode("Height")->GetIntInc() * m_pDevice->GetRemoteNode("Height")->GetIntInc());
// 			m_pDevice->GetRemoteNode("OffsetX")->SetInt(m_pDevice->GetRemoteNode("OffsetX")->GetIntMax() / 2 / m_pDevice->GetRemoteNode("OffsetX")->GetIntInc() * m_pDevice->GetRemoteNode("OffsetX")->GetIntInc());
// 			m_pDevice->GetRemoteNode("OffsetY")->SetInt(m_pDevice->GetRemoteNode("OffsetY")->GetIntMax() / 2 / m_pDevice->GetRemoteNode("OffsetY")->GetIntInc() * m_pDevice->GetRemoteNode("OffsetY")->GetIntInc());
// 			//************************************
// 			m_pDevice->GetRemoteNode("TriggerMode")->SetString("On");
// 			m_pDevice->GetRemoteNode("TriggerSource")->SetString("Software");
// 			m_pDevice->GetRemoteNode("SequencerTriggerSource")->SetString("ExposureActive");
// 			m_pDevice->GetRemoteNode("SequencerTriggerActivation")->SetString("RisingEdge");
// 			m_pDevice->GetRemoteNode("SequencerSetNext")->SetInt(2);
// 			m_pDevice->GetRemoteNode("SequencerSetSave")->Execute();
// 
// 			//SET 2
// 			m_pDevice->GetRemoteNode("SequencerSetSelector")->SetInt(2);
// 			m_pDevice->GetRemoteNode("SequencerSetLoad")->Execute();
// 			m_pDevice->GetRemoteNode("SequencerFeatureSelector")->SetString("ExposureTime");
// 			m_pDevice->GetRemoteNode("ExposureTime")->SetDouble(4000.0); 
// 			//*****************设ROI为图像的一半
// 			m_pDevice->GetRemoteNode("OffsetX")->SetInt(0);
// 			m_pDevice->GetRemoteNode("OffsetY")->SetInt(0);
// 			m_pDevice->GetRemoteNode("Width")->SetInt(m_pDevice->GetRemoteNode("Width")->GetIntMax() / 2 / m_pDevice->GetRemoteNode("Width")->GetIntInc() * m_pDevice->GetRemoteNode("Width")->GetIntInc());
// 			m_pDevice->GetRemoteNode("Height")->SetInt(m_pDevice->GetRemoteNode("Height")->GetIntMax() / 2 / m_pDevice->GetRemoteNode("Height")->GetIntInc() * m_pDevice->GetRemoteNode("Height")->GetIntInc());
// 			m_pDevice->GetRemoteNode("OffsetX")->SetInt(m_pDevice->GetRemoteNode("OffsetX")->GetIntMax() / 2 / m_pDevice->GetRemoteNode("OffsetX")->GetIntInc() * m_pDevice->GetRemoteNode("OffsetX")->GetIntInc());
// 			m_pDevice->GetRemoteNode("OffsetY")->SetInt(m_pDevice->GetRemoteNode("OffsetY")->GetIntMax() / 2 / m_pDevice->GetRemoteNode("OffsetY")->GetIntInc() * m_pDevice->GetRemoteNode("OffsetY")->GetIntInc());
// 			//**************************************
// 			m_pDevice->GetRemoteNode("TriggerMode")->SetString("On");
// 			m_pDevice->GetRemoteNode("TriggerSource")->SetString("Software");
// 			m_pDevice->GetRemoteNode("SequencerTriggerSource")->SetString("ExposureActive");
// 			m_pDevice->GetRemoteNode("SequencerTriggerActivation")->SetString("RisingEdge");
// 			m_pDevice->GetRemoteNode("SequencerSetNext")->SetInt(0);
// 			m_pDevice->GetRemoteNode("SequencerSetSave")->Execute();
//             //********************************************************
// 			m_pDevice->GetRemoteNode("SequencerSetStart")->SetInt(0);
// 			m_pDevice->GetRemoteNode("SequencerConfigurationMode")->SetString("Off");
// 			m_pDevice->GetRemoteNode("SequencerMode")->SetString("On");
// 
// 
// 			//m_pDevice->GetRemoteNode("TriggerMode")->SetString("On");
// 			m_pDataStream->StartAcquisitionContinuous();
//             m_pDevice->GetRemoteNode("AcquisitionStart")->Execute();
// 
// 
// 
// 	}
// 
// 
// void CGigeDemoDlg::OnBnClickedButton12()
// {
// 	// TODO: 在此添加控件通知处理程序代码
// 	//*****************************************SEQUENCE，触发
// 			
// 	if(m_pDevice->GetRemoteNode("TriggerSource")->GetString() == "Software" )
// 	{
// 		m_pDevice->GetRemoteNode("TriggerSoftware")->Execute();
// 	}
// 	else if(m_pDevice->GetRemoteNode("TriggerSource")->GetString() == "SoftwareTrigger" )
// 	{
// 		m_pDevice->GetRemoteNode("TriggerSoftware")->Execute();
// 	}
// }
// 
// 
// void CGigeDemoDlg::OnBnClickedButton13()
// {
// 	// TODO: 在此添加控件通知处理程序代码
// 	//*****************************************停下SEQUENCE
// 	m_pDevice->GetRemoteNode("AcquisitionStop")->Execute();
//     m_pDataStream->StopAcquisition();
// 			
// 	if (m_pDevice->GetRemoteNode("SequencerMode")->GetString() == "On")
// 	{
// 		m_pDevice->GetRemoteNode("SequencerMode")->SetString("Off");
// 
// 	}
// 	m_pDataStream->StartAcquisitionContinuous();
//     m_pDevice->GetRemoteNode("AcquisitionStart")->Execute();
// 
// 	//*****************************************
// }
// 
// 
// void CGigeDemoDlg::OnBnClickedButton14()
// {
// 	// TODO: 在此添加控件通知处理程序代码
// 	//*****************************************开始SEQUENCE
// 	m_pDevice->GetRemoteNode("AcquisitionStop")->Execute();
//     m_pDataStream->StopAcquisition();
// 			
// 	if (m_pDevice->GetRemoteNode("SequencerMode")->GetString() == "Off")
// 	{
// 		m_pDevice->GetRemoteNode("SequencerMode")->SetString("On");
// 
// 	}
// 	m_pDataStream->StartAcquisitionContinuous();
//     m_pDevice->GetRemoteNode("AcquisitionStart")->Execute();
// 	//*****************************************
// }



void CGigeDemoDlg::OnBnClickedButtonInitSys()
{
	// TODO:  在此添加控件通知处理程序代码
	USES_CONVERSION;
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		//m_pSystemList = SystemList::CreateInstanceFromPath("C:\\Users\\user\\Desktop\\GigeDemoV2.5\\x64\\Debug");
		m_pSystemList = SystemList::GetInstance();
		//m_pSystemList->GetInstance();
		m_pSystemList->Refresh();
		//debug
		int syscount = (int)m_pSystemList->size();
		int x = 0;
	}
	catch (BGAPI2::Exceptions::IException& ex)
	{
		//LPCTSTR pwch;

		CString str1;
		str1.Format(_T("ExceptionType:%s! ErrorDescription:%s in function:%s"), ex.GetType(), ex.GetErrorDescription(), ex.GetFunctionName());
		MessageBox(str1);
	}
	//OPEN THE FIRST SYSTEM IN THE LIST WITH A CAMERA CONNECTED
	try
	{
		for (SystemList::iterator sysIterator = m_pSystemList->begin(); sysIterator != m_pSystemList->end(); sysIterator++)
		{
			try
			{
				sysIterator->second->Open();
				//debug part*********************************************************************************************
				CString sysType;
				CString sysVersion;
				CString sysName;
				CString sysID;
				CString sysVendor;
				CString sysModel;
				CString sysPathName;
				CString sysDisplay;

				USES_CONVERSION;
				sysName = A2W(sysIterator->second->GetFileName());//"bgapi_gige.cti"
				sysType = A2W(sysIterator->second->GetTLType());//GEV
				sysVersion = A2W(sysIterator->second->GetVersion());//2.8.155
				sysID = A2W(sysIterator->second->GetID());
				sysVendor = A2W(sysIterator->second->GetVendor());//Baumer
				sysModel = A2W(sysIterator->second->GetModel());//bgapi_gige
				sysPathName = A2W(sysIterator->second->GetPathName());
				sysDisplay = A2W(sysIterator->second->GetDisplayName());//Baumer GigE TL
				//********************************************************************************************************//
				m_sSystemID = sysIterator->first;
				//InterfaceList
				try
				{
					m_pInterfaceList = sysIterator->second->GetInterfaces();
					m_pInterfaceList->Refresh(1000);
					// interface count
					int infcount = (int)m_pInterfaceList->size();
					int x = 0;
				}
				catch (BGAPI2::Exceptions::IException& ex)
				{
					CString str2;
					str2.Format(_T("ExceptionType:%s! ErrorDescription:%s in function:%s"), ex.GetType(), ex.GetErrorDescription(), ex.GetFunctionName());
					MessageBox(str2);
				}
				try
				{
					//OPEN THE FIRST INTERFACE IN THE LIST
					for (InterfaceList::iterator ifIterator = m_pInterfaceList->begin(); ifIterator != m_pInterfaceList->end(); ifIterator++)
					{
						try
						{
							ifIterator->second->Open();
							//Debug part*******************************
							CString infType = A2W(ifIterator->second->GetTLType());
							CString infName = A2W(ifIterator->second->GetDisplayName());

							//****************************************
							//search for any camera is connected to this interface
							m_pDeviceList = ifIterator->second->GetDevices();
							m_pDeviceList->Refresh(1000);
							if (m_pDeviceList->size() == 0)
							{
								//MessageBox(_T("Close Interface(No camera was found)!"));
								ifIterator->second->Close();
								//continue;
							}
							else
							{
								m_sInterfaceID = ifIterator->first;
								//Debug part**********************************

								if (ifIterator->second->GetTLType() == "GEV")
								{
									bo_int64 iIpAddress = ifIterator->second->GetNode("GevInterfaceSubnetIPAddress")->GetInt();
									CString strIpAddress;
									strIpAddress.Format(_T("%I64d.%I64d.%I64d.%I64d"), (iIpAddress >> 24), ((iIpAddress & 0xffffff) >> 16), ((iIpAddress & 0xffff) >> 8), (iIpAddress & 0xff));
									bo_int64 iSubnetMask = ifIterator->second->GetNode("GevInterfaceSubnetMask")->GetInt();
									CString strSubnetMask;
									strSubnetMask.Format(_T("%I64d.%I64d.%I64d.%I64d"), (iSubnetMask >> 24), ((iSubnetMask & 0xffffff) >> 16), ((iSubnetMask & 0xffff)) >> 8, (iSubnetMask & 0xff));
								}
								//********************************************
								break;
							}
						}
						catch (BGAPI2::Exceptions::ResourceInUseException& ex)
						{
							CString str3;
							str3.Format(_T("Interface %s already opened!ResourceInUseException:%s"), ifIterator->first, ex.GetErrorDescription());
							MessageBox(str3);
						}

					}
				}
				catch (BGAPI2::Exceptions::IException& ex)
				{
					CString str4;
					str4.Format(_T("ExceptionType:%s! ErrorDescription:%s in function:%s"), ex.GetType(), ex.GetErrorDescription(), ex.GetFunctionName());
					MessageBox(str4);
				}
				//if a camera is connected to the system interface then leave the system loop
				if (m_sInterfaceID != "")
				{
					break;
				}
			}
			catch (BGAPI2::Exceptions::ResourceInUseException& ex)
			{
				CString str5;
				str5.Format(_T("Interface %s already opened!ResourceInUseException:%s"), sysIterator->first, ex.GetErrorDescription());
				MessageBox(str5);
			}
		}
	}
	catch (BGAPI2::Exceptions::IException& ex)
	{
		CString str6;
		str6.Format(_T("ExceptionType:%s! ErrorDescription:%s in function:%s"), ex.GetType(), ex.GetErrorDescription(), ex.GetFunctionName());
		MessageBox(str6);
	}

	if (m_sSystemID == "")
	{
		MessageBox(_T("No system found!"));
		BGAPI2::SystemList::ReleaseInstance();
	}
	else
	{
		m_pSystem = (*m_pSystemList)[m_sSystemID];
	}

	if (m_sInterfaceID == "")
	{
		MessageBox(_T("No camera found!"));
		m_pSystem->Close();
		BGAPI2::SystemList::ReleaseInstance();
	}
	else
	{
		m_pInterface = (*m_pInterfaceList)[m_sInterfaceID];
	}
	//Device List
	try
	{
		//count available cameras
		m_pDeviceList = m_pInterface->GetDevices();
		m_pDeviceList->Refresh(1000);
		int devcount;
		devcount = (int)m_pDeviceList->size();
		int x = 0;



	}
	catch (BGAPI2::Exceptions::IException& ex)
	{
		CString str7;
		str7.Format(_T("ExceptionType:%s! ErrorDescription:%s in function:%s"), ex.GetType(), ex.GetErrorDescription(), ex.GetFunctionName());
		MessageBox(str7);
	}


	//在线相机个数
	m_iOnlineCamNum = m_pDeviceList->size();

	for (int i = 0; i < m_iOnlineCamNum; i++)
	{			
		m_pBaumerCam[i] = new CCamBaumer_12M;
	}
}


	void CGigeDemoDlg::OnBnClickedButtonInitDlp()
	{
		// TODO:  在此添加控件通知处理程序代码
	}
