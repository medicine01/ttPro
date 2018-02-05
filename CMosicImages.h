#pragma  once
#include "qmosicprocess_global.h"
#include <gdal_priv.h>
#include <ogr_api.h>
#include <ogrsf_frmts.h>
#include <ogr_core.h>
#include <ogr_geometry.h>

#include <opencv2/opencv.hpp>

#include <map>
#include <cassert>
#include <vector>
#include <stdio.h>
#include <io.h>  
#include <fstream>  
#include <alg.h>
#include <cpl_conv.h>
#include <gdalwarper.h>
#include <iostream>

using namespace cv;

struct RESULT_INFO
{
	double resX;//X����ķֱ��ʣ���Ϊ��λ��
	double resY;//Y����ķֱ��ʣ���Ϊ��λ��
	ushort lines;//ͼ�������
	ushort cols;//ͼ�������
	cv::Rect_<double> fileExtent;//ͼ��ķ�Χ����γ�ȵ�λ��
	std::string projectionRef;//����ϵ��
};

class QMOSICPROCESS_EXPORT CMosicImages
{
public:
	 //************************************
	// Method:    CMosicImages
	// FullName:  CMosicImages::CMosicImages
	// Access:    public 
	// Variables std::vector<std::string> &imagesFilepath ����������б�
	// Variables std::string resultPath ����Ľ�����������ͼƬ��λ�ú͸�ʽ
	// Variables std::string shpPath  ���ʸ������shp��λ�á�
	// Returns:   
	// Qualifier: ���캯����
	//************************************
	CMosicImages(std::vector<std::string> &imagesFilepath,
		std::string resultPath,std::string shpPath );
	~CMosicImages(){}
	 //************************************
	// Method:    doMosic
	// FullName:  CMosicImages::doMosic
	// Access:    public 
	// Returns:   bool
	// Qualifier: ����ƴ��
	//************************************
	bool doMosic();

private:
	 //************************************
	// Method:    init
	// FullName:  CMosicImages::init
	// Access:    private 
	// Returns:   void
	// Qualifier: ��ʼ������
	//************************************
	void init();
	 //************************************
	// Method:    getImageInfo
	// FullName:  CMosicImages::getImageInfo
	// Variables char **papszSrcFiles  �����ͼ���ļ�·����
	// Variables int filesize          ����ͼ���ļ���������
	// Variables const char *pszFormat  ��ȡGDAL�ļ�����Ҫ�ĸ�ʽ��
	// Variables GDALDataType eDT  �ļ���������Ϣ��
	// Variables RESULT_INFO &fileinfo  ��ȡƴ�ӽ��ͼ��ķ�Χ��Ϣ��
	// Access:    private 
	// Returns:  std::map<std::string ,RESULT_INFO > ���ظô���������ÿ���ļ���ƴ����Ϣ
	// Qualifier:  ��ȡ�ô���������ÿ���ļ���ƴ����Ϣ���Լ���ȡƴ�ӽ��ͼ��ķ�Χ��Ϣ
	//************************************
	std::map<std::string ,RESULT_INFO > getImageInfo(char **papszSrcFiles, int filesize,
		const char *pszFormat, GDALDataType eDT ,RESULT_INFO &fileinfo);
	 //************************************
	// Method:    addBoundary
	// FullName:  CMosicImages::addBoundary
	// Access:    private 
	// Variables cv::Mat&thisImage  ��ǰͼ����Ϣ��
	// Variables cv::Mat&resultImgeo  ���ͼ����Ϣ��
	// Variables cv::Mat &boudaryImge  �߽�ͼ����Ϣ��
	// Variables int beginx  ��ͼ��ʼλ��x��
	// Variables int beginy  ��ͼ��ʼλ��y��
	// Returns:   void
	// Qualifier: д�߽�ͼ��
	//************************************
	void addBoundary(cv::Mat&thisImage,cv::Mat&resultImge,
		cv::Mat &boudaryImge,int beginx,int beginy);
	 //************************************
	// Method:    writeBoundaryShp
	// FullName:  CMosicImages::writeBoundaryShp
	// Variables RESULT_INFO &fileinfo  ƴ�ӽ��ͼ��ķ�Χ��Ϣ��
	// Variables cv::Mat&edgesResult  �߽�ͼ��
	// Access:    private 
	// Returns:   bool
	// Qualifier: д��߽��ߣ�shp�ļ���
	//************************************
	bool writeBoundaryShp(RESULT_INFO &fileInfo,cv::Mat&edgesResult);
	 //************************************
	// Method:    mosicAllImages
	// FullName:  CMosicImages::mosicAllImages
	// Variables cv::Mat &mosicResult  ���ͼ��
	// Variables cv::Mat &boundImge  �߽�ͼ��
	// Variables RESULT_INFO &fileinfo  ���ͼ����Ϣ��
	// Variables std::map<std::string ,RESULT_INFO> &allFilest  ����ͼ����Ϣ��
	// Access:   private 
	// Returns:   bool
	// Qualifier: �ϲ�����Ӱ��
	//************************************
	void mosicAllImages(cv::Mat &mosicResult,cv::Mat &boundImge, RESULT_INFO &fileinfo,
		std::map<std::string ,RESULT_INFO> &allFiles);

	OGRGeometry* ConvertPolylineToPolygon(OGRGeometry* polyline);

	void createPolygonPoints(cv::Mat &thisImage,int i, RESULT_INFO &fileinfo,std::map<std::string ,RESULT_INFO> &allFiles);

	cv::Rect_<double> overRect(cv::Rect_<double> r1,cv::Rect_<double> r2);

	cv::Mat transImageToMat(std::string imagepath);
	void writeBoundaryPolygonShp(RESULT_INFO &fileInfo,std::string filepath);
private:
	//
	std::vector<std::string> _imagesFilepath;
	//
	std::string _resultPath;
	//
	std::string _shpPath;
	//
	std::vector<std::vector<cv::Point>> _polygons;
};