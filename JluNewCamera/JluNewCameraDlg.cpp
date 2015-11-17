
// JluNewCameraDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "JluNewCamera.h"
#include "JluNewCameraDlg.h"
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CJluNewCameraDlg �Ի���




CJluNewCameraDlg::CJluNewCameraDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJluNewCameraDlg::IDD, pParent)
	, m_nImageWidth(0)
	, m_nImageHeight(0)
	, m_nImageChannels(0)
	, m_ProcMethod(0)
	, m_ObjectWidth(0)
	, m_ObjectHeight(0)
	, m_ObjectDistance(0)
	, m_ObjectDisparity(0)
	, m_nCornerSize_X(0)
	, m_nCornerSize_Y(0)
	, m_nSquareSize(0)
	, m_nBoards(0)
	, m_nID_RAD(0)
	, m_nMinDisp(0)
	, m_nMaxDisp(0)
	, m_nSADWinSiz(0)
	, m_nTextThres(0)
	, m_nDisp12MaxDiff(-1)
	, m_nPreFiltCap(0)
	, m_nUniqRatio(0)
	, m_nSpeckRange(0)
	, m_nSpeckWinSiz(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CJluNewCameraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDV_MinMaxInt(pDX, m_nCornerSize_X, 0, 50);
	DDV_MinMaxInt(pDX, m_nCornerSize_Y, 0, 50);
	DDV_MinMaxInt(pDX, m_nBoards, 0, 100);
	DDV_MinMaxInt(pDX, m_nMinDisp, -64, 16);
	DDV_MinMaxInt(pDX, m_nMaxDisp, 0, 240);
	DDV_MinMaxInt(pDX, m_nTextThres, 0, 50);
	DDV_MinMaxInt(pDX, m_nDisp12MaxDiff, -1, 16);
	DDV_MinMaxInt(pDX, m_nPreFiltCap, 0, 100);
	DDV_MinMaxInt(pDX, m_nUniqRatio, 0, 50);
	DDV_MinMaxInt(pDX, m_nSpeckRange, 0, 64);
	DDV_MinMaxInt(pDX, m_nSpeckWinSiz, 0, 200);
	DDX_Text(pDX, IDC_EDIT_speckWinSiz, m_nSpeckWinSiz);
	DDX_Text(pDX, IDC_EDIT_speckRange, m_nSpeckRange);
	DDX_Text(pDX, IDC_EDIT_uniqRatio, m_nUniqRatio);
	DDX_Text(pDX, IDC_EDIT_preFiltCap, m_nPreFiltCap);
	DDX_Text(pDX, IDC_e7ObjDist, m_ObjectDistance);
	DDX_Text(pDX, IDC_BoardWidth, m_nCornerSize_X);
	DDX_Text(pDX, IDC_BoardHeight, m_nCornerSize_Y);
	DDX_Text(pDX, IDC_SquareSize, m_nSquareSize);
	DDX_Text(pDX, IDC_EDIT_minDisp, m_nMinDisp);
	DDX_Text(pDX, IDC_nBoards, m_nBoards);
	DDX_Text(pDX, IDC_EDIT_maxDisp, m_nMaxDisp);
	DDX_Text(pDX, IDC_EDIT_SADWinSiz, m_nSADWinSiz);
	DDX_Text(pDX, IDC_EDIT_textThres, m_nTextThres);
	DDX_Text(pDX, IDC_EDIT_disp12MaxDiff, m_nDisp12MaxDiff);
}

BEGIN_MESSAGE_MAP(CJluNewCameraDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BN_DefaultCamCalibParam, &CJluNewCameraDlg::OnBnClickedBnDefaultcamcalibparam)
	ON_BN_CLICKED(IDC_BNDETECTAG, &CJluNewCameraDlg::OnBnClickedBndetectag)
	ON_BN_CLICKED(IDC_BN2StereoCalib, &CJluNewCameraDlg::OnBnClickedBn2stereocalib)
	ON_BN_CLICKED(IDC_BN_StereoDefParam, &CJluNewCameraDlg::OnBnClickedBnStereodefparam)
	ON_BN_CLICKED(IDC_BNGIVEDISP, &CJluNewCameraDlg::OnBnClickedBngivedisp)
	ON_BN_CLICKED(IDC_BN_CompDisp, &CJluNewCameraDlg::OnBnClickedBnCompdisp)
	ON_BN_CLICKED(IDC_RAD_BM, &CJluNewCameraDlg::OnBnClickedRadBm)
	ON_BN_CLICKED(IDC_RAD_SGBM, &CJluNewCameraDlg::OnBnClickedRadSgbm)
	ON_BN_CLICKED(IDC_BN_MOUSEON, &CJluNewCameraDlg::OnBnClickedBnMouseon)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_FACEDETECT, &CJluNewCameraDlg::OnBnClickedFacedetect)
	ON_BN_CLICKED(IDC_ONLYDISP, &CJluNewCameraDlg::OnBnClickedOnlydisp)
	ON_BN_CLICKED(IDC_SGBMTEST, &CJluNewCameraDlg::OnBnClickedSgbmtest)
END_MESSAGE_MAP()


// CJluNewCameraDlg ��Ϣ�������

