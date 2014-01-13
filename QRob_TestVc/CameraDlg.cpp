// CameraDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QRob_TestVc.h"
#include "CameraDlg.h"
//#include "afxdialogex.h"
#include "DlgMain.h"

//#include <algorithm>
// CameraDlg �Ի���

 

IMPLEMENT_DYNAMIC(CameraDlg, CDialog)

CameraDlg::CameraDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CameraDlg::IDD, pParent)
{
flag=false;
}

CameraDlg::~CameraDlg()
{
}

void CameraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CAMERA1, m_Camera);
}

void CameraDlg::set_dlg(CDialog * parnet_dlg)
{
	m_pMianDlg =parnet_dlg;
}

BEGIN_MESSAGE_MAP(CameraDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CameraDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CameraDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CameraDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CameraDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CameraDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CameraDlg ��Ϣ�������


void CameraDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDlgMain *parent_dlg = (CDlgMain *)m_pMianDlg;
	m_Camera.InitCameraDll(); 
	m_Camera.OpenWebCamera(0,480*360);
	(parent_dlg->m_speak).ClearPlayList();//��ղ����б�
	(parent_dlg->m_speak).AddTextToPlayList(_T("��ʼ����¼��"), _T(""), TRUE);
	(parent_dlg->m_speak).StartAsynPlay();
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
	
}

void CameraDlg::svmTrain()

{
	int ImgWidht =64;  
    int ImgHeight = 64;  
    vector<string> img_path;  //�����ļ�������  
    vector<int> img_catg;    
    int nLine = 0;    
    string buf;    
    ifstream svm_data( ".\\SVM_DATA.txt" );   //ѵ������ͼƬ·�� 
    unsigned long n;    
    
    while( svm_data )  //��ѵ�������ļ����ζ�ȡ����  
    {    
        if( getline( svm_data, buf ) )    
        {    
            nLine ++;    
           
            if( nLine % 2 == 0 )//����ķ���Ƚ�����˼�����ó��������SVM_DATA.txt�ı���Ӧ����һ�����ļ�·����������һ�о��Ǹ�ͼƬ����𣬿�������Ϊ0����1����Ȼ���Ҳ����ν   
            {    
                 img_catg.push_back( atoi( buf.c_str() ) );//atoi���ַ���ת�������ͣ���־��0,1����ע����������Ҫ��������𣬷�������    
            }    
            else    
            {    
                img_path.push_back( buf );//ͼ��·��    
            }    
        }    
    }    
    svm_data.close();//�ر��ļ�    
    
    int nImgNum = nLine/2;            //������������    
    CvMat * FeaturesMat = cvCreateMat(nImgNum, 1764, CV_32FC1);//64*128��ѵ���������þ�����totalSample*3780,64*64��ѵ���������þ�����totalSample*1764  
    cvSetZero(FeaturesMat);    
    CvMat * LabelMat = cvCreateMat(nImgNum, 1, CV_32FC1);//������ʶ    
    cvSetZero(LabelMat);  

    IplImage* src;  
   IplImage*  trainImg=cvCreateImage(cvSize(64,64),8,3);

   for( vector<string>::size_type i = 0; i != img_path.size(); i++ )  //vector<string>�Ĳ��������ж���vector�ĵڼ���Ԫ�ص�  
    {    
         
		 src=cvLoadImage(img_path[i].c_str(),1);   
         cvResize(src,trainImg);   //��ȡͼƬ 
		cv::Mat img(trainImg,0);

        HOGDescriptor hog(cvSize(64,64),cvSize(16,16),cvSize(8,8),cvSize(8,8),9);  //������˼���ο�����1,2       
        vector<float>  descriptors;//�������       
		hog.compute(img, descriptors); //���ü��㺯����ʼ����  
      
        n=0;    
        for(vector<float>::iterator iter=descriptors.begin();iter!=descriptors.end();iter++)    
        {    
            //��HOG�洢����  
		cvmSet(FeaturesMat,i,n,*iter);  
		  n++;    
        }    
       
		  cvmSet(LabelMat, i, 0, img_catg[i] ); 

    }    
                 
    CvSVM svm = CvSVM();  //�½�һ��SVM
    CvSVMParams param;  //����  
    CvTermCriteria criteria;      
    criteria = cvTermCriteria( CV_TERMCRIT_EPS, 1000, FLT_EPSILON );      
    param = CvSVMParams( CvSVM::C_SVC, CvSVM::RBF, 10.0, 0.09, 1.0, 10.0, 0.5, 1.0, NULL, criteria );     
      
    /* 
    SVM���ࣺCvSVM::C_SVC      
    Kernel�����ࣺCvSVM::RBF      
    degree��10.0���˴β�ʹ�ã�      
    gamma��8.0      
    coef0��1.0���˴β�ʹ�ã�      
    C��10.0      
    nu��0.5���˴β�ʹ�ã�      
    p��0.1���˴β�ʹ�ã�      
    Ȼ���ѵ���������滯����������CvMat�͵������      
                                                        */         

   //����������(5)SVMѧϰ�������������           
    svm.train( FeaturesMat, LabelMat, Mat(), Mat(), param ); //ѵ��      
    //�������ѵ�����ݺ�ȷ����ѧϰ����,����SVMѧϰ�����       
    svm.save( ".\\SVM_DATA.xml" );  
     CDlgMain *parent_dlg = (CDlgMain *)m_pMianDlg;
	(parent_dlg->m_speak).ClearPlayList();//��ղ����б�
	(parent_dlg->m_speak).AddTextToPlayList(_T("������ѵ���ɹ�"), _T(""), TRUE);
	(parent_dlg->m_speak).StartAsynPlay();
	//GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
   AfxMessageBox(_T("������ѵ���ɹ���"));

}



void CameraDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDlgMain *parent_dlg = (CDlgMain *)m_pMianDlg;
	(parent_dlg->m_image).SaveImage(_T(".\\hand.png"));
	m_Camera.CloseWebCamera();
	IplImage* pFrame=cvLoadImage(".\\hand.png",1);
	CString a = svmRecognize(pFrame);
	cvReleaseImage( &pFrame); 
	
	//����ͼƬ
	//�������
	//AfxMessageBox(a);
	(parent_dlg->m_speak).AddTextToPlayList(a, _T(""), TRUE);
	(parent_dlg->m_speak).StartAsynPlay();
	//��ʾ����
	GetDlgItem(IDC_EDIT1)->SetWindowText(a);
	
	
}
BEGIN_EVENTSINK_MAP(CameraDlg, CDialog)
	ON_EVENT(CameraDlg, IDC_CAMERA1, 1, CameraDlg::ImageCaptureCamera, VTS_I4 VTS_I4 VTS_PVARIANT)
END_EVENTSINK_MAP()


void CameraDlg::ImageCaptureCamera(long width, long height, VARIANT* imageData)
{
	// TODO: �ڴ˴������Ϣ����������
	CDlgMain *parent_dlg = (CDlgMain *)m_pMianDlg;
	if(!((parent_dlg->m_image).CreateDispatch(_T("QrobotInterface.BasicImage.1"))))
	{    
		AfxMessageBox(_T("Image Create Dispach Failed"));
	}
	// TODO: �ڴ˴������Ϣ����������
	(parent_dlg->m_image).CreateImageFromBuffer(width,height,*imageData); 
	(parent_dlg->m_image).ShowImage((_int64)(GetDlgItem(IDC_CAMERA1)->GetDC()->m_hDC),0,0,1.0);
	
}
int CameraDlg::otsu(const IplImage *src_image)
{
	double sum = 0.0;  
    double w0 = 0.0;  
    double w1 = 0.0;  
    double u0_temp = 0.0;  
    double u1_temp = 0.0;  
    double u0 = 0.0;  
    double u1 = 0.0;  
    double delta_temp = 0.0;  
    double delta_max = 0.0;  
  
    //src_image�Ҷȼ�  
    int pixel_count[256]={0};  
    float pixel_pro[256]={0};  
    int threshold = 0;  
    uchar* data = (uchar*)src_image->imageData;  
    //ͳ��ÿ���Ҷȼ������صĸ���  
    for(int i = 0; i < src_image->height; i++)  
    {  
        for(int j = 0;j < src_image->width;j++)  
        {  
            pixel_count[(int)data[i * src_image->width + j]]++;  
            sum += (int)data[i * src_image->width + j];  
        }  
    }  
    //cout<<"ƽ���Ҷȣ�"<<sum / ( src_image->height * src_image->width )<<endl;  
    //����ÿ���Ҷȼ���������Ŀռ����ͼ��ı���  
    for(int i = 0; i < 256; i++)  
    {  
    pixel_pro[i] = (float)pixel_count[i] / ( src_image->height * src_image->width );  
    }  
    //�����Ҷȼ�[0,255],Ѱ�Һ��ʵ�threshold  
    for(int i = 0; i < 256; i++)  
    {  
        w0 = w1 = u0_temp = u1_temp = u0 = u1 = delta_temp = 0;  
        for(int j = 0; j < 256; j++)  
        {  
            if(j <= i)   //��������  
            {  
                w0 += pixel_pro[j];  
                u0_temp += j * pixel_pro[j];  
            }  
            else   //ǰ������  
            {  
                w1 += pixel_pro[j];  
                u1_temp += j * pixel_pro[j];  
            }  
        }  
        u0 = u0_temp / w0;  
        u1 = u1_temp / w1;  
        delta_temp = (float)(w0 *w1* pow((u0 - u1), 2)) ;  
        if(delta_temp > delta_max)  
        {  
            delta_max = delta_temp;  
            threshold = i;  
        }  
    }  
    return threshold;  
}

