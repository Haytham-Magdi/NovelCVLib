// MfcCvTut_11Jun07Dlg.h : header file
//

#pragma once

#include <Novel-Lib\Ncv\IOMgr.h>
#include "afxwin.h"


// Define our callback which we will install for
// mouse events.
//

// CMfcCvTut_11Jun07Dlg dialog
class CMfcCvTut_11Jun07Dlg : public CDialog, public Ncv::IOMgr::IIOMgrCore
{
// Construction
public:
	CMfcCvTut_11Jun07Dlg(CWnd* pParent = NULL);	// standard constructor

	virtual void ReadString( char * a_sKey, char * a_buff);
	virtual bool ValueExists( char * a_sKey );
	void InitIOValues();

// Dialog Data
	enum { IDD = IDD_MFCCVTUT_11JUN07_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	void DoClearIo();

	static void OpenCV_Mouse_Callback(
		int a_event, int a_x, int a_y, int a_flags, void* a_param	
		);

	static void RgnSgmImg_Mouse_Callback(
		int a_event, int a_x, int a_y, int a_flags, void* a_param	
		);


// Implementation
protected:

	int m_nMouseLBCnt;

	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenImageBtn();
public:
	afx_msg void OnBnClickedProcessImageBtn();
public:
	afx_msg void OnBnClickedCreateBtn();
public:
	afx_msg void OnBnClickedSobelBtn();
public:
	afx_msg void OnBnClickedTry1Btn();
public:
	afx_msg void OnBnClickedTry2Btn();
public:
	afx_msg void OnBnClickedTry3Btn();
public:
	afx_msg void OnBnClickedTry4Btn();
public:
	afx_msg void OnBnClickedTry5Btn();
public:
	afx_msg void OnBnClickedTry6Btn();
public:
	afx_msg void OnBnClickedTry7Btn();
public:
	afx_msg void OnBnClickedClustersBtn();
public:
	afx_msg void OnBnClickedTry8Btn();
public:
	afx_msg void OnBnClickedTry9Btn();
public:
	afx_msg void OnBnClickedTry10Btn();
public:
	afx_msg void OnBnClickedFastAvgBtn();
public:
	afx_msg void OnBnClickedMaxMinEdgeBtn();
public:
	afx_msg void OnBnClickedTry11Btn();
public:
	afx_msg void OnBnClickedTry12Btn();
	afx_msg void OnBnClickedTry13Btn();
	afx_msg void OnBnClickedTry14Btn();
	afx_msg void OnBnClickedSobelMaxBtn();
	afx_msg void OnBnClickedTry15Btn();
	afx_msg void OnBnClickedEdgeDirBtn();
	afx_msg void OnBnClickedTry16Btn();
	afx_msg void OnBnClickedEdgeDir2Btn();
	afx_msg void OnBnClickedTry17Btn();
	afx_msg void OnBnClickedTry18Btn();
	afx_msg void OnBnClickedTry19Btn();
	afx_msg void OnLbnSelchangeList2();
protected:
	CListBox m_listKeys;
	CListBox m_listValues;
public:
	afx_msg void OnBnClickedTryMouseBtn();
	afx_msg void OnBnClickedClearIo();
	afx_msg void OnBnClickedDrawLinePath();
	CEdit edtAvg;
	afx_msg void OnBnClickedAvgBtn();
	afx_msg void OnBnClickedResetBtn();
	CEdit edtSizeUp;
	afx_msg void OnBnClickedSizeUpBtn();
	afx_msg void OnBnClickedSizeDownBtn();
	CEdit edtSizeDown;
	afx_msg void OnBnClickedSaveToFileBtn();
	CEdit edtSaveToFile;
	afx_msg void OnBnClickedClipBtn();
	afx_msg void OnBnClickedTry20Btn();
	CEdit edtThreshold;
	afx_msg void OnBnClickedThresholdBtn();
	afx_msg void OnBnClickedUndoBtn();
	afx_msg void OnBnClickedRedoBtn();
	CEdit edtDilate;
	CEdit edtErode;
	afx_msg void OnBnClickedDilateBtn();
	afx_msg void OnBnClickedErodeBtn();
	CEdit edtMedian;
	afx_msg void OnBnClickedMedianBtn();
	afx_msg void OnBnClickedEqualizeHistBtn();
	CEdit edtAprSize1D;
	afx_msg void OnBnClickedGrayBtn();
	afx_msg void OnBnClickedMultByBtn();
	afx_msg void OnBnClickedTry26Btn();
};
