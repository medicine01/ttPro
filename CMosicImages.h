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
	double resX;//X方向的分辨率（度为单位）
	double resY;//Y方向的分辨率（度为单位）
	ushort lines;//图像的行数
	ushort cols;//图像的列数
	cv::Rect_<double> fileExtent;//图像的范围（经纬度单位）
	std::string projectionRef;//坐标系。
};

class QMOSICPROCESS_EXPORT CMosicImages
{
public:
	 //************************************
	// Method:    CMosicImages
	// FullName:  CMosicImages::CMosicImages
	// Access:    public 
	// Variables std::vector<std::string> &imagesFilepath 输入的数据列表
	// Variables std::string resultPath 输出的结果，即保存成图片的位置和格式
	// Variables std::string shpPath  输出矢量数据shp的位置。
	// Returns:   
	// Qualifier: 构造函数，
	//************************************
	CMosicImages(std::vector<std::string> &imagesFilepath,
		std::string resultPath,std::string shpPath );
	~CMosicImages(){}
	 //************************************
	// Method:    doMosic
	// FullName:  CMosicImages::doMosic
	// Access:    public 
	// Returns:   bool
	// Qualifier: 进行拼接
	//************************************
	bool doMosic();

private:
	 //************************************
	// Method:    init
	// FullName:  CMosicImages::init
	// Access:    private 
	// Returns:   void
	// Qualifier: 初始化变量
	//************************************
	void init();
	 //************************************
	// Method:    getImageInfo
	// FullName:  CMosicImages::getImageInfo
	// Variables char **papszSrcFiles  输入的图像文件路径。
	// Variables int filesize          输入图像文件的数量。
	// Variables const char *pszFormat  读取GDAL文件，需要的格式。
	// Variables GDALDataType eDT  文件的坐标信息。
	// Variables RESULT_INFO &fileinfo  获取拼接结果图像的范围信息。
	// Access:    private 
	// Returns:  std::map<std::string ,RESULT_INFO > 返回该处理批次中每个文件的拼接信息
	// Qualifier:  获取该处理批次中每个文件的拼接信息，以及获取拼接结果图像的范围信息
	//************************************
	std::map<std::string ,RESULT_INFO > getImageInfo(char **papszSrcFiles, int filesize,
		const char *pszFormat, GDALDataType eDT ,RESULT_INFO &fileinfo);
	 //************************************
	// Method:    addBoundary
	// FullName:  CMosicImages::addBoundary
	// Access:    private 
	// Variables cv::Mat&thisImage  当前图像信息。
	// Variables cv::Mat&resultImgeo  结果图像信息。
	// Variables cv::Mat &boudaryImge  边界图像信息。
	// Variables int beginx  该图像开始位置x。
	// Variables int beginy  该图像开始位置y。
	// Returns:   void
	// Qualifier: 写边界图像
	//************************************
	void addBoundary(cv::Mat&thisImage,cv::Mat&resultImge,
		cv::Mat &boudaryImge,int beginx,int beginy);
	 //************************************
	// Method:    writeBoundaryShp
	// FullName:  CMosicImages::writeBoundaryShp
	// Variables RESULT_INFO &fileinfo  拼接结果图像的范围信息。
	// Variables cv::Mat&edgesResult  边界图像。
	// Access:    private 
	// Returns:   bool
	// Qualifier: 写入边界线（shp文件）
	//************************************
	bool writeBoundaryShp(RESULT_INFO &fileInfo,cv::Mat&edgesResult);
	 //************************************
	// Method:    mosicAllImages
	// FullName:  CMosicImages::mosicAllImages
	// Variables cv::Mat &mosicResult  结果图像。
	// Variables cv::Mat &boundImge  边界图像。
	// Variables RESULT_INFO &fileinfo  结果图像信息。
	// Variables std::map<std::string ,RESULT_INFO> &allFilest  单个图像信息。
	// Access:   private 
	// Returns:   bool
	// Qualifier: 合并所有影像
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