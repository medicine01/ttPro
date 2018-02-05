
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
	// Qualifier: ����ģʽ
	//************************************
	static CProcessBar* instance();

 
	//************************************
	// Method:    initProcessBar
	// FullName:  CProcessBar::initProcessBar
	// Ac cess:    public 
	// Returns:   void
	// Qualifier: ��ʼ��������
	//************************************
	void initProcessBar();//��ʼ��������
	 //************************************
	// Method:    setCurrentValue
	// FullName:  CProcessBar::setCurrentValue
	// Access:    public 
	// Returns:   void
	// Qualifier: ��������ǰֵ
	//************************************
	void setCurrentValue(int value);
private:
	CProcessBar();

	~CProcessBar(){};	

	CProcessBar( const CProcessBar& ){};

	CProcessBar& operator = ( const CProcessBar& ){ return *this;} 
 
private:
	double _curentValue;//��������ǰֵ
	 
private: 	

  static CProcessBar* m_instance ;	 
};
#endif CPROCESS_BAR_H