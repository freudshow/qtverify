#ifndef DATATESTDLG_H
#define DATATESTDLG_H

#ifdef DATATESTDLG_DLL
#  ifdef WIN32
#  define DATATESTDLG_EXPORT __declspec(dllexport)
#  else
#  define DATATESTDLG_EXPORT
#  endif
#else
#  ifdef WIN32
#  define DATATESTDLG_EXPORT __declspec(dllimport)
#  else
#  define DATATESTDLG_EXPORT
#  endif
#endif

#include <QtGui/QWidget>
#include <QSettings>
#include "ui_datatestdlg.h"
#include "comobject.h"
#include "qtexdb.h"
#include "basedef.h"

class ParaSetReader;
class ParaSetDlg;
class ReadComConfig;

/*
** 类名：DataTestDlg
** 功能：数据采集与测试
*/

class DATATESTDLG_EXPORT DataTestDlg : public QWidget
{
	Q_OBJECT

public:
	DataTestDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~DataTestDlg();

	ParaSetReader *m_paraSetReader;
	ParaSetDlg *m_paraSetDlg;

	ReadComConfig *m_readComConfig; //读串口设置

	ComThread m_tempThread;  //温度采集线程
	TempComObject *m_tempObj;
	QTimer *m_tempTimer;  //计时器:用于请求管路温度

	ComThread m_stdTempThread;  //标准温度采集线程
	StdTempComObject *m_stdTempObj;
	QTimer *m_stdTempTimer;  //计时器:用于请求标准温度
	stdTempCommand m_stdTempCommand;

	ComThread m_valveThread;   //阀门控制线程
	ControlComObject *m_controlObj;

	QMap<int, bool> m_valveStatus;//<阀门端口号，阀门状态>
	QMap<int, QPushButton*> m_valveBtn;	//<阀门端口号，阀门按钮>
	int m_nowPortNo;	//当前控制阀门端口号

	QMap<int, bool> m_regStatus; //<调节阀端口号，调节阀状态>
	QMap<int, QPushButton*> m_regBtn;//<调节阀端口号，调节阀按钮>	
	int m_nowRegNo;  //当前调节阀端口号

	ComThread m_balanceThread; //天平采集线程
	BalanceComObject *m_balanceObj;

	ComThread m_meterThread;  //热量表线程
	MeterComObject *m_meterObj;

	//天平最大容量和回水底量
	float m_balMaxWht;
	float m_balBottomWht;

	//计算流速用
	uint m_totalcount;  //计数器
	float m_startWeight;//天平初值
	float m_endWeight;  //天平终值
	float m_deltaWeight[FLOW_SAMPLE_NUM];
	QTimer *m_flowRateTimer;  //计时器:用于计算流速

	PortSet_Ini_STR m_portsetinfo; //端口配置

	MeterCoe_PTR m_oldCoe; //热表当前流量点系数

	void closeEvent(QCloseEvent * event);
	void showEvent(QShowEvent *event);
	void initTemperatureCom();    //温度采集串口
	void initStdTemperatureCom(); //标准温度采集串口
	void initBalanceCom();        //天平串口
	void initControlCom();        //阀门控制串口
	void initComOfHeatMeter();    //热量表1串口

	void initValveStatus();	   //初始化阀门状态
	void initRegulateStatus(); //初始化调节阀状态

public slots:
	void on_btnWaterIn_clicked(); //进水阀
	void on_btnWaterOut_clicked();//放水阀
	void on_btnValveBig_clicked(); //大流量阀
	void on_btnValveMiddle1_clicked(); //中流一
	void on_btnValveMiddle2_clicked(); //中流二
	void on_btnValveSmall_clicked(); //小流量阀
	void on_btnWaterPump_clicked(); //水泵

	void on_btnSetFreq_clicked(); //设置频率
	void on_btnRegulate1_clicked();
	void on_btnRegulate2_clicked();

	void on_btnParaSet_clicked();
	void on_btnExit_clicked();

	void slotAskPipeTemperature();
	void slotFreshComTempValue(const QString& tempStr); //刷新温度值
	void slotFreshStdTempValue(const QString& stdTempStr); //刷新标准温度值
	void slotFreshBalanceValue(const float& balValue);     //刷新天平数值
	
