
// JluNewCameraDlg.h : ͷ�ļ�
//

//#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "stdlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "afxdialogex.h"
#include "calib.h"
#include "match.h"
#include "Point_Analyze.h"
#include "string.h"
#include "cvaux.h"
#include "cxcore.h"
#include "highgui.h"
#include "cv.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
//#include "camerads.h"

#include "CvvImage.h"
#include "calib.h"
//#include "StereoMatch.h"
//#include "PointCloudAnalyzer.h"

using namespace std;
using namespace cv;
// CJluNewCameraDlg �Ի���
static cv::Point moupoint;
class CJluNewCameraDlg : public CDialogEx
{
// ����
public:
	CJluNewCameraDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void FixDisp(Mat_<float> & disp,int numofdisp);
// �Ի�������
	enum { IDD = IDD_JLUNEWCAMERA_DIALOG };
	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	
	
	/***
	 *	ȫ��˽�б���
	 */
	//CCameraDS lfCam;
	//CCameraDS riCam;
//	VideoCapture lfCam;
//	VideoCapture riCam;
	cv::Mat m_lfImage;
	cv::Mat m_riImage;
	cv::Mat m_disparity;
	calib m_stereoCalibrator;
//	StereoMatch m_stereoMatcher;
//	int m_lfCamID;
//	int m_riCamID;
//	int m_nCamCount;
	int m_ProcMethod;
	int m_nImageWidth;
	int m_nImageHeight;
	int m_nImageChannels;
	CString m_workDir;

	#pragma region �ؼ���������
	int m_nCornerSize_X;
	int m_nCornerSize_Y;
	int m_nBoards;
//	int m_nDelayTime;
	int m_nMinDisp;
	int m_nMaxDisp;
	int m_nSADWinSiz;
	int m_nTextThres;
	int m_nDisp12MaxDiff;
	int m_nPreFiltCap;
	int m_nUniqRatio;
	int m_nSpeckRange;
	int m_nSpeckWinSiz;
	int m_P1;
	int m_P2;
	UINT m_nID_RAD;
//	BOOL m_bFullDP;
//	BOOL m_bSaveFrame;
	float m_nSquareSize;
	double m_ObjectWidth;
	double m_ObjectHeight;
	double m_ObjectDistance;
	double m_ObjectDisparity;

/*	CButton* m_pCheck;
	CComboBox m_CBNCamList;
	CComboBox m_CBNMethodList;
	CComboBox m_CBNResolution;
	CSpinButtonCtrl m_spinMinDisp;
	CSpinButtonCtrl m_spinMaxDisp;
	CSpinButtonCtrl m_spinSADWinSiz;
	CSpinButtonCtrl m_spinTextThres;
	CSpinButtonCtrl m_spinDisp12MaxDiff;
	CSpinButtonCtrl m_spinPreFiltCap;
	CSpinButtonCtrl m_spinUniqRatio;
	CSpinButtonCtrl m_spinSpeckRange;
	CSpinButtonCtrl m_spinSpeckWinSiz;*/
		/***
	 *	���ܺ���
	 */
//	void DoShowOrigFrame(void);
	void DoStereoCalib(void);
//	void DoFrameProc(Mat& src, Mat& dst);
//	void DoParseOptionsOfCameraCalib(OptionCameraCalib& opt);
//	void DoParseOptionsOfStereoMatch(OptionStereoMatch& opt);
	void DoClearParamsOfStereoMatch(void);
	vector<CStringA> DoSelectFiles(LPCTSTR	lpszDefExt, DWORD	dwFlags, LPCTSTR	lpszFilter, LPCWSTR	lpstrTitle, LPCWSTR	lpstrInitialDir);
	void DoUpdateStateBM(void);
	void DoUpdateStateSGBM(int imgChannels);
	CString F_GetAppExecPath();
	void F_Gray2Color(Mat& gray_mat, Mat& color_mat);
	void F_Saveframe(Mat& lfImg, Mat&riImg, Mat& lfDisp);
	void F_ShowImage(Mat& src, Mat& des, UINT ID);
//	void F_EdgeDetectCanny(Mat& src, Mat& des);
#pragma endregion �ؼ���������
public:
	afx_msg void OnEnChangeBoardheight();
	afx_msg void OnEnChangeSquaresize();
	afx_msg void OnEnChangeBoardwidth();
	afx_msg void OnBnClickedBnDefaultcamcalibparam();
	afx_msg void OnBnClickedBndetectag();
	afx_msg void OnBnClickedBn2stereocalib();
	typedef enum { STEREO_BM, STEREO_SGBM } STEREO_METHOD;
	static void CJluNewCameraDlg::On_Mouse(int event,int x,int y,int flags,void *)
    {
		switch(event)
		{
		case CV_EVENT_LBUTTONDOWN:
			{
				
				moupoint.x=x;
				moupoint.y=y;
//				AfxMessageBox(_T("������"));
			}
			break;
		case CV_EVENT_LBUTTONUP:
			{
			}
			break;
		}
    }
	struct OptionStereoMatch
	{
		bool			readLocalImage;		//�Ƿ���뱾��ͼ���������ƥ��
		bool			generatePointCloud;	//�Ƿ�������ά����
		bool			useStereoRectify;	//�Ƿ�ʹ��˫ĿУ���㷨
		STEREO_METHOD	stereoMethod;		//ѡ�������ƥ���㷨
		calib::RECTIFYMETHOD	rectifyMethod;		//ѡ���˫ĿУ���㷨
	};

	struct OptionCameraCalib
	{
		int				numberBoards;		//���̼�����
		int				flagCameraCalib;	//��Ŀ�����־��
		int				flagStereoCalib;	//˫Ŀ�����־��
		int				numberFrameSkip;	//�ǵ����֡������
		bool			doStereoCalib;		//�Ƿ����˫Ŀ�궨
		bool			readLocalImage;		//�Ƿ�ӱ��ض�������ͼƬ
		double			squareSize;			//���̷����С
		cv::Size		cornerSize;			//���̽ǵ���
		calib::RECTIFYMETHOD	rectifyMethod;		//ѡ���˫ĿУ���㷨
	};
	
	afx_msg void OnBnClickedBnStereodefparam();
	afx_msg void OnBnClickedBngivedisp();
	afx_msg void OnBnClickedBnCompdisp();
	afx_msg void OnBnClickedRadBm();
	afx_msg void OnBnClickedRadSgbm();
	afx_msg void OnBnClickedBnMouseon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedFacedetect();
	afx_msg void OnBnClickedOnlydisp();
	afx_msg void OnBnClickedSgbmtest();
};
