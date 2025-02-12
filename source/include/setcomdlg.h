#ifndef SETCOMFRM_H
#define SETCOMFRM_H

#include <QtGui/QWidget>
#include <QtXml/QtXml>
#include <QSettings>
#include <QtSql/QSqlTableModel>

#include "ui_setcomDlg.h"
#include "systemsetdlg_global.h"

class ReadComConfig;

class SYSTEMSETDLG_EXPORT SetComDlg : public QWidget
{
	Q_OBJECT

public slots:
	void showEvent(QShowEvent *);
	void closeEvent(QCloseEvent *);
signals:
	void signalClosed();
public:
	SetComDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~SetComDlg();

private:
	Ui::SetComDlgClass gui;
	QSettings *m_com_settings;
	QButtonGroup *btnGroupBalanceType; //天平类型
	QButtonGroup *btnGroupBalanceType2;//天平类型2
	ReadComConfig *m_config;//读取配置信息
	QSqlTableModel *m_model;

	/**************读取配置文件*****************/
	void InstallConfigs();
	void InstallValeConfig();
	void InstallValeConfig2();
	void InstallBalanceConfig();
	void InstallBalanceConfig2();
	void InstallBalanceTypeConfig();
	void InstallBalanceTypeConfig2();
	void InstallTempConfig();
	void InstallStdtmpConfig();
	void InstallInstStdConfig();
	void InstallAccumStdConfig();
	void InstallMetersConfig();
	/********************************************/

	/**************写入配置文件*****************/
	void WriteValveConfig();//写入阀门配置
	void WriteValveConfig2();//写入阀门配置
	void WriteBalanceConfig();//写入天平配置
	void WriteBalanceConfig2();//写入天平配置
	void WriteBalanceTypeConfig();//写入天平类型配置
	void WriteBalanceTypeConfig2();//写入天平类型配置2
	void WriteTempConfig();//写入温度采集配置
	void WriteStdTempConfig();//写入标准温度计配置
	void WriteInstStdConfig();//写入采集瞬时流量模块配置
	void WriteAccumStdConfig();//写入采集累积流量模块配置
	void WriteMetersConfig();//写入被检表配置
	void WriteConfigById(QGroupBox*);//写入配置
	/********************************************/

private slots:
	void on_btnExit_clicked();
	void on_btnSave_clicked();
};

#endif // SETCOMFRM_H