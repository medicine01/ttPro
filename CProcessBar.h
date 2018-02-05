
#ifndef CPROCESS_BAR_H
#define CPROCESS_BAR_H
#include <QProgressBar>
#include <QCoreApplication>
#include <QProgressDialog>
#include "qmosicprocess_global.h"
  
class QMOSICPROCESS_EXPORT CProcessBar :public QProgressBar
{
	Q_OBJECT
public:
	//************************************
	// Method:    instance
	// FullName:  CProcessBar::instance
	// Access:    public static 
	// Returns:   CProcessBar*
	// Qualifier: 单例模式
	//************************************
	static CProcessBar* instance();

 
	//************************************
	// Method:    initProcessBar
	// FullName:  CProcessBar::initProcessBar
	// Ac cess:    public 
	// Returns:   void
	// Qualifier: 初始化进度条
	//************************************
	void initProcessBar();//初始化进度条
	 //************************************
	// Method:    setCurrentValue
	// FullName:  CProcessBar::setCurrentValue
	// Access:    public 
	// Returns:   void
	// Qualifier: 进度条当前值
	//************************************
	void setCurrentValue(int value);
private:
	CProcessBar();

	~CProcessBar(){};	

	CProcessBar( const CProcessBar& ){};

	CProcessBar& operator = ( const CProcessBar& ){ return *this;} 
 
private:
	double _curentValue;//进度条当前值
	 
private: 	

  static CProcessBar* m_instance ;	 
};
#endif CPROCESS_BAR_H