#ifndef TVERPARAMPARAMDLG_H
#define TVERPARAMPARAMDLG_H

#ifdef TVERPARAM_DLL
#  ifdef WIN32
#  define TVERPARAM_EXPORT __declspec(dllexport)
#  else
#  define TVERPARAM_EXPORT
#  endif
#else
#  ifdef WIN32
#  define TVERPARAM_EXPORT __declspec(dllimport)
#  else
#  define TVERPARAM_EXPORT
#  endif
#endif


#include <QtGui/QWidget>
#include <QSettings>
#include "ui_tverparam_param.h"
#include "qtexdb.h"
#include "basedef.h"

class TVERPARAM_EXPORT tverparamparamDlg : public QWidget
{
	Q_OBJECT

public:
	tverparamparamDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~tverparamparamDlg();

	public slots:
		void closeEvent(QCloseEvent * event);
		void showEvent(QShowEvent * event);

		void on_btn_exit_clicked();
		void on_btn_save_clicked();
private:
	Ui::PlaParamParamDlgClass ui;

	bool cBoxData_inited;//标记, 界面的下拉条已经从数据库中读取了数据

	int m_meterStdNum;	//热量表规格
	MeterStandard_PTR m_meterStdPtr;//热量表规格

	int m_manuFacNum;	//制造单位
	Manufacture_PTR m_manuFacPtr;//制造单位数量

	QSettings* m_config;//读取及保存配置文件
private:
	void initCmbBox();//初始化comboBox
	void readConfig();//读取上次设置参数
	void saveConfig();//保存本次设置参数
};

#endif//TVERPARAMPARAMDLG_H