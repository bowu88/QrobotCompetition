#pragma once


// PicDialog �Ի���

class PicDialog : public CDialog
{
	DECLARE_DYNAMIC(PicDialog)

public:
	PicDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PicDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
public:
	CDialog *m_pMianDlg;
	void set_dlg(CDialog * parnet_dlg);
	void show();
	
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButton1();
	
};