BOOL CJluNewCameraDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CheckRadioButton(IDC_RAD_BOUGUET, IDC_RAD_BOUGUET, IDC_RAD_BOUGUET);				// Ĭ��ʹ��BOUGUET����˫ĿУ��
	CheckRadioButton(IDC_RAD_BM, IDC_RAD_SGBM, IDC_RAD_BM);	// Ĭ��ʹ�� BM �㷨�����Ӳ�	
	CheckRadioButton(IDC_RAD_CalibFromImg, IDC_RAD_CalibFromImg, IDC_RAD_CalibFromImg);
	m_nMaxDisp = 0;
	m_nSADWinSiz =0;
	m_nPreFiltCap =0;
	m_nSpeckRange = 0;
	UpdateData( FALSE );

	// ��ʼ��ͼ����ʾ�ؼ���ͼ��
	CRect rect;
	GetDlgItem(IDC_PicLfCam) ->GetClientRect( &rect );
	m_lfImage = Mat::zeros(rect.Height(), rect.Width(), CV_8UC3);
	GetDlgItem(IDC_PicRiCam) ->GetClientRect( &rect );
	m_riImage = Mat::zeros(rect.Height(), rect.Width(), CV_8UC3);
	GetDlgItem(IDC_PicSynImg) ->GetClientRect( &rect );
	m_disparity = Mat::zeros(rect.Height(), rect.Width(), CV_8UC3);
	//ʹһЩ�ؼ�������Ч״̬
	GetDlgItem(IDC_BN_CompDisp)->EnableWindow(FALSE);
	GetDlgItem(IDC_BN_MOUSEON)->EnableWindow(FALSE);
	GetDlgItem(IDC_BN2StereoCalib)->EnableWindow(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CJluNewCameraDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CJluNewCameraDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		CDialog::UpdateWindow();				// ����windows���ڣ�������ⲽ���ã�ͼƬ��ʾ�����������
		if (!m_lfImage.empty()||m_riImage.empty()||!m_disparity.empty())
		{
			F_ShowImage( m_lfImage, m_lfImage, IDC_PicLfCam );		// �ػ�ͼƬ����
			F_ShowImage( m_riImage, m_riImage, IDC_PicRiCam );		// �ػ�ͼƬ����
			F_ShowImage( m_disparity, m_disparity, IDC_PicSynImg );	// �ػ�ͼƬ����
		}
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CJluNewCameraDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int flag;
/*----------------------------
 * ���� : ��ʾͼ��
 *		 ��Ҫ���Ƶ�ͼ�� src ���Ƶ� des��Ȼ����Ƶ��ؼ���Ϊ ID �� Picture �ؼ�
 *----------------------------
 * ���� : CStereoVisionDlg::F_ShowImage
 * ���� : private 
 * ���� : void
 *
 * ���� : src	[in]	����ʾͼ��
 * ���� : des	[in]	����ͼ��
 * ���� : ID		[in]	ͼ�񴰿ڿؼ�ID
 */
void CJluNewCameraDlg::F_ShowImage(Mat& src, Mat& des, UINT ID)
{
	if (src.empty())
	{
		return;
	}
	// ���㽫ͼƬ���ŵ� Image ��������ı�������
	double wRatio = des.cols / (double)src.cols;
	double hRatio = des.rows / (double)src.rows;
	double srcWH = src.cols / (double)src.rows;
	double desWH = des.cols / (double)des.rows;
	double scale = srcWH > desWH ? wRatio : hRatio;

	// ���ź�ͼƬ�Ŀ�͸�
	int nw = (int)( src.cols * scale );
	int nh = (int)( src.rows * scale );

	// Ϊ�˽����ź��ͼƬ���� des �����в�λ�������ͼƬ�� des ���Ͻǵ���������ֵ
	int tlx = (int)((des.cols - nw) / 2);
	int tly = (int)((des.rows - nh) / 2);

	// ���� des �� ROI ������������ͼƬ img
	Mat desRoi = des(Rect(tlx, tly, nw, nh));

	// ���src�ǵ�ͨ��ͼ����ת��Ϊ��ͨ��ͼ��
	if (src.channels() == 1)
	{
		Mat src_c;
		cvtColor(src, src_c, CV_GRAY2BGR);
		// ��ͼƬ src_t �������ţ������뵽 des ��
		resize(src_c, desRoi, desRoi.size());
	}
	else
	{
		// ��ͼƬ src �������ţ������뵽 des ��
		resize( src, desRoi, desRoi.size() );
	}

	CDC* pDC = GetDlgItem( ID ) ->GetDC();		// �����ʾ�ؼ��� DC
	HDC hDC = pDC ->GetSafeHdc();				// ��ȡ HDC(�豸���) �����л�ͼ����
	CRect rect;
	GetDlgItem(ID) ->GetClientRect( &rect );	// ��ȡ�ؼ��ߴ�λ��
	CvvImage cimg;
	IplImage cpy = des;
	cimg.CopyOf( &cpy );						// ����ͼƬ
	cimg.DrawToHDC( hDC, &rect );				// ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������
	ReleaseDC( pDC );
}

/*----------------------------
 * ���� : �������ļ��Ի���ѡ�񵥸������ļ�
 *----------------------------
 * ���� : CStereoVisionDlg::DoSelectFiles
 * ���� : private 
 * ���� : selectedFiles	ѡ����ļ���·������
 *
 * ���� : lpszDefExt			[in]	�ļ�Ĭ�ϸ�ʽ
 * ���� : dwFlags			[in]	�Ի���ѡ��
 * ���� : lpszFilter			[in]	�ļ���ʽ��������
 * ���� : lpstrTitle			[in]	�Ի������
 * ���� : lpstrInitialDir	[in]	�Ի���ĳ�ʼ·��
 */
vector<CStringA> CJluNewCameraDlg::DoSelectFiles(
	LPCTSTR	lpszDefExt,
	DWORD	dwFlags,
	LPCTSTR	lpszFilter,
	LPCWSTR	lpstrTitle,
	LPCWSTR	lpstrInitialDir )
{
	vector<CStringA> selectedFiles;
	POSITION filePosition;
	DWORD MAXFILE = 4000;  
	TCHAR* pc = new TCHAR[MAXFILE];  

	CFileDialog dlg( TRUE, lpszDefExt, NULL, dwFlags, lpszFilter, NULL );	
	
	dlg.m_ofn.nMaxFile = MAXFILE; 
	dlg.m_ofn.lpstrFile = pc;   
	dlg.m_ofn.lpstrFile[0] = NULL; 
	dlg.m_ofn.lpstrTitle = lpstrTitle;
	dlg.m_ofn.lpstrInitialDir = lpstrInitialDir;

	if( dlg.DoModal() == IDOK )
	{
		filePosition = dlg.GetStartPosition();
		while(filePosition != NULL)   
		{   
			CStringA path;
			path = dlg.GetNextPathName(filePosition);
			selectedFiles.push_back( path );  
		}  
	}

	delete []pc;
	return selectedFiles;
}

void CJluNewCameraDlg::OnBnClickedBnDefaultcamcalibparam()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nCornerSize_X = 9;
	m_nCornerSize_Y = 6;
	m_nBoards = 20;
	m_nSquareSize = 20.0f;
	UpdateData(FALSE);
	CheckRadioButton(IDC_RAD_CalibFromImg, IDC_RAD_CalibFromImg, IDC_RAD_CalibFromImg);
	return;

}

