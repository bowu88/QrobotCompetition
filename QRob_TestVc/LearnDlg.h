#pragma once
#include "camera1.h"


// LearnDlg �Ի���

class LearnDlg : public CDialog
{
	DECLARE_DYNAMIC(LearnDlg)

public:
	LearnDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LearnDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CDQrobotCamera m_CameraLearn;

	CDialog *m_pMianDlg;
	void set_dlg(CDialog * parnet_dlg);
	bool flag;

	DECLARE_EVENTSINK_MAP()
	void ImageCaptureCamera(long width, long height, VARIANT* imageData);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	
};