CString CameraDlg::svmRecognize( IplImage* src1)
{
	CvSVM svm = CvSVM();//�½�һ��SVM  
    svm.load(".\\SVM_DATA.xml", 0);  
	
    IplImage* trainImg=cvCreateImage(cvSize(64,64),8,3); 
    char line[512];    
    ofstream predict_txt( ".\\SVM_PREDICT.txt", 1); 

	//IplImage *src1 = cvLoadImage(".\\picture\\1.png",1); 
   
	 cvZero(trainImg);    
      cvResize(src1,trainImg);   //��ȡͼƬ 
	  cv::Mat img(trainImg,0);

     HOGDescriptor hog(cvSize(64,64),cvSize(16,16),cvSize(8,8),cvSize(8,8),9);  //������˼���ο�����1,2
    vector<float> descriptors(1764);//�������

     hog.compute(img, descriptors); //���ü��㺯����ʼ����   
    
     CvMat* SVMtrainMat=cvCreateMat(1,descriptors.size(),CV_32FC1);     
       int  n=0;    
       for(vector<float>::iterator iter=descriptors.begin();iter!=descriptors.end();iter++)    
       {    
            cvmSet(SVMtrainMat,0,n,*iter);  
            n++;    
       }    
    
        int ret = svm.predict(SVMtrainMat);  //��ȡ���ռ����  

		CString a;

	if(ret == 0)
		a = "8";
	else if(ret == 1)
		a = "��";
	else if(ret == 2)
		a = "��";
	else if(ret == 3)
		a = "��";
	else if(ret == 4)
		a = "��";
	else if(ret == 5)
		a = "ô";
	else if(ret == 6)
		a = "��";
	else if(ret == 7)
		a = "ʲ";
	else if(ret == 8)
		a = "��";
	else if(ret == 9)
		a = "��";
	else 
		a = "С";

	
        std::sprintf( line, "%d\r\n",ret );   
        predict_txt<<line;
		//cvReleaseImage( &src1 );

		  predict_txt.close();
	    cvReleaseImage( &trainImg);    
       return a;		
	  // AfxMessageBox(a);
}



// ��������Ŀ¼��������Ŀ¼������*.txt������CStringArray��
void CameraDlg::getFolderDayFile(CString pathStr, CStringArray& arrStrFile)
{
    CString m_cstrFileList=_T(""); 
    CFileFind tempFind; 
    BOOL bFound; //�ж��Ƿ�ɹ��ҵ��ļ�
    bFound=tempFind.FindFile(_T("D:\\hand\\*.png"));   //�޸�" "�����ݸ��޶������ļ�����
    CString strTmp;   //����ҵ������ļ��� ����ļ���·��
    while(bFound)      //���������ļ�
    { 
        bFound=tempFind.FindNextFile(); //��һ��ִ��FindNextFile��ѡ�񵽵�һ���ļ����Ժ�ִ��Ϊѡ��
      
       
            strTmp=tempFind.GetFileTitle(); //�����ļ�����������׺��
			arrStrFile.Add(strTmp);
			//AfxMessageBox(strTmp);
            // �ڴ˴���Ӷ��ҵ��ļ��Ĵ���
       
    } 
    tempFind.Close(); 
    return; 
}    
const char*  CameraDlg::CStrToChar(CString strSrc)  
{  
#ifdef UNICODE  
    DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, strSrc.GetBuffer(0), -1, NULL, 0, NULL, FALSE);  
    char *psText;  
    psText = new char[dwNum];  
    if (!psText)  
        delete []psText;  
    WideCharToMultiByte(CP_OEMCP, NULL, strSrc.GetBuffer(0), -1, psText, dwNum, NULL, FALSE);  
    return (const char*)psText;  
#else  
    return (LPCTSRT)strSrc;  
#endif  
}




void CameraDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	svmTrain();
}





void CameraDlg::OnBnClickedButton4()
{
	
	USES_CONVERSION;	//��ʽת����־



	CDlgMain *parent_dlg = (CDlgMain *)m_pMianDlg;

	bool isChange = true;
	CString a=_T("");
	CString s=_T("");
	for(int i = 1;i<=10;i++)
	{

		if(flag)  break;
		(parent_dlg->m_image).SaveImage(_T(".\\hand.png"));
		IplImage* pFrame=cvLoadImage(".\\hand.png",1);
		cvShowImage("fd", pFrame);

		a = svmRecognize(pFrame);	
		if(a != s)
			isChange = true;
		else 
			isChange = false;
		s = a;
		if(isChange)
		{
			//�������
			(parent_dlg->m_speak).AddTextToPlayList(a, _T(""), TRUE);
			(parent_dlg->m_speak).StartAsynPlay();
			//��ʾ����
			GetDlgItem(IDC_EDIT1)->SetWindowText(a);
		}
		//nNum++;//֡��++
		//CString str;
		//str.Format(_T("D:/hand/%d.png"),nNum);
		//cvSaveImage(T2A(str),pFrame);

		 cvReleaseImage( &pFrame); 
		 //AfxMessageBox(_T("hh"));
		 cvWaitKey(2000);

	
	}

	

}


void CameraDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	flag=true;
	CDlgMain *parent_dlg = (CDlgMain *)m_pMianDlg;
	m_Camera.CloseWebCamera();
}