/************************
Ϊ�ֿ��ǵ���ͱ궨�������ȫ�ֱ���
***************************/

calib::CornerDatas cornerDatas;
calib::StereoParams stereoParams;
calib::RemapMatrixs remapMatrixs;
CJluNewCameraDlg::OptionCameraCalib optCalib;
void CJluNewCameraDlg::OnBnClickedBndetectag()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*���г�ʼ��
	*/
	GetDlgItem(IDC_BN2StereoCalib)->EnableWindow(TRUE);
	const char* cornerFile = "CornerData.yml";
	int nFoundBoard = 0,nFrame=0;
	vector<CStringA> img0Files, img1Files;
	const char* img0_file = NULL, *img1_file = NULL;
	cv::Mat frame0, frame1, img0, img1;
	cv::Size imageSize;
	GetDlgItem(IDC_BN2StereoCalib)->EnableWindow(FALSE);
	UpdateData(TRUE);
	
	try
	{
		
		optCalib.cornerSize.width = m_nCornerSize_X; 	// ���̽ǵ��� (nx, ny)
	    optCalib.cornerSize.height = m_nCornerSize_Y;
	    optCalib.numberBoards = m_nBoards;				// ������̴���
	    optCalib.squareSize = m_nSquareSize;
		m_nID_RAD = GetCheckedRadioButton(IDC_RAD_CalibFromImg, IDC_RAD_CalibFromImg);
	
		optCalib.readLocalImage = m_nID_RAD == IDC_RAD_CalibFromImg;
		if(optCalib.readLocalImage)		// ���ӱ���ͼƬ���룬����֡������Ϊ 5 ֡
			optCalib.numberFrameSkip = 5;
		if(optCalib.readLocalImage)
		{
				
			img0Files = DoSelectFiles(
				_T("*.bmp"), 
				OFN_ENABLESIZING   |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("ѡ������ͼ�ļ�"),
				_T("Imgs\\Left"));
				img1Files = DoSelectFiles(
					_T("*.bmp"), 
					OFN_ENABLESIZING   |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
					_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
					_T("ѡ������ͼ�ļ�"),
					_T("Imgs\\Right"));//����ѡ��֮���Ժ󴴽����ļ���ֻҪû��ָ��·�����˾�Ϊ����Ĭ��·����������
				
				if( img0Files.empty() )	// �ж��Ƿ���ͼƬ
				{
					LPCTSTR errMsg = _T("û��ѡ����Ч��ͼ���ļ���������ѡ��!");
					throw errMsg;
				}
				
				img0_file = img0Files[ 0 ];
				img0 = cvLoadImage(img0_file);
				if(img0.rows>1000)
				{
					cv::resize(img0,img0,Size(img0.cols/6,img0.rows/6));
				//	cv::resize(img1,img1,Size(img1.cols/6,img1.rows/6));
						//AfxMessageBox(_T("lslslsl"));
				}
				imageSize = img0.size();

				if (false == img1Files.empty())
				{
					optCalib.numberBoards = MIN(optCalib.numberBoards, MIN(img0Files.size(), img1Files.size()));
					optCalib.doStereoCalib = true;
				}
				else
				{
					optCalib.doStereoCalib = false;
					optCalib.numberBoards = MIN(optCalib.numberBoards, img0Files.size());
				}
				m_stereoCalibrator.initCornerData(optCalib.numberBoards, imageSize, optCalib.cornerSize, optCalib.squareSize, cornerDatas);
			
				// ��ʼ���ǵ�
				//MSG msg;
				while(nFoundBoard < optCalib.numberBoards)
				{

					// ����ͼ��
					if(optCalib.readLocalImage)	// �ӱ���ͼƬ
					{
						img0_file = img0Files[ nFoundBoard ];
						frame0 = cvLoadImage(img0_file);
					// ����ͼ��
						img0 = frame0.clone();
						if(img0.rows>1000)
						{
							cv::resize(img0,img0,Size(img0.cols/6,img0.rows/6));
						//	cv::resize(img1,img1,Size(img1.cols/6,img1.rows/6));
						//AfxMessageBox(_T("lslslsl"));
						}
						if (optCalib.doStereoCalib)
						{
							img1_file = img1Files[ nFoundBoard ];
							frame1 = cvLoadImage(img1_file);
							img1 = frame1.clone();
							if(img1.rows>1000)
							{
								//cv::resize(img0,img0,Size(img0.cols/6,img0.rows/6));
								cv::resize(img1,img1,Size(img1.cols/6,img1.rows/6));
						//AfxMessageBox(_T("lslslsl"));
							}
						}
					} 
		//			if (optCalib.doStereoCalib) img1 = frame1.clone();
					if(img0.rows>1000)
					{
						cv::resize(img0,img0,Size(img0.cols/6,img0.rows/6));
						cv::resize(img1,img1,Size(img1.cols/6,img1.rows/6));
						//AfxMessageBox(_T("lslslsl"));
					}
					// ���ǵ�
					if ( m_stereoCalibrator.detectCorners(img0, img1, cornerDatas, nFoundBoard) )
					{
						//if (nFrame++ > optCalib.numberFrameSkip)
						//{
							//������ͼ
						/*	if (optCalib.readLocalImage == false)
							{
								CStringA imgName( m_workDir );
								imgName.AppendFormat("Images\\left%03d.jpg",nFoundBoard);
								string imgname = imgName.GetBuffer(0);
								imwrite(imgname, frame0);

								if (optCalib.doStereoCalib) 
								{
									imgName = m_workDir;
									imgName.AppendFormat("Images\\right%03d.jpg",nFoundBoard);
									imgname = imgName.GetBuffer(0);
									imwrite(imgname, frame1);
								}
							}*/

							nFoundBoard++; 
							nFrame = 0;
						//}

						if (nFoundBoard > 0 && nFrame < 5)
						{
							//ʹͼ��ɫ������ͬʱ�ҵ����������̽ǵ�
							bitwise_not(img0, img0);
							if (optCalib.doStereoCalib) bitwise_not(img1, img1);
						}
					} // --End "if ( m_stereoCalibrator.detectCorners )"

					// ��ʾ��⵽�Ľǵ�
					F_ShowImage( img0, m_lfImage, IDC_PicLfCam );
					F_ShowImage( img1, m_riImage, IDC_PicRiCam ); 
				} // --End "while(nFoundBoard < optCalib.numberBoards) "
			
				if (nFoundBoard < 4)
				{
				//	LPCTSTR errMsg = _T("���ɹ�������ͼ����С��4�����˳�˫Ŀ�궨!");
				//	throw errMsg;
					CString str;
				//	str.Format("%d",nFoundBoard);
					str.Format(_T("%d"),nFoundBoard);
					AfxMessageBox(str);

				}
				else if (nFoundBoard != optCalib.numberBoards)
				{
					optCalib.numberBoards = nFoundBoard;
					m_stereoCalibrator.resizeCornerData(optCalib.numberBoards, cornerDatas);
				}
			
				// ����ǵ���������
				m_stereoCalibrator.saveCornerData(cornerFile, cornerDatas);
				GetDlgItem(IDC_BN2StereoCalib)->EnableWindow(TRUE);
				AfxMessageBox(_T("���̽ǵ������"));
			// �ѻ�ȡ�ǵ���������
		} 
		}
	catch (LPCTSTR errMsg)
	{
		AfxMessageBox(errMsg);
	}
	catch (cv::Exception& e)
	{
		char err[2048];
		sprintf_s(err, "��������: %s", e.what());
		CStringW errInfo;
		errInfo = err;
		AfxMessageBox(errInfo);
	}
	catch (...)
	{
		AfxMessageBox(_T("����δ֪����"));
	}
}


