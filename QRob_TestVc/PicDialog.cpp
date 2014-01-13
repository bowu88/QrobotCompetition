// PicDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QRob_TestVc.h"
#include "PicDialog.h"
#include "afxdialogex.h"
#include "DlgMain.h"
#include "CvvImage.h"
// PicDialog �Ի���

IMPLEMENT_DYNAMIC(PicDialog, CDialog)

PicDialog::PicDialog(CWnd* pParent /*=NULL*/)
	: CDialog(PicDialog::IDD, pParent)
{
	
}

PicDialog::~PicDialog()
{
}

void PicDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void PicDialog::set_dlg(CDialog * parnet_dlg)
{
	m_pMianDlg =parnet_dlg;
}

BEGIN_MESSAGE_MAP(PicDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &PicDialog::OnBnClickedButton1)
	
END_MESSAGE_MAP()


// PicDialog ��Ϣ�������


void PicDialog::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	CDlgMain *parent_dlg = (CDlgMain *)m_pMianDlg;
	CString sceneFileName ( "hand.xml");
	if (!((parent_dlg->m_Talk).ChangScenceFile(sceneFileName)))
            {
               MessageBox(_T("ת��ʧ��"));
            }
	parent_dlg->PicFlag = true;
	parent_dlg->strCommand = _T("");
	(parent_dlg->m_Talk).StartRecognize(_T("QQRobot"), FALSE);
	
	

}



void PicDialog::show()
{
	/*
	CDlgMain *parent_dlg = (CDlgMain *)m_pMianDlg;
	 
	CDC * pDC = GetDlgItem(IDC_STATIC)->GetDC();
			CImage image;
			CFileFind   f;
	if(parent_dlg->strCommand.GetLength()>0)
	{
	CString temp;
	CString file;
	for(int i=0;i<parent_dlg->strCommand.GetLength();i++)
	{

			temp=parent_dlg->strCommand[i];
			CString s1(".\\hand\\");
			CString s2(".png");
			 file=s1+temp+s2;
			//AfxMessageBox(file); 
		if(f.FindFile(file))
	    {

		CString picName = f.GetFileTitle();
		
		//f.FindNextFile();

		   parent_dlg->path=file;
           image.Load(parent_dlg->path);
			//AfxMessageBox(parent_dlg->path); 
			image.Draw(pDC->m_hDC,10,10);
			Sleep(1000);
			//parent_dlg->RobotMove(_T(".\\motion\\eyeshow\\����.txt"));
			
			//RobotMove(_T(".\\motion\\dance\\normal\\1.txt"));
			//break;
         }
	    }
	image.Load(_T(".//picture//default.png"));
	image.Draw(pDC->m_hDC,10,10);
	ReleaseDC(pDC); 
	
	parent_dlg->strCommand=_T("");

	}
	*/
	CDlgMain *parent_dlg = (CDlgMain *)m_pMianDlg;
	CFileFind f;
	if(parent_dlg->strCommand.GetLength()>0) 
	{
		CString path = _T(".\\video\\")+parent_dlg->strCommand+_T(".avi");
		if(f.FindFile(path))
		{


				CString str=parent_dlg->strCommand+_T("��ʼ����");
				parent_dlg->m_speak.StopAsynPlay();
				parent_dlg->m_speak.ClearPlayList();
				parent_dlg->m_speak.AddTextToPlayList(str, str, FALSE);
				parent_dlg->m_speak.AddRecToPlayList();
				parent_dlg->m_speak.StartAsynPlay();
				Sleep(2000);
				USES_CONVERSION;	//��ʽת����־
				setlocale( LC_ALL, "C" );
				const char* strOut;
				char temp[0x100];
				 ::wsprintfA(temp, "%ls", (LPCTSTR)path);
				 strOut = temp;

				CvCapture* capture=0;
				capture = cvCreateFileCapture(strOut);
			

				double rate= (double)cvGetCaptureProperty( capture , CV_CAP_PROP_FPS);
				bool stop(false);
				IplImage* frame = NULL;
				CvvImage m_CvvImage;
				int delay= 1000/rate;
				CDC * pDC = GetDlgItem(IDC_STATIC)->GetDC();
				CRect rectprint;
				GetDlgItem(IDC_STATIC)->GetClientRect(&rectprint);
				while (!stop) 
				{
					frame = cvQueryFrame(capture);
					if (!frame)
						break;
				//	image.CopyOf(frame,1);
				//	image.Draw(pDC->m_hDC,10,10);
					m_CvvImage.CopyOf(frame,1); //���Ƹ�֡ͼ��    
					m_CvvImage.DrawToHDC(pDC->m_hDC, &rectprint); //��ʾ���豸�ľ��ο���
					if (cvWaitKey(delay)>=0)
						stop= true;
					Sleep(400);		
				}
				cvReleaseCapture(&capture);
			
				GetDlgItem(IDC_STATIC)->EnableWindow(TRUE);

			
		}
		else 
		{
			(parent_dlg->m_speak).AddTextToPlayList(_T("���ˣ��һ�û��ѧϰ�������"), _T(""), TRUE);
			(parent_dlg->m_speak).StartAsynPlay();
		}
		parent_dlg->strCommand=_T("");
	}
	
	
}
	
			
			