	void slotFreshMeterNo(const QString& comName, const QString& meterNo);//刷新表号
	void slotFreshMeterFlow(const QString& comName, const QString& flow); //刷新表流量
	void slotFreshMeterHeat(const QString& comName, const QString& heat); //刷新表热量
	void slotFreshMeterDate(const QString& comName, const QString& date); //刷新表日期
	void slotFreshMeterTemper(const QString& comName, const QString& tempIn, const QString& tempOut); //刷新表进出水温度
	void slotFreshBigCoe(const QString& comName, const QString& bigCoe); //刷新大流量系数
	void slotFreshMid2Coe(const QString& comName, const QString& mid2Coe); //刷新中流2流量系数
	void slotFreshMid1Coe(const QString& comName, const QString& mid1Coe); //刷新中流1流量系数
	void slotFreshSmallCoe(const QString& comName, const QString& smallCoe); //刷新小流量系数


	void slotSetValveBtnStatus(const UINT8 &portno, const bool &status); //继电器返回成功对应的槽函数
	void slotSetRegulateOk();

	void setValveBtnBackColor(QPushButton *btn, bool status); //设置阀门按钮背景色
	void setRegBtnBackColor(QPushButton *btn, bool status);	//设置调节阀按钮背景色

	void slotFreshFlowRate();//计算流速

	void on_btnSetVerifyStatus_clicked(); //设置检定状态
	void on_btnExitVerifyStatus_clicked();//退出检定状态
	void on_btnReadMeterData_clicked(); //读表数据
	void on_btnModifyMeterNo_clicked(); //修改表号
	void on_btnModifyFlowCoe_clicked(); //修改流量系数
	void on_btn2ModifyFlowCoe_clicked();//二次修改流量系数
	void on_btnSetStandard_clicked();//设置口径
	void on_btnSetTime_clicked();//设置系统时间
	void on_btnSetAddr1_clicked();//设置一级地址
	void on_btnSetAddr2_clicked();//设置二级地址
	void on_btnStartModifyCoe_clicked(); //下发流量修正开始命令
	void on_btnModifyData_clicked(); //修改表数据-历史数据
	

	void on_btnOpenCom_clicked(); //打开串口
	void on_btnCloseCom_clicked();//关闭串口

	void on_btnStdTempCollect_clicked(); //采集标准温度
	void on_btnStdTempStop_clicked();    //停止采集标准温度
	void on_lnEditInStdResist_textChanged(const QString & text);
	void on_lnEditOutStdResist_textChanged(const QString & text);

	void slotAskStdTemperature();
	void clearMeterDispInfo();
	void setMeterComboxEnabled(bool flag);
	void setMeterOperBtnEnabled(bool flag);

private:
	Ui::DataTestDlgClass ui;
	/*******************标准流量计******************************/
	void initInstStdCom();//瞬时流量串口初始化
	void initAccumStdCom();//累积流量串口初始化

	uchar m_accumDevAddress;//当前累积流量采集所使用的力创模块设备地址, 默认为0x01
	uchar m_instDevAddress;//当前瞬时流量采集所使用的力创模块设备地址, 默认为0x01

	lcModRtuComObject *m_instantFlowCom;//瞬时流量串口对象
	ComThread m_instantFlowThread;//瞬时流量采集线程
	QTimer* m_instSTDMeterTimer;//瞬时流量计时器
	QByteArray m_instStdPulse;//瞬时流量脉冲值, 需二次加工

	lcModRtuComObject *m_accumulateFlowCom;//累积流量串口对象
	ComThread m_accumFlowThread;//累积流量采集线程
	QTimer* m_accumSTDMeterTimer;//累积流量计时器
	QByteArray m_accumStdPulse;//16路累积流量脉冲值, 需二次加工

	QList<int> m_instRouteIsRead;//瞬时流量的通道号是否被采集过
	QList<int> m_accumRouteIsRead;//累积流量的通道号是否被采集过
	QSettings *m_stdParam;//读取标准表设置

	int getRouteByWdg(flow_rate_wdg, flow_type);//根据部件号读取标准表的通道号
	float getStdUpperFlow(flow_rate_wdg wdgIdx);//根据部件号读取相应标准表的上限流量值
	double getStdPulse(flow_rate_wdg wdgIdx);//根据部件号读取相应标准表的脉冲值

	void freshInstStdMeter();//刷新瞬时读数
	void freshAccumStdMeter();//刷新累积读数

	float getInstFlowRate(flow_rate_wdg idx);
	float getAccumFLowVolume(flow_rate_wdg idx);

	/******************标准流量计end***************************/


private slots:
	/*******************标准流量计******************************/
	void slotAskInstPulse();//请求瞬时流量
	void slotAskAccumPulse();//请求累积流量

	void slotGetInstStdMeterPulse(const QByteArray &);//瞬时流量槽函数
	void slotGetAccumStdMeterPulse(const QByteArray &);//累积流量槽函数
	/******************标准流量计end***************************/
	void openPump();
	void closePump();
};

#endif // DATATESTDLG_H
