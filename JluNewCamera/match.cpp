#include "StdAfx.h"
#include "match.h"
using namespace cv;
StereoMatch::StereoMatch(void)
	: m_frameWidth(0), m_frameHeight(0), m_numberOfDisparies(0)
{
}

StereoMatch::~StereoMatch(void)
{
}


/*----------------------------
 * ���� : ��ʼ���ڲ�����������˫Ŀ����������
 *----------------------------
 * ���� : StereoMatch::init
 * ���� : public 
 * ���� : 0 - ���붨������ʧ�ܣ�1 - ���붨�����ݳɹ�
 *
 * ���� : imgWidth		[in]	ͼ����
 * ���� : imgHeight		[in]	ͼ��߶�
 * ���� : xmlFilePath	[in]	˫Ŀ�����������ļ�
 */
int StereoMatch::init(int imgWidth, int imgHeight, const char* xmlFilePath)
{
	m_frameWidth = imgWidth;
	m_frameHeight = imgHeight;
	m_numberOfDisparies = 0;

	return loadCalibData(xmlFilePath);
}

/*----------------------------
 * ���� : ����˫Ŀ����������
 *----------------------------
 * ���� : StereoMatch::loadCalibData
 * ���� : public 
 * ���� : 1		�ɹ�
 *		 0		����У������ʧ��
 *		 -1		���������ͼ��ߴ��뵱ǰ���õ�ͼ��ߴ粻һ��
 *		 -2		У���������� BOUGUET ����
 *		 -99	δ֪����
 * 
 * ���� : xmlFilePath	[in]	˫Ŀ�����������ļ�
 */
int StereoMatch::loadCalibData(const char* xmlFilePath)
{
	// ��������ͷ������� Q roi1 roi2 mapx1 mapy1 mapx2 mapy2
	try
	{
		cv::FileStorage fs(xmlFilePath, cv::FileStorage::READ);		
		if ( !fs.isOpened() )
		{
			return (0);
		}

		cv::Size imageSize;
		cv::FileNodeIterator it = fs["imageSize"].begin(); 
		it >> imageSize.width >> imageSize.height;
		if (imageSize.width != m_frameWidth || imageSize.height != m_frameHeight)
		{
			return (-1);
		}

		vector<int> roiVal1;
		vector<int> roiVal2;

		fs["leftValidArea"] >> roiVal1;
		m_Calib_Roi_L.x = roiVal1[0];
		m_Calib_Roi_L.y = roiVal1[1];
		m_Calib_Roi_L.width = roiVal1[2];
		m_Calib_Roi_L.height = roiVal1[3];

		fs["rightValidArea"] >> roiVal2;
		m_Calib_Roi_R.x = roiVal2[0];
		m_Calib_Roi_R.y = roiVal2[1];
		m_Calib_Roi_R.width = roiVal2[2];
		m_Calib_Roi_R.height = roiVal2[3];

		fs["QMatrix"] >> m_Calib_Mat_Q;
		fs["remapX1"] >> m_Calib_Mat_Remap_X_L;
		fs["remapY1"] >> m_Calib_Mat_Remap_Y_L;
		fs["remapX2"] >> m_Calib_Mat_Remap_X_R;
		fs["remapY2"] >> m_Calib_Mat_Remap_Y_R;

		cv::Mat lfCamMat;
		fs["leftCameraMatrix"] >> lfCamMat;
		m_FL = lfCamMat.at<double>(0,0);

		m_Calib_Mat_Q.at<double>(3, 2) = -m_Calib_Mat_Q.at<double>(3, 2);

		m_Calib_Mat_Mask_Roi = cv::Mat::zeros(m_frameHeight, m_frameWidth, CV_8UC1);
		cv::rectangle(m_Calib_Mat_Mask_Roi, m_Calib_Roi_L, cv::Scalar(255), -1);

		m_BM.state->roi1 = m_Calib_Roi_L;
		m_BM.state->roi2 = m_Calib_Roi_R;

		m_Calib_Data_Loaded = true;

		string method;
		fs["rectifyMethod"] >> method;
		if (method != "BOUGUET")
		{
			return (-2);
		}

	}
	catch (std::exception& e)
	{	
		m_Calib_Data_Loaded = false;
		return (-99);	
	}
	
	return 1;
}
/*----------------------------
 * ���� : ���� BM �㷨�����Ӳ�
 *----------------------------
 * ���� : StereoMatch::bmMatch
 * ���� : public 
 * ���� : 0 - ʧ�ܣ�1 - �ɹ�
 *
 * ���� : frameLeft		[in]	�������֡ͼ
 * ���� : frameRight		[in]	�������֡ͼ
 * ���� : disparity		[out]	�Ӳ�ͼ
 * ���� : imageLeft		[out]	����������ͼ��������ʾ
 * ���� : imageRight		[out]	����������ͼ��������ʾ
 */