void CJluNewCameraDlg::OnBnClickedBn2stereocalib()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	stereoParams.cameraParams1.flags = optCalib.flagCameraCalib;
//	stereoParams.cameraParams2.flags = optCalib.flagCameraCalib;
	stereoParams.flags = 0;//CV_CALIB_FIX_PRINCIPAL_POINT|CV_CALIB_USE_INTRINSIC_GUESS|CV_CALIB_FIX_ASPECT_RATIO|CV_CALIB_SAME_FOCAL_LENGTH
	//bool needCalibSingleCamera = TRUE;
	bool needCalibSingleCamera = FALSE;
	stereoParams.alpha=-1;
	m_stereoCalibrator.calibrateStereoCamera(cornerDatas, stereoParams, needCalibSingleCamera);

	// ����궨���
	double avgErr = 0;
	m_stereoCalibrator.getStereoCalibrateError(cornerDatas, stereoParams, avgErr);
	char info[50];
	sprintf_s( info, "�궨��� = %7.4g", avgErr );
	CString ss;
	ss = info;
	AfxMessageBox(ss);
	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_BOUGUET, IDC_RAD_BOUGUET);
	optCalib.rectifyMethod = m_nID_RAD == IDC_RAD_BOUGUET ? calib::RECTIFY_BOUGUET : calib::RECTIFY_HARTLEY;		
			// ִ��˫ĿУ��
	m_stereoCalibrator.rectifyStereoCamera(cornerDatas, stereoParams, remapMatrixs, optCalib.rectifyMethod);
	//�õ���ͶӰ�����У��ӳ�����
	AfxMessageBox(_T("�����˫ĿУ��"));
			
	// ��������ͷ�������	
	m_stereoCalibrator.saveCalibrationDatas("calib_paras.xml"/*����Ϊ�ɱ��������ļ�ȷ��*/, optCalib.rectifyMethod, cornerDatas, stereoParams, remapMatrixs);
	AfxMessageBox(_T("�ѱ��涨�����"));
}


