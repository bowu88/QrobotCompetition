#pragma once
#include "qroboteventctrl1.h"
#include "CQrobotSpeak.h"
#include "cqrobottalk.h"
#include "cqrobotscript.h"
#include "cqrobotbasicimage.h"
#include "cqrobotcontroller.h"
#include "atlimage.h"
#include "camera1.h"
#include "PicDialog.h"
#include "CameraDlg.h"
#include "LearnDlg.h"
#include "string.h"
#include<vector>
#include<Iterator>
// CDlgMain dialog

class CDlgMain : public CDialog
{
	DECLARE_DYNAMIC(CDlgMain)

public:
	enum CloundMode
	{
		CLOUND_NORMAL = 0x01,
        ClOUND_CHILD = 0x02,
        CLOUND_QQMUSIC = 0x03,
        CLOUND_STOCK = 0x04,
        CLOUND_DEFMUSIC = 0x05,
	};
	enum VoiceMsg
	{
		MSG_RECORD_FINISHED = 0x02,     //����¼������
        MSG_RECORD_BEGIN = 0x03,     //��ʼ¼������

        MSG_PLAY_READYFLAG = 0x14,     //���������źţ�1:��ʼ��0:����
        MSG_PLAY_ASYNCSTART = 0x15,     //ͬ�����������У���������������
        MSG_PLAY_ASYNCFINISH = 0x16,    //�첽�����������	
        MSG_PLAY_ASYNCSTOP = 0x17,     //�첽�����ж�
        MSG_START_RECORD = 0x18      //��ʼ¼��
	};
	enum MotioMsg
	{
        HEAD_TOUCH_DOWM = 0x01,
        HEAD_TOUCH_UP = 0x02,
        HEAD_LONG_TOUCH = 0x03,
        NECK_TOUCH_DOWN = 0x04,
        NECK_TOUCH_UP = 0x05
	};
	CDlgMain(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgMain();

// Dialog Data
	enum { IDD = IDD_DIALOG_MAIN };
public:
	CQrobotSpeak m_speak;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void InitModuleQroboteventctrl1();
	CQroboteventctrl1 m_eventCtrl;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void CreateModuleWindowQroboteventctrl1(long top, long left, long width, long height);
	void CloudVoiceCmdQroboteventctrl1(long msgType, LPCTSTR strResult);
	void ExitModuleQroboteventctrl1();
	void DestroyModuleWindowQroboteventctrl1();
	void LineCommandQroboteventctrl1(LPCTSTR strResult);
	void LocaleVoiceCmdQroboteventctrl1(long msgType, long sentenceID, long matchScore, long slotNum, VARIANT* slotID, VARIANT* slotText);
	void QRobotMsgMotionQroboteventctrl1(long nMsgID, long param1, VARIANT* param2);
	void QRobotMsgNormalQroboteventctrl1(long nMsgID, long param1, VARIANT* param2);
	void QRobotMsgVoiceQroboteventctrl1(long nMsgID, long param1, VARIANT* param2);
	
	
	CQrobotScript m_Script;
	afx_msg void OnBnClickedButton1();
	
	afx_msg void OnBnClickedButton3();
	CFile  file;
	CFile  myfile;
public:
	CString strCommand;
	std::vector<CString>   piclist;
	CString path;
	PicDialog test;
	CQrobotTalk m_Talk;
	BOOL RobotMove(LPCTSTR);
	CQrobotBasicImage m_image;
	afx_msg void OnBnClickedButton2();
	bool PicFlag;
	bool LearnFlag;
	//void getFiles( string path, vector<string>& files )  ; 
};