int StereoMatch::bmMatch(cv::Mat& frameLeft, cv::Mat& frameRight, cv::Mat& disparity, cv::Mat& imageLeft, cv::Mat& imageRight)
{
	// ������
	if (frameLeft.empty() || frameRight.empty())
	{
		disparity = cv::Scalar(0);
		return 0;
	}
	if (m_frameWidth == 0 || m_frameHeight == 0)
	{
		if (init(frameLeft.cols, frameLeft.rows, "calib_paras.xml"/*����Ϊ�ɱ��������ļ�ȷ��*/) == 0)	//ִ�����ʼ��
		{
			return 0;
		}
	}

	// ת��Ϊ�Ҷ�ͼ
	//cv::Mat  img1proc, img2proc;
	cv::Mat img1proc;
	cv::Mat img2proc;
	cvtColor(frameLeft, img1proc, CV_BGR2GRAY);
	cvtColor(frameRight, img2proc, CV_BGR2GRAY);

	// У��ͼ��ʹ������ͼ�ж���	
	cv::Mat img1remap, img2remap;
	if (m_Calib_Data_Loaded)
	{
		remap(img1proc, img1remap, m_Calib_Mat_Remap_X_L, m_Calib_Mat_Remap_Y_L, cv::INTER_LINEAR);		// �������Ӳ����Ļ������У��
		remap(img2proc, img2remap, m_Calib_Mat_Remap_X_R, m_Calib_Mat_Remap_Y_R, cv::INTER_LINEAR);
	} 
	else
	{
		img1remap = img1proc;
		img2remap = img2proc;
	}
	////////////////
	// ��������ͼ����߽��б߽����أ��Ի�ȡ��ԭʼ��ͼ��ͬ��С����Ч�Ӳ�����
	cv::Mat img1border, img2border;
	if (m_numberOfDisparies != m_BM.state->numberOfDisparities)
		m_numberOfDisparies = m_BM.state->numberOfDisparities;
//	copyMakeBorder(img1remap, img1border, 0, 0, m_BM.state->numberOfDisparities, 0, IPL_BORDER_REPLICATE);
//	copyMakeBorder(img2remap, img2border, 0, 0, m_BM.state->numberOfDisparities, 0, IPL_BORDER_REPLICATE);
	copyMakeBorder(img1remap, img1border, 0, 0, m_BM.state->numberOfDisparities, 0, IPL_BORDER_REPLICATE);
	copyMakeBorder(img2remap, img2border, 0, 0, m_BM.state->numberOfDisparities, 0, IPL_BORDER_REPLICATE);
	//http://blog.sina.com.cn/s/blog_627e716701015zeg.html
	// �����Ӳ�
	cv::Mat dispBorder;
	m_BM(img1border, img2border, dispBorder);

	// ��ȡ��ԭʼ�����Ӧ���Ӳ�������ȥ�ӿ�Ĳ��֣�
	cv::Mat disp;
	disp = dispBorder.colRange(m_BM.state->numberOfDisparities, img1border.cols);	
/*	disp.copyTo(disparity, m_Calib_Mat_Mask_Roi);
	cv::Mat disp;
	img1proc=img1remap;
	img2proc=img2remap;
	m_BM(img1proc,img1proc,disp);*/
	disp.copyTo(disparity,m_Calib_Mat_Mask_Roi);
//	disp.convertTo(disparity, CV_8U, 255/(m_BM.state->numberOfDisparities*16.));
	// ���������ͼ��
	if (m_Calib_Data_Loaded)
		remap(frameLeft, imageLeft, m_Calib_Mat_Remap_X_L, m_Calib_Mat_Remap_Y_L, cv::INTER_LINEAR);
	else
	{
		frameLeft.copyTo(imageLeft);
	}
	rectangle(imageLeft, m_Calib_Roi_L, CV_RGB(0,0,255), 3);

	if (m_Calib_Data_Loaded)
		remap(frameRight, imageRight, m_Calib_Mat_Remap_X_R, m_Calib_Mat_Remap_Y_R, cv::INTER_LINEAR);
	else
	{
		frameRight.copyTo(imageRight);
	}
	rectangle(imageRight, m_Calib_Roi_R, CV_RGB(0,255,0), 3);
	return 1;
}