void CJluNewCameraDlg::OnBnClickedBnStereodefparam()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_BM, IDC_RAD_SGBM);
	CheckRadioButton(IDC_RAD_DispFromImg, IDC_RAD_DispFromImg, IDC_RAD_DispFromImg);
	if (m_nID_RAD == IDC_RAD_BM)
	{
		m_nMinDisp = 0;	
		m_nMaxDisp = 144;
		m_nSADWinSiz = 53;
		m_nTextThres = 10;
		m_nDisp12MaxDiff = 1;
		m_nPreFiltCap = 31;
		m_nUniqRatio = 25;
		m_nSpeckRange = 32;
		m_nSpeckWinSiz = 100;
		UpdateData(FALSE);
	} 
	else if(m_nID_RAD == IDC_RAD_SGBM)
	{
		m_nMinDisp = 0;	
		m_nMaxDisp = 144;
		m_nSADWinSiz = 25;
		m_nDisp12MaxDiff = 1;
		m_nPreFiltCap = 63;
		m_nUniqRatio = 20;
		m_nSpeckRange = 32;
		m_nSpeckWinSiz = 100;
//		m_nUniqRatio = 10;
//		sgbm.P1 = 8*cn*sgbm.SADWindowSize*sgbm.SADWindowSize;
//       sgbm.P2 = 32*cn*sgbm.SADWindowSize*sgbm.SADWindowSize;
//		m_pCheck = (CButton*)GetDlgItem(IDC_CHK_fullDP);
//		m_pCheck->SetCheck(0);
		UpdateData(FALSE);
	}
	
}
void CJluNewCameraDlg::FixDisp(Mat_<float> & disp,int numofdisp)
{
	Mat_<float> disp1;
	float lastPixel = 10;
	int minDisparity = 23;
//	disp.at<float>(0,144) = lastPixel;
	for (int i = 0; i < disp.rows; i++)
	{
		for (int j = numofdisp; j < disp.cols; j++)
		{
			if (disp(i,j) <= minDisparity) disp(i,j) = lastPixel;
			else lastPixel = disp(i,j);
		}
	}
	int an = 4;
	copyMakeBorder(disp, disp1, an,an,an,an, BORDER_REPLICATE);
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(an*2+1, an*2+1));
	morphologyEx(disp1, disp1, CV_MOP_OPEN, element);
	morphologyEx(disp1, disp1, CV_MOP_CLOSE, element);
	disp = disp1(Range(an, disp.rows-an), Range(an, disp.cols-an)).clone();
}
cv::Mat img1, img2, img1p, img2p, disp8u, pointCloud;
cv::Mat disp;
StereoMatch m_stereoMatcher;

void CJluNewCameraDlg::OnBnClickedBngivedisp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_BN_CompDisp)->EnableWindow(TRUE);
	CJluNewCameraDlg::OptionCameraCalib opt;
//	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_BM, IDC_RAD_BM);
//	opt.stereoMethod = m_nID_RAD == IDC_RAD_BM ? STEREO_BM :
//		m_nID_RAD == IDC_RAD_SGBM ? STEREO_SGBM : STEREO_BM;
//	m_nID_RAD=STEREO_BM;
	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_DispFromImg, IDC_RAD_DispFromImg);
	opt.readLocalImage = m_nID_RAD == IDC_RAD_DispFromImg;
	CStringA xmlPath;			// �����������ļ�
	vector<CStringA> imgFiles1; //������ͼ�ļ�·������
	vector<CStringA> imgFiles2;	
	OptionStereoMatch optMatch;
	int i = 0, j = 0;
	const char* img1_filename = NULL;
	const char* img2_filename = NULL;
	const char* xml_filename = NULL;

