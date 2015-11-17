
#include "StdAfx.h"
#include "Point_Analyze.h"
#include "JluNewCamera.h"////////////
#include "JluNewCameraDlg.h"///////////////////

PointCloudAnalyzer::PointCloudAnalyzer(void)
{
}


PointCloudAnalyzer::~PointCloudAnalyzer(void)
{
}


/*----------------------------
 * ���� : ������Ŀ�꣬���Ŀ����Ϣ����
 *----------------------------
 * ���� : PointCloudAnalyzer::detectNearObject
 * ���� : public 
 * ���� : void
 *
 * ���� : image			[io]	���������ͼ�������ԭλ����������Ŀ��ߴ�λ��
 * ���� : pointCloud		[in]	��ά����
 * ���� : objectInfos	[out]	Ŀ����Ϣ����
 */
void PointCloudAnalyzer::detectNearObject(cv::Mat& image, cv::Mat& pointCloud, vector<ObjectInfo>& objectInfos)
{
	if (image.empty() || pointCloud.empty())
	{
		return;
	}

	// ��ȡ���ͼ��
	vector<cv::Mat> xyzSet;
	split(pointCloud, xyzSet);
	cv::Mat depth;
	xyzSet[2].copyTo(depth);
	// ���������ֵ���ж�ֵ������
	double maxVal = 0, minVal = 0;
	cv::Mat depthThresh = cv::Mat::zeros(depth.rows, depth.cols, CV_8UC1);
	cv::minMaxLoc(depth, &minVal, &maxVal);//�ҵ�depth�е���Сֵ�����ֵ
	threshold(depth, depthThresh, 125, 255, CV_THRESH_BINARY_INV);//  "http://baike.baidu.com/view/3586026.htm"
//	threshold(depth, depthThresh,80, 255, CV_THRESH_BINARY_INV);
	depthThresh.convertTo(depthThresh, CV_8UC1);
	imageDenoising(depthThresh, 3);
	
//	Mat img_gray,img_gray_out;
//	cvtColor( image, img_gray, CV_BGR2GRAY );
//	threshold(img_gray, img_gray_out, 100, 255, CV_THRESH_BINARY);
//	imageDenoising(img_gray, 3);
//	blur( img_gray, img_gray, Size(3,3) );
//	cv::namedWindow("lslsls",1);
//	imshow("lslsls",img_gray);
//	blur( img_gray, img_gray, Size(3,3) );
	parseCandidates(depthThresh, depth, objectInfos);
//	parseCandidates(img_gray, depth, objectInfos);
	
    if(depthThresh.empty())
		AfxMessageBox(_T("objectΪ��@@@@"));
	// ��ȡ������ͷ�Ͻ���������Ϣ
/*	cvNamedWindow("lslsls",CV_WINDOW_AUTOSIZE);
	imshow("lslsls",depth);
	cvWaitKey(0);
	cvDestroyWindow("lslsls");*/
	if(objectInfos.empty())
		AfxMessageBox(_T("objectInfosΪ��"));

	// ��������ֲ�
	showObjectInfo(objectInfos, image);
}


/*----------------------------
 * ���� : ͼ��ȥ��
 *----------------------------
 * ���� : PointCloudAnalyzer::imageDenoising
 * ���� : private 
 * ���� : void
 *
 * ���� : img	[in]	������ͼ��ԭλ����
 * ���� : iters	[in]	��̬ѧ�������
 */
void PointCloudAnalyzer::imageDenoising( cv::Mat& img, int iters )
{
	cv::Mat pyr = cv::Mat(img.cols/2, img.rows/2, img.type());

	IplImage iplImg = img;
	cvSmooth(&iplImg, &iplImg, CV_GAUSSIAN, 3, 3);	// ƽ���˲�CV_GAUSSIAN (gaussian blur) - ��ͼ����к˴�СΪ param1��param2 �ĸ�˹���
	GaussianBlur( img, img, Size(3,3), 0, 0, BORDER_DEFAULT );
	pyrDown(img, pyr);	// ��ƽ�����ͼ����ж�������
	pyrUp(pyr, img);

	erode(img, img, 0, cv::Point(-1,-1), iters);	// ͼ��ʴ�����㣬ȥ��С��������
	dilate(img, img, 0, cv::Point(-1,-1), iters);	// ͼ������
/*	int dilation_type;
	int dilation_size=20;
    dilation_type = MORPH_RECT; 
    Mat element = getStructuringElement( dilation_type,
                                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                       Point( dilation_size, dilation_size ) );
	erode(img, img,element);
	dilate(img, img,element);	// ͼ������*/
	
}


/*----------------------------////?????
 * ���� : ���ɽ���������Ϣ����
 *----------------------------
 * ���� : PointCloudAnalyzer::parseCandidates
 * ���� : private 
 * ���� : void
 *
 * ���� : objects		[in]	�����ֵ����Ķ�ֵͼ����ʾ�˽�������ķֲ�
 * ���� : depthMap		[in]	����ά���ƾ����г�ȡ��������ݾ���
 * ���� : objectInfos	[out]	Ŀ����Ϣ����
 */