/*----------------------------
 * ���� : ���� SGBM �㷨�����Ӳ�
 *----------------------------
 * ���� : StereoMatch::sgbmMatch
 * ���� : public 
 * ���� : 0 - ʧ�ܣ�1 - �ɹ�
 *
 * ���� : frameLeft		[in]	�������֡ͼ
 * ���� : frameRight		[in]	�������֡ͼ
 * ���� : disparity		[out]	�Ӳ�ͼ
 * ���� : imageLeft		[out]	����������ͼ��������ʾ
 * ���� : imageRight		[out]	����������ͼ��������ʾ
 */
int StereoMatch::sgbmMatch(cv::Mat& frameLeft, cv::Mat& frameRight, cv::Mat& disparity, cv::Mat& imageLeft, cv::Mat& imageRight)
{
	// ������
	if (frameLeft.empty() || frameRight.empty())
	{
		disparity = cv::Scalar(0);
		return 0;
	}
	if (m_frameWidth == 0 || m_frameHeight == 0)
	{
		if (init(frameLeft.cols, frameLeft.rows, "calib_paras.xml"/*����Ϊ�ɱ��������ļ�ȷ��*/) == 0)	//ִ�����ʼ��
		{
			return 0;
		}
	}

	// ����ͼ��
	cv::Mat img1proc, img2proc;
	frameLeft.copyTo(img1proc);
	frameRight.copyTo(img2proc);

	// У��ͼ��ʹ������ͼ�ж���	
	cv::Mat img1remap, img2remap;
	if (m_Calib_Data_Loaded)
	{
		remap(img1proc, img1remap, m_Calib_Mat_Remap_X_L, m_Calib_Mat_Remap_Y_L, cv::INTER_LINEAR);		// �������Ӳ����Ļ������У��
		remap(img2proc, img2remap, m_Calib_Mat_Remap_X_R, m_Calib_Mat_Remap_Y_R, cv::INTER_LINEAR);
	} 
	else
	{
		img1remap = img1proc;
		img2remap = img2proc;
	}

	// ��������ͼ����߽��б߽����أ��Ի�ȡ��ԭʼ��ͼ��ͬ��С����Ч�Ӳ�����
	cv::Mat img1border, img2border;
	if (m_numberOfDisparies != m_SGBM.numberOfDisparities)
		m_numberOfDisparies = m_SGBM.numberOfDisparities;
	copyMakeBorder(img1remap, img1border, 0, 0, m_SGBM.numberOfDisparities, 0, IPL_BORDER_REPLICATE);
	copyMakeBorder(img2remap, img2border, 0, 0, m_SGBM.numberOfDisparities, 0, IPL_BORDER_REPLICATE);

	// �����Ӳ�
	cv::Mat dispBorder;
	m_SGBM(img1border, img2border, dispBorder);

	// ��ȡ��ԭʼ�����Ӧ���Ӳ�������ȥ�ӿ�Ĳ��֣�
	cv::Mat disp;
	disp = dispBorder.colRange(m_SGBM.numberOfDisparities, img1border.cols);	
	disp.copyTo(disparity, m_Calib_Mat_Mask_Roi);
//	disp.convertTo(disparity, CV_8U, 255/(m_SGBM.numberOfDisparities*16.));
	// ���������ͼ��
	imageLeft = img1remap.clone();
	imageRight = img2remap.clone();
	rectangle(imageLeft, m_Calib_Roi_L, CV_RGB(0,255,0), 3);
	rectangle(imageRight, m_Calib_Roi_R, CV_RGB(0,255,0), 3);

	return 1;
}
void StereoMatch::GcMatch(IplImage * Left,IplImage * Right,CvMat * Left_disp,CvMat * Right_disp)
{
	Mat cv_left_rectified1;
    Mat cv_right_rectified1;
	Mat cv_left_rectified2;
    Mat cv_right_rectified2;
	CvMat Lefttemp;
	CvMat Righttemp;
	cv_left_rectified1=Left;
	cv_right_rectified1=Right;
	if (m_frameWidth == 0 || m_frameHeight == 0)
	{
		if (init(cv_left_rectified1.cols, cv_left_rectified1.rows, "calib_paras.xml"/*����Ϊ�ɱ��������ļ�ȷ��*/) == 0)	//ִ�����ʼ��
		{
			return;
		}
	}
	remap(cv_left_rectified1, cv_left_rectified2, m_Calib_Mat_Remap_X_L, m_Calib_Mat_Remap_Y_L, cv::INTER_LINEAR);		// �������Ӳ����Ļ������У��
	remap(cv_right_rectified1, cv_right_rectified2, m_Calib_Mat_Remap_X_R, m_Calib_Mat_Remap_Y_R, cv::INTER_LINEAR);
	Lefttemp=cv_left_rectified2;
	Righttemp=cv_right_rectified2;
	CvStereoGCState* state = cvCreateStereoGCState( 184, 2 ); 
	cvFindStereoCorrespondenceGC(&Lefttemp,&Righttemp,Left_disp,Right_disp,state,0 ); 
	cvReleaseStereoGCState( &state );  
	CvSize size = cvGetSize( Left );
	CvMat* disparity_left_visual = cvCreateMat( size.height, size.width, CV_8U );
	cvConvertScale( Left_disp, disparity_left_visual, -16 );
	cvSave( "disparity.png", disparity_left_visual );
	cvNamedWindow( "disparity", 1);
	cvShowImage("disparity", disparity_left_visual );
	cvWaitKey( 0 );
	cvDestroyWindow( "disparity" );
}
/*----------------------------
 * ���� : ��ȡα��ɫ�Ӳ�ͼ
 *----------------------------
 * ���� : StereoMatch::getDisparityImage
 * ���� : public 
 * ���� : 0 - ʧ�ܣ�1 - �ɹ�
 *
 * ���� : disparity			[in]	ԭʼ�Ӳ�����
 * ���� : disparityImage		[out]	α��ɫ�Ӳ�ͼ
 * ���� : isColor			[in]	�Ƿ����α��ɫ��Ĭ��Ϊ true����Ϊ false ʱ���ػҶ��Ӳ�ͼ
 */