//	cv::Mat img1, img2, img1p, img2p, disp, disp8u, pointCloud;
	LPCTSTR errMsg;
	try
	{
		if (opt.readLocalImage)
		{
			// ѡ������ͼ
			imgFiles1 = DoSelectFiles(
				_T("*.bmp"), 
				OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("ѡ������ͼͼ��"),
				m_workDir
				);
			// ѡ������ͼ
			imgFiles2 = DoSelectFiles(
				_T("*.bmp"), 
				OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("ѡ������ͼͼ��"),
				m_workDir
				);

			if( imgFiles1.empty() || imgFiles2.empty() )	
			{
				errMsg = _T("û��ѡ����Ч��ͼ���ļ�!");
				throw errMsg;
			}

			img1_filename = imgFiles1[0];
			img2_filename = imgFiles2[0];
			img1 = imread(img1_filename);
			img2 = imread(img2_filename);
			if(img1.rows>1000)
			{
				cv::resize(img1,img1,Size(img1.cols/6,img1.rows/6));
				cv::resize(img2,img2,Size(img2.cols/6,img2.rows/6));
			//AfxMessageBox(_T("lslslsl"));
			}
		} 
	}
	catch (LPCTSTR ErrMsg)
	{
		AfxMessageBox(ErrMsg);
		return;
	}
	catch (cv::Exception& e)
	{
		char err[2048];
		sprintf_s(err, "��������: %s", e.what());
		CStringW errInfo;
		errInfo = err;
		AfxMessageBox(errInfo);
		return;
	}
	catch (...)
	{
		AfxMessageBox(_T("����δ֪����"));
		return;
	}
	try
	{
		vector<CStringA> xmlFiles;
		xmlFiles = DoSelectFiles(
			_T("*.xml"), 
			OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
			_T("XML/YML file (*.xml; *.yml) |*.xml; *.yml | All Files (*.*) |*.*||"), 
			_T("ѡ������ͷ��������ļ�"),
			m_workDir
			);
		if( xmlFiles.empty() )	
		{
			errMsg = _T("û��ѡ����Ч������ͷ��������ļ�!");			
			throw errMsg;
		}
		xmlPath = xmlFiles[0];			// ��ȡxml�ļ�·��
		xml_filename = xmlPath;
	//	StereoMatch m_stereoMatcher;
		// ��������ͷ�������
		switch (m_stereoMatcher.init(img1.cols, img1.rows, xml_filename))
		{
		case 0:
		case -99:
		errMsg = _T("��ȡ����ͷ��������ļ�ʧ�ܣ�������ѡ��!");			
		throw errMsg;
		case -1:
				errMsg = _T("���������ͼ��ߴ��뵱ǰ���õ�ͼ��ߴ粻һ�£�������ѡ��!");			
				throw errMsg;
				break;
		}
	}
	catch (LPCTSTR ErrMsg)
	{
		AfxMessageBox(ErrMsg);
		return;
	}
	catch (cv::Exception& e)
	{
		char err[2048];
		sprintf_s(err, "��������: %s", e.what());
		CStringW errInfo;
		errInfo = err;
		AfxMessageBox(errInfo);
		return;
	}
	catch (...)
	{
		AfxMessageBox(_T("����δ֪����"));
		return;
	}
	m_stereoMatcher.m_BM.state->disp12MaxDiff = m_nDisp12MaxDiff;
	m_stereoMatcher.m_SGBM.disp12MaxDiff = m_nDisp12MaxDiff;
	int frameCount = 0;	//ͼ�����
	m_nID_RAD = GetCheckedRadioButton(IDC_RAD_BM, IDC_RAD_SGBM);
	optMatch.stereoMethod = m_nID_RAD == IDC_RAD_BM ? STEREO_BM :
		m_nID_RAD == IDC_RAD_SGBM ? STEREO_SGBM : STEREO_BM;
	while(true)
	{
		if (frameCount >= MIN(imgFiles1.size(), imgFiles2.size()))
					break;
		img1_filename = imgFiles1[frameCount];
		img2_filename = imgFiles2[frameCount];
		img1 = imread(img1_filename, 1);
		img2 = imread(img2_filename, 1);
		if(img1.rows>1000)
		{
			cv::resize(img1,img1,Size(img1.cols/6,img1.rows/6));
			cv::resize(img2,img2,Size(img2.cols/6,img2.rows/6));
			//AfxMessageBox(_T("lslslsl"));
		}
		if(img1.empty() || img2.empty()) break;
		frameCount++;
		//����update_state_BM
		if (optMatch.stereoMethod == STEREO_BM)
		{
			UpdateData(TRUE);
			m_stereoMatcher.m_BM.state->preFilterCap = m_nPreFiltCap;
			m_stereoMatcher.m_BM.state->SADWindowSize = m_nSADWinSiz;
			m_stereoMatcher.m_BM.state->minDisparity = m_nMinDisp;
			m_stereoMatcher.m_BM.state->numberOfDisparities = m_nMaxDisp;
			m_stereoMatcher.m_BM.state->textureThreshold = m_nTextThres;
			m_stereoMatcher.m_BM.state->uniquenessRatio = m_nUniqRatio;
			m_stereoMatcher.m_BM.state->speckleWindowSize = m_nSpeckWinSiz;
			m_stereoMatcher.m_BM.state->speckleRange = m_nSpeckRange;
		//	m_stereoMatcher.m_BM.state->preFilterSize=41;
			m_stereoMatcher.bmMatch(img1, img2, disp, img1p, img2p);//BM�㷨
		}
		else if (optMatch.stereoMethod == STEREO_SGBM)
		{
//			DoUpdateStateSGBM(img1.channels());
			int imgChannels=img1.channels();
			UpdateData(TRUE);
			m_stereoMatcher.m_SGBM.preFilterCap = m_nPreFiltCap;
			m_stereoMatcher.m_SGBM.SADWindowSize = m_nSADWinSiz;
			m_stereoMatcher.m_SGBM.P1 =  48 * imgChannels * m_nSADWinSiz * m_nSADWinSiz;
			m_stereoMatcher.m_SGBM.P2 = 48 * imgChannels * m_nSADWinSiz * m_nSADWinSiz;
			m_stereoMatcher.m_SGBM.minDisparity = m_nMinDisp;
			m_stereoMatcher.m_SGBM.numberOfDisparities = m_nMaxDisp;
			m_stereoMatcher.m_SGBM.uniquenessRatio = m_nUniqRatio;
			m_stereoMatcher.m_SGBM.speckleWindowSize = m_nSpeckWinSiz;
			m_stereoMatcher.m_SGBM.speckleRange = m_nSpeckRange;
			m_stereoMatcher.m_SGBM.fullDP = true;
			m_stereoMatcher.sgbmMatch(img1, img2, disp, img1p, img2p);
			
		}
		for( j = 0; j < img1p.rows; j += 32 )		
		{
			line( img1p, cvPoint(0,j),	cvPoint(img1p.cols,j), CV_RGB(0,255,0)); 
			line( img2p, cvPoint(0,j),	cvPoint(img2p.cols,j), CV_RGB(0,255,0)); 
		}
		//�����Ӳ�ͼ�񵽱����ļ���
/*		std::string str="./";
		cv::imwrite(str+"disp1.jpg",disp);
		imshow("222llll",disp);
		///
		Mat_<float> disptemp;
		disp.convertTo(disptemp,CV_32FC1,1.0/16);
		imshow("llll",disptemp);
	//	FixDisp(disptemp,m_nMaxDisp);
		std::string str1="./";
		cv::imwrite(str1+"disp.jpg",disptemp);
		imshow("llll2",disptemp);*/
    	m_stereoMatcher.getDisparityImage(disp, disp8u, true);//�õ�α��
//		imshow("lslsl",disp8u);
		F_ShowImage( img1p, m_lfImage, IDC_PicLfCam );
		F_ShowImage( img2p, m_riImage, IDC_PicRiCam );
		F_ShowImage( disp8u, m_disparity, IDC_PicSynImg );
/*		NamedWindow("lslsls",CV_WINDOW_AUTOSIZE);
	    imshow("lslsls",disp8u);
	    waitKey(0);*/
	}
}