void PointCloudAnalyzer::parseCandidates(cv::Mat& objects, cv::Mat& depthMap, vector<ObjectInfo>& objectInfos)
{
	// ��ȡ��������
//	Mat canny_output;
	vector<vector<cv::Point> > contours;	// ������������
//	vector<Vec4i>hierarchy;
	cv::Mat tempobjects=objects;
	/// ��Canny���Ӽ���Ե
//    Canny( tempobjects, canny_output, 80, 160, 3 );
	findContours(tempobjects, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
/*	Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
     {
       Scalar color = Scalar(0, 233, 0);
       drawContours( drawing, contours, i, color, 2, 8);
     }

  /// �ڴ�������ʾ���
  namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
  imshow( "Contours", drawing );*/
//	findContours(objects, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
//	findContours(objects,contours,hierarchy,CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
	/*
	findContours���������Ϣcontours���ܹ��ڸ��Ӳ�ƽ����������approxPolyDP�����Ըö�����������ʵ�����
contourArea�������Եõ���ǰ������������Ĵ�С������������ɸѡ
findContours������drawContours���ʹ�ã��������������Ƴ�����
���е�һ������image��ʾĿ��ͼ�񣬵ڶ�������contours��ʾ����������飬ÿһ�������ɵ�vector���ɣ�
����������contourIdxָ�����ڼ�������������ò���Ϊ��ֵ����ȫ�����������ĸ�����colorΪ��������ɫ��
���������thicknessΪ�������߿����Ϊ��ֵ��CV_FILLED��ʾ��������ڲ�������������lineTypeΪ���ͣ�
���߸�����Ϊ�����ṹ��Ϣ���ڰ˸�����ΪmaxLevel*/
	// ��������
	double areaThresh = 0.005 * depthMap.rows * depthMap.cols;
	cv::Mat mask = cv::Mat::zeros(objects.size(), CV_8UC1);////1
	bool useMeanDepth = false;
//	CString str;
//	str.Format(_T("%d"),contours.size());
//			AfxMessageBox(str);
	for( UINT objID = 0; objID < contours.size(); objID++ )//�ó�ÿ����������Ϣ
	{
		cv::Mat contour = cv::Mat( contours[objID] );
		double area = contourArea( contour );//�����������
		if(area>0)
		{
			ObjectInfo object;
			// ��������ڲ�������Ϊ��������
			mask = cv::Scalar(0);
			drawContours(mask,contours,objID,cv::Scalar(255),-1);
			/*
			�������������Ƴ��������е�һ������image��ʾĿ��ͼ��
			�ڶ�������contours��ʾ����������飬ÿһ�������ɵ�vector���ɣ�
			����������contourIdxָ�����ڼ�������������ò���Ϊ��ֵ��
			��ȫ�����������ĸ�����colorΪ��������ɫ��
			���������thicknessΪ�������߿�
			���Ϊ��ֵ��CV_FILLED��ʾ��������ڲ���
			����������lineTypeΪ���ͣ����߸�����Ϊ�����ṹ��Ϣ���ڰ˸�����ΪmaxLevel
			*/
			double minVal = 0, maxVal = 0;
			cv::Point minPos;
			cv::minMaxLoc(depthMap, &minVal, &maxVal, &minPos, NULL, mask);
			object.distance = depthMap.at<float>(minPos.y, minPos.x);
//			}
				// ������������
			object.boundRect = boundingRect( contour );//����㼯�������棨up-right�����α߽�
			object.minRect = minAreaRect( contour );
			object.center = object.minRect.center;

			// ��������������Ϣ
			objectInfos.push_back( object );
		}
	}

	// �����������������
	//std::sort( objectInfos.begin(), objectInfos.end(), std::greater<ObjectInfo>() );
}

void PointCloudAnalyzer::showObjectInfo(vector<ObjectInfo>& objectInfos, cv::Mat& outImage)
{
	int showCount = objectInfos.size() < 5 ? objectInfos.size() : 5;
	
	// �������п���������
	for (int i = 0; i < showCount; i++)
	{
		//��������
		circle(outImage, objectInfos[i].center, 3, CV_RGB(0,0,255), 2);
		
		//������С����
		cv::Point2f rect_points[4]; 
//		objectInfos[i].minRect.points( rect_points );
		objectInfos[i].minRect.points( rect_points );
//		rectangle(outImage,objectInfos[i].boundRect,CV_RGB(0,0,255),2);
		if (i==0)
		{
			for( int j = 0; j < 4; j++ )
				line( outImage, rect_points[j], rect_points[(j+1)%4], CV_RGB(255,0,0), 4 );
		} 
		else
		{
			for( int j = 0; j < 4; j++ )
				line( outImage, rect_points[j], rect_points[(j+1)%4], CV_RGB(255-i*40,i*40,0), 2 );
		}
	}
}