int StereoMatch::getDisparityImage(cv::Mat& disparity, cv::Mat& disparityImage, bool isColor)
{
	// ��ԭʼ�Ӳ����ݵ�λ��ת��Ϊ 8 λ
	cv::Mat disp8u;
	if (disparity.depth() != CV_8U)
	{
		disparity.convertTo(disp8u, CV_8U, 255/(m_numberOfDisparies*16.));
	} 
	else
	{
		disp8u = disparity;
	}

	// ת��Ϊα��ɫͼ�� �� �Ҷ�ͼ��
	if (isColor)
	{
		if (disparityImage.empty() || disparityImage.type() != CV_8UC3 )
		{
			disparityImage = cv::Mat::zeros(disparity.rows, disparity.cols, CV_8UC3);
		}

		for (int y=0;y<disparity.rows;y++)
		{
			for (int x=0;x<disparity.cols;x++)
			{
				uchar val = disp8u.at<uchar>(y,x);
				uchar r,g,b;

				if (val==0) 
					r = g = b = 0;
				else
				{
					r = 255-val;
					g = val < 128 ? val*2 : (uchar)((255 - val)*2);
					b = val;
				}

				disparityImage.at<cv::Vec3b>(y,x) = cv::Vec3b(r,g,b);
			}
		}
	} 
	else
	{
		disp8u.copyTo(disparityImage);
	}

	return 1;
}
/*----------------------------
 * ���� : ������ά����
 *----------------------------
 * ���� : StereoMatch::getPointClouds
 * ���� : public 
 * ���� : 0 - ʧ�ܣ�1 - �ɹ�
 *
 * ���� : disparity		[in]	�Ӳ�����
 * ���� : pointClouds	[out]	��ά����
 */
int StereoMatch::getPointClouds(cv::Mat& disparity, cv::Mat& pointClouds)
{
	if (disparity.empty())
	{
		return 0;
	}

	//����������ά����
	cv::reprojectImageTo3D(disparity, pointClouds, m_Calib_Mat_Q, true);
	
	// ��������У��
	// ���� 16 �õ� ���� ��λ���꣬���� 1.6 �õ� ���� ��λ����
	// ԭ��μ���http://blog.csdn.net/chenyusiyuan/article/details/5967291 
//	pointClouds *= 16; 	
//	pointClouds /= 16; 
	cv::FileStorage fs("pointcloud.xml", cv::FileStorage::WRITE);
	if (fs.isOpened())
	{
		fs<<"ls"<<pointClouds;
	}
	fs.release();
	// У�� Y �������ݣ�������ת
	// ԭ��μ���http://blog.csdn.net/chenyusiyuan/article/details/5970799 
	for (int y = 0; y < pointClouds.rows; ++y)
	{
		for (int x = 0; x < pointClouds.cols; ++x)
		{
			cv::Point3f point = pointClouds.at<cv::Point3f>(y,x);
			point.y = -point.y;
			pointClouds.at<cv::Point3f>(y,x) = point;
		}
	}

	return 1;
}