void CJluNewCameraDlg::OnBnClickedBnCompdisp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_BN_MOUSEON)->EnableWindow(TRUE);
	m_stereoMatcher.getPointClouds(disp, pointCloud);//������ά���Ʋ�����Y�ᷴת
	vector<PointCloudAnalyzer::ObjectInfo> objectInfos;
	PointCloudAnalyzer pointCloudAnalyzer;
	pointCloudAnalyzer.detectNearObject(disp8u, pointCloud, objectInfos);////////
	pointCloudAnalyzer.showObjectInfo(objectInfos, img1p);
	m_ObjectDistance = objectInfos[0].distance; m_ObjectDistance = (int)(m_ObjectDistance * 10000) / 10000.;
	m_ObjectDistance=-1*m_ObjectDistance;
	UpdateData(FALSE);
	F_ShowImage( img1p, m_lfImage, IDC_PicLfCam );
	F_ShowImage( img2p, m_riImage, IDC_PicRiCam );
	F_ShowImage( disp8u, m_disparity, IDC_PicSynImg );
}

void CJluNewCameraDlg::DoClearParamsOfStereoMatch(void)
{
	m_nMinDisp = 0;	
	m_nMaxDisp = 0;
	m_nSADWinSiz = 0;
	m_nTextThres = 0;
	m_nDisp12MaxDiff = -1;
	m_nPreFiltCap = 0;
	m_nUniqRatio = 0;
	m_nSpeckRange = 0;
	m_nSpeckWinSiz = 0;
	UpdateData(FALSE);
	return;
}
void CJluNewCameraDlg::OnBnClickedRadBm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DoClearParamsOfStereoMatch();
	CheckRadioButton(IDC_RAD_BM, IDC_RAD_SGBM, IDC_RAD_BM);
	GetDlgItem(IDC_EDIT_disp12MaxDiff)->EnableWindow(FALSE);

}


void CJluNewCameraDlg::OnBnClickedRadSgbm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DoClearParamsOfStereoMatch();
	CheckRadioButton(IDC_RAD_BM, IDC_RAD_SGBM, IDC_RAD_SGBM);
}

void CJluNewCameraDlg::OnBnClickedBnMouseon()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	moupoint.x=5;
	moupoint.y=5;
	vector<cv::Mat> xyzSet;
	split(pointCloud, xyzSet);
	cv::Mat depth;
	xyzSet[2].copyTo(depth);
	cv::namedWindow("��������",1);
	flag=1;
	while(flag)
	{
		imshow("��������",disp8u);
		cv::setMouseCallback( "��������",On_Mouse, 0 );
	
		if(moupoint.x>20)
		{
			flag=1;
			m_ObjectDistance=depth.at<float>(moupoint);
		//	m_ObjectDistance=depth.ptr<float>(moupoint.x)[moupoint.y];
			m_ObjectDistance=-1*m_ObjectDistance;
			if(m_ObjectDistance>0)
			{
			    UpdateData(FALSE);
			}
		}
	
	//	cv::waitKey(15);
		if( waitKey(100) == 27 )
			break;
	}
	destroyWindow("��������");
}


void CJluNewCameraDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	AfxMessageBox(_T("errInfo"));
//	CDialogEx::OnLButtonDown(nFlags, point);
/*	if(flag==1)
	{
		moupoint.x=5;
		moupoint.y=5;
		vector<cv::Mat> xyzSet;
		split(pointCloud, xyzSet);
		cv::Mat depth;
		xyzSet[2].copyTo(depth);
		CRect rect;
	 //this->GetClientRect(&rect);
	   (this->GetDlgItem(IDC_PicSynImg))->GetWindowRect(&rect);
	   ScreenToClient(rect);
	   // CPoint p(rect.right,rect.bottom);
/*	   CRect rect;
       m_edit->GetWindowRect(&rect);   //ȡ�ÿؼ���ȫ������
       this->ScreenToClient(&rect);        //ת�ɿͻ��������꣬thisָ��ؼ����ڵĴ��ڡ�
	   moupoint.x=point.x-rect.left+50;
	   moupoint.y=point.y-rect.top+50;
	   CString str;
     //str.Format("%d",nFoundBoard);
	   str.Format(_T("%d"),moupoint.y);
//	   AfxMessageBox(str);
	   if(moupoint.x>10&&moupoint.y>10)
		{
			m_ObjectDistance=depth.at<float>(moupoint);
		//	m_ObjectDistance=depth.ptr<float>(moupoint.x)[moupoint.y];
			m_ObjectDistance=-2*m_ObjectDistance;
			if(m_ObjectDistance>0)
			{
			    UpdateData(FALSE);
			}
		}
	}*/
}


void CJluNewCameraDlg::OnBnClickedFacedetect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ʼ��
	vector<CStringA> imgfaceFiles1; //������ͼ�ļ�·������
	vector<CStringA> imgfaceFiles2;	
	const char* img1_filename = NULL;
	const char* img2_filename = NULL;
	Mat faceimg1,faceimg2;
//	LPCTSTR errMsg;
	imgfaceFiles1 = DoSelectFiles(
				_T("*.bmp"), 
				OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.pgm; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("ѡ������ͼͼ��"),
				m_workDir
				);		// ѡ������ͼ

	if( imgfaceFiles1.empty() )	
	{
		//errMsg = _T("û��ѡ����Ч��ͼ���ļ�!");
		//throw errMsg;
		AfxMessageBox(_T("û��ѡ��ͼ���ļ���"));
		return;
	}
	img1_filename=imgfaceFiles1[0];
//	img2_filename=imgfaceFiles2[0];
	faceimg1=imread(img1_filename);
