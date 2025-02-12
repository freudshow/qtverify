#ifndef PARASETDLG_H
#define PARASETDLG_H

#include <QtGui/QWidget>
#include <QSettings>
#include <QDateTime>

#include "ui_parasetdlg.h"
#include "systemsetdlg_global.h"
#include "basedef.h"

class QSqlTableModel;

/*
** 将配置文件中的所有字面信息保存至结构QParams_PTR中
*/
class SYSTEMSETDLG_EXPORT ParaSetReader
{
public:
		
	QMap<int,QString> m_valvePortMap;//建立阀门的字面值与其端口号的双射关系
	QMap<int,QString> m_regPortMap;//建立调节阀的字面值与其端口号的双射关系
	ParaSetReader();
	~ParaSetReader();

	Verify_Params_PTR getParams();
	Verify_Params_PTR m_params;
	
	int readIniFile();
	Flow_Point_Info getFpBySeq(int i);//取出检定次序为i的流量点信息

	int getBigSmallBySeq(int i);//取出检定次序为i的界面控件索引号

private:
	QSettings *m_settings;
	QSettings *m_port_config;//阀门端口配置文件

	void initValveMap();
	void readParamValues();//读取配置文件所有的信息

	void readHead();//读取配置文件的[head]组的信息
	void readFlowPoints();//读取配置文件的[FlowPoints]组的信息
	void readBool();//读取配置文件的[Bool]组的信息
	void readOther();//读取配置文件的[Other]组的信息
	void readWaterPara();
};

class SYSTEMSETDLG_EXPORT ParaSetDlg : public QWidget
{
	Q_OBJECT

public:
	ParaSetDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ParaSetDlg();

	int m_meterStdNum;	//热量表规格
	MeterStandard_PTR m_meterStdPtr;

	int m_manuFacNum;	//制造单位
	Manufacture_PTR m_manuFacPtr;

	void initUiData(); //从数据库读取记录，填充combox等
	void initBtnGroup();//初始化ButtonGroup

	void mapPickCodeModel(); //采集代码模型
	QSqlTableModel *m_pickCodeModel;
	int m_curPickCodeIdx; //当前采集代码的索引

	void mapVfDeptModel(); //送检单位模型
	QSqlTableModel *m_vfDeptModel;
	int m_curVfDeptIdx; //当前送检单位的索引

	void mapManuDeptModel(); //制造单位模型
	QSqlTableModel *m_manuDeptModel;
	int m_curManuDeptIdx; //当前制造单位的索引

	void mapUserModel(); //送检员和核验员模型
	QSqlTableModel *m_userModel;
	int m_curVerifyPersonIdx; //当前送检员的索引
	int m_curCheckPersonIdx;  //当前核验员的索引

	void mapMeterModelModel(); //表型号模型
	QSqlTableModel *m_modelModel;
	int m_curModelIdx; //当前表型号的索引

	void showWaterPara();

signals:
	void saveSuccessSignal();

public slots:
	void showEvent(QShowEvent * event);
	void closeEvent(QCloseEvent * event);
	void on_btnExit_clicked();
	void on_btnSave_clicked();
	void on_cmbStandard_currentIndexChanged();
	void slot_autopick_clicked(int);

	void onVerifyFlowChanged(QString vFlow, int num);
	void on_lnEdit_Flow1_textChanged(const QString & text);
	void on_lnEdit_Flow2_textChanged(const QString & text);
	void on_lnEdit_Flow3_textChanged(const QString & text);
	void on_lnEdit_Flow4_textChanged(const QString & text);

	void onUpperFlowChanged();
	void on_lineEdit_Upper_1_textChanged(const QString & text);
	void on_lineEdit_Upper_2_textChanged(const QString & text);
	void on_lineEdit_Upper_3_textChanged(const QString & text);
	void on_lineEdit_Upper_4_textChanged(const QString & text);

private:
	Ui::ParaSetDlgClass ui;
	bool cBoxData_inited;//标记, 界面的下拉条已经从数据库中读取了数据
	
	QSettings *settings;//配置文件
	Verify_Params_PTR params;//本次的配置参数
	ParaSetReader *lastParams;//上次的配置参数
	qint64 timestamp;//时间戳

	QVector<QLineEdit*> lineEdit_uppers;//上限流量点控件数组
	QVector<QLineEdit*> lineEdit_flows;//检定流量点控件数组
	QVector<QLineEdit*> lineEdit_quantites;//检定水量控件数组
	QVector<QComboBox*> cBox_valves;//流量点对应的阀门控件数组
	QVector<QLineEdit*> lineEdit_freqs;//水泵频率控件数组
	QVector<QComboBox*> cBox_seqs;//检定次序控件数组
	QVector<QLineEdit*> lineEdit_Openings;//流量点对应的调节阀开度控制数组

	QButtonGroup *m_btnGroup_autopick; //自动采集
	QButtonGroup *m_btnGroup_adjustError; //修正误差
	QButtonGroup *m_btnGroup_writeNum; //修正误差

	void flowPointVector();//将各流量点中, 相似功能的控件加入数组, 便于使用
	void installLastParams();//装载上次的参数配置
	void installHead();//加载配置文件的[head]组的信息
	void installFlowPoint();//加载配置文件的[FlowPoint_i]组的信息
	void installBool();//加载配置文件的[Bool]组的信息
	void installOther();//加载配置文件的[Other]组的信息
	void installWaterPara();

	void installDftDBinfo();//加载数据库中默认的参数

	bool chkSeq();//检查选定的检定次序是否满足要求
	bool chkTotalQuantity();//检查设定的检定量之和是否超出天平的最大范围
	void SaveHead();//保存基本信息
	void SaveFlowPoint();//保存流量点信息
	void SaveBool();//保存布尔值
	void SaveOther();//保存其他信息
	void SaveWaterPara();//保存水表参数

	void Update_T_Meter_Default_Params();

private slots:

};

#endif // PARASETDLG_H
