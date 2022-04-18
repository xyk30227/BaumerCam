
// GigeDemoDlg.h : 头文件
//

#pragma once

#include "afxwin.h"
#include "afxcmn.h"
#include "CamObj.h"
#include "CamBaumer_12M.h"
enum
{
	CAM_BAUMER_12M,
};
// CGigeDemoDlg 对话框
class CGigeDemoDlg : public CDialogEx
{
// 构造
public:
	CGigeDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GIGEDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CCamObj *m_pCam[2];
	
	int m_iCamMode;
	int  GetCamMode() { return m_iCamMode; };
	void SetCamMode(int iCamMode) { m_iCamMode = iCamMode; };
	CCamObj *GetCam() 
	{ 
		if (GetCamMode() == CAM_BAUMER_12M)
		{
			CCamBaumer_12M *pCam = new CCamBaumer_12M;
			return pCam;
		}
	};


	CCamBaumer_12M *m_pBaumerCam[2];
	bool m_bCamReady;
	int m_iOnlineCamNum;
public:
	//variables for systemlist and system
	BGAPI2::SystemList*       m_pSystemList ;
	BGAPI2::System*           m_pSystem;
	BGAPI2::String            m_sSystemID;

	//variables for Interfacelist and Interface
	BGAPI2::InterfaceList*    m_pInterfaceList;
	BGAPI2::Interface*        m_pInterface;
	BGAPI2::String            m_sInterfaceID;

	//variables for Devicelist and device
	BGAPI2::DeviceList*       m_pDeviceList;



	bool                  m_bSaveImage;
	Gdiplus::Bitmap*      m_pBitmap;
	CString               m_strDirectory;
	bool                  m_bEnabled;
	bool                  m_bSwTrigger;

	
	//control variables
public:
	CEdit                 m_edtCameraType;
	CSliderCtrl           m_sldShutter;
	CEdit                 m_edtShutter;
	CStatic               m_stcMaxShutter;
	CStatic               m_stcMinShutter;
	CSliderCtrl           m_sldGain;
	CEdit                 m_edtGain;
	CStatic               m_stcMaxGain;
	CStatic               m_stcMinGain;
	CButton               m_chkSaving;
	CEdit                 m_edtPath;
	CSpinButtonCtrl       m_spnShutter;
	CButton               m_chkTrgEnabled;
	CComboBox             m_cmbTrgSource;
	CComboBox             m_cmbTrgMode;
	CSpinButtonCtrl       m_spnDelay;
	CEdit                 m_edtDelay;
	CStatic               m_stcPicture;
private:
	afx_msg void OnBnClickedBtnpath();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnplay();
	afx_msg void OnBnClickedBtnpause();
	afx_msg void OnBnClickedBtnsnap();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnswtexcute();
	afx_msg void OnBnClickedBtnexposure();
	afx_msg void OnBnClickedBtngain();
	afx_msg void OnNMCustomdrawSldexposure(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSldgain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCmbtsource();
	afx_msg void OnCbnSelchangeCmbtactivation();
	afx_msg void OnBnClickedBtndelay();
	afx_msg void OnDeltaposSpnexposure(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpndelay(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtninitialize();
public:
	bool    SaveImage(CString str,BYTE* bdata,int width,int height);
	afx_msg void OnBnClickedChktriggerenabled();
	CEdit m_edtWidth;
	CEdit m_edtHeight;
	CEdit m_edtOffsetX;
	CEdit m_edtOffsetY;
	CStatic m_stcWMin;
	CStatic m_stcWMax;
	CStatic m_stcHMin;
	CStatic m_stcHMax;
	CStatic m_stcOXMin;
	CStatic m_stcOXMax;
	CStatic m_stcOYMin;
	CStatic m_stcOYMax;
// 	afx_msg void OnBnClickedButton1();
// 	afx_msg void OnBnClickedButton2();
// 	afx_msg void OnBnClickedButton3();
// 	afx_msg void OnBnClickedButton5();
// 	afx_msg void OnBnClickedButton6();
// 	afx_msg void OnBnClickedButton7();
// 	afx_msg void OnBnClickedButton8();
// 	afx_msg void OnBnClickedButton9();
// 	afx_msg void OnEnChangeEdit2();
// 	afx_msg void OnBnClickedButton10();
// 	afx_msg void OnBnClickedButton11();
// 	afx_msg void OnBnClickedButton12();
// 	afx_msg void OnBnClickedButton13();
// 	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButtonInitSys();
	afx_msg void OnBnClickedButtonInitDlp();
};