//	faceimg2=imread(img2_filename);
	int width=faceimg1.cols;
	int height=faceimg1.rows;
	//�����������
	string fn_haar = "E:\\wanghao\\FaceRecognizer\\haarcascade_frontalface_alt2.xml";
	CascadeClassifier haar_cascade;
    haar_cascade.load(fn_haar);
//	resize(faceimg1,faceimg1,Size(width/4,height/4),1.0,1.0,INTER_CUBIC);
	Mat gray;
    cvtColor(faceimg1, gray, CV_BGR2GRAY);
        // Find the faces in the frame:
    vector< Rect_<int> > faces;
	Mat imgrect;
    haar_cascade.detectMultiScale(gray, faces,1.3,4,0|CV_HAAR_SCALE_IMAGE,Size(30, 30));	
	for(int i=0;i<faces.size();i++)
	{
	
		
	Rect face1=faces[i];
//	Size size(20,20);
//	Rect facetemp=
//	face1=Rect(face1.tl(),face1.br()*1.5);
//	face1=face1+face1.size();
	/*
	Rect temp=Rect(face1.tl().x*0.8,face1.tl().y*0.4,face1.width*1.6,face1.height*1.7);*/
	imgrect=faceimg1(face1);
	rectangle(faceimg1, face1, CV_RGB(0, 255,0), 1);
	
	}
	Size dsize=Size(92,112);
	resize(imgrect,imgrect,dsize);
	cv::cvtColor(imgrect,imgrect,CV_BGR2GRAY);
	imshow("lslsl",faceimg1);
	imshow("haha",imgrect);
	imwrite("../test.pgm",imgrect);

}


void CJluNewCameraDlg::OnBnClickedOnlydisp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	vector<CStringA> imgFiles1; //������ͼ�ļ�·������
	vector<CStringA> imgFiles2;	
	//OptionStereoMatch optMatch;
	int i = 0, j = 0;
	const char* img1_filename = NULL;
	const char* img2_filename = NULL;
	const char* xml_filename = NULL;
	imgFiles1 = DoSelectFiles(
				_T("*.bmp"), 
				OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("ѡ������ͼͼ��"),
				m_workDir
				);
			// ѡ������ͼ
			imgFiles2 = DoSelectFiles(
				_T("*.bmp"), 
				OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("ѡ������ͼͼ��"),
				m_workDir
				);

			if( imgFiles1.empty() || imgFiles2.empty() )	
			{
			//	errMsg = _T("û��ѡ����Ч��ͼ���ļ�!");
			//	throw errMsg;
			}
			img1_filename = imgFiles1[0];
			img2_filename = imgFiles2[0];
			IplImage * cv_left_rectified;
            IplImage * cv_right_rectified;
             cv_left_rectified = cvLoadImage( img1_filename, CV_LOAD_IMAGE_GRAYSCALE);
             cv_right_rectified = cvLoadImage( img2_filename, CV_LOAD_IMAGE_GRAYSCALE);
             CvSize size = cvGetSize( cv_left_rectified );
			CvMat * disparity_left = cvCreateMat(size.height,size.width,CV_16S);
			CvMat * disparity_right = cvCreateMat(size.height,size.width,CV_16S);	
////		
			m_stereoMatcher.GcMatch(cv_left_rectified,cv_right_rectified,disparity_left,disparity_right);
		/////
			// CV_BGR2GRAY
}


void CJluNewCameraDlg::OnBnClickedSgbmtest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	vector<CStringA> imgFiles1; //������ͼ�ļ�·������
	vector<CStringA> imgFiles2;	
	//OptionStereoMatch optMatch;
	int i = 0, j = 0;
	const char* img1_filename = NULL;
	const char* img2_filename = NULL;
	const char* xml_filename = NULL;
	imgFiles1 = DoSelectFiles(
				_T("*.bmp"), 
				OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("ѡ������ͼͼ��"),
				m_workDir
				);
			// ѡ������ͼ
			imgFiles2 = DoSelectFiles(
				_T("*.bmp"), 
				OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("ѡ������ͼͼ��"),
				m_workDir
				);

			if( imgFiles1.empty() || imgFiles2.empty() )	
			{
			//	errMsg = _T("û��ѡ����Ч��ͼ���ļ�!");
			//	throw errMsg;
			}
			img1_filename = imgFiles1[0];
			img2_filename = imgFiles2[0];
			img1 = imread(img1_filename, 1);
		//	imshow("lsls1",img1);
	     	img2 = imread(img2_filename, 1);
		//	imshow("lsls2",img2);
			cv::cvtColor(img1,img1,CV_BGR2GRAY);
			cv::cvtColor(img2,img2,CV_BGR2GRAY);
		    //if(img1.empty() || img2.empty()) break;
			int imgChannels=img1.channels();
			m_stereoMatcher.m_SGBM.preFilterCap = 63;
			m_stereoMatcher.m_SGBM.SADWindowSize = 9;
			m_stereoMatcher.m_SGBM.P1 =  8 * imgChannels * m_nSADWinSiz * m_nSADWinSiz;
			m_stereoMatcher.m_SGBM.P2 = 32 * imgChannels * m_nSADWinSiz * m_nSADWinSiz;
			m_stereoMatcher.m_SGBM.minDisparity = 0;
			m_stereoMatcher.m_SGBM.numberOfDisparities = 64;
			m_stereoMatcher.m_SGBM.uniquenessRatio = 10;
			m_stereoMatcher.m_SGBM.speckleWindowSize = 100;
			m_stereoMatcher.m_SGBM.speckleRange = 32;
			m_stereoMatcher.m_SGBM.disp12MaxDiff = 1;
			m_stereoMatcher.sgbmMatch(img1, img2, disp, img1p, img2p);
			imshow("lsls",disp);

}
