#ifndef ADJUSTRATEDLG_H
#define ADJUSTRATEDLG_H

#ifdef ADJUSTRATEDLG_DLL
#  ifdef WIN32
#  define ADJUSTRATEDLG_EXPORT __declspec(dllexport)
#  else
#  define ADJUSTRATEDLG_EXPORT
#  endif
#else
#  ifdef WIN32
#  define ADJUSTRATEDLG_EXPORT __declspec(dllimport)
#  else
#  define ADJUSTRATEDLG_EXPORT
#  endif
#endif

#include <QtGui/QWidget>
#include <QSettings>
#include "ui_adjustratedlg.h"
#include "comobject.h"
#include "qtexdb.h"
#include "basedef.h"

class ParaSetReader;
class ParaSetDlg;
class ReadComConfig;

/*
** 类名：AdjustRateDlg
** 功能：调节流速
*/

#define PRECISION (0.03*m_targetRate)//流速设定误差限
#define BIG_RBTN 0
#define MID_RBTN 1
#define GAIN_TARGET_TIMES (10)//如果达到目标误差限的次数大于此数, 则认为调整成功, 停止调整流速
#define ONE_MINUTES	(60000)
#define ADJUST_MINUTES 10//调节流速用掉的时间
#define PUMP_FREQ_MIN 20 //水泵正常工作时的最小频率
#define PUMP_FREQ_MAX 49 //水泵正常工作时的最大频率
#define DELETE_RESOURCE(Pointer)	if (NULL != Pointer)\
									{\
										delete Pointer;\
										Pointer = NULL;\
									}

class ADJUSTRATEDLG_EXPORT AdjustRateDlg : public QWidget
{
	Q_OBJECT

public:
	AdjustRateDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~AdjustRateDlg();

	ParaSetReader *m_paraSetReader;
	ParaSetDlg *m_paraSetDlg;

	ReadComConfig *m_readComConfig; //读串口设置


	ComThread m_valveThread;   //阀门控制线程
	ControlComObject *m_controlObj;

	QMap<int, bool> m_valveStatus;//<阀门端口号，阀门状态>
	QMap<int, QPushButton*> m_valveBtn;	//<阀门端口号，阀门按钮>
	int m_nowPortNo;	//当前控制阀门端口号

	QMap<int, bool> m_regStatus; //<调节阀端口号，调节阀状态>
	QMap<int, QPushButton*> m_regBtn;//<调节阀端口号，调节阀按钮>	
	int m_nowRegNo;  //当前调节阀端口号

	PortSet_Ini_STR m_portsetinfo; //端口配置

	void closeEvent(QCloseEvent * event);
	void showEvent(QShowEvent *event);
	void initControlCom();        //阀门控制串口
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

	void slotSetValveBtnStatus(const UINT8 &portno, const bool &status); //继电器返回成功对应的槽函数
	void slotSetRegulateOk();

	void setValveBtnBackColor(QPushButton *btn, bool status); //设置阀门按钮背景色
	void setRegBtnBackColor(QPushButton *btn, bool status);	//设置调节阀按钮背景色

	void on_btnStartSet_clicked();
	void on_btnSopSet_clicked();

	void on_lnEditKp_big_returnPressed();
	void on_lnEditKi_big_returnPressed();
	void on_lnEditKd_big_returnPressed();
	void on_lnEditCycleTime_big_returnPressed();
	void on_lnEditMaxRate_big_returnPressed();
	void on_lnEditTargetRate_big_returnPressed();

	void on_lnEditKp_mid_returnPressed();
	void on_lnEditKi_mid_returnPressed();
	void on_lnEditKd_mid_returnPressed();
	void on_lnEditCycleTime_mid_returnPressed();
	void on_lnEditMaxRate_mid_returnPressed();
	void on_lnEditTargetRate_mid_returnPressed();

	void on_lnEditKp_pump_returnPressed();
	void on_lnEditKi_pump_returnPressed();
	void on_lnEditKd_pump_returnPressed();
	void on_lnEditCycleTime_pump_returnPressed();
signals:
	void signalClosed();
private:
	Ui::AdjustVelocityDlgClass ui;
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

	/*******************电动调节阀******************************/
	void initAdjustParams();
	QSettings *m_pidConfig;
	QButtonGroup *m_btnGroupValve;

	QRegExp m_rx;
	QTimer *m_setRegularTimer;
	
	QTime m_elapsetime;//计时器, 记录从设定开始到当前的运行时间
	int m_gainPreciseTimes;//达到目标流量的次数

	float m_pre_error;
	float m_curr_error;
	float m_integral;
	int m_degree;
	int m_openRegulateTimes;

	float m_Kp;
	float m_Ki;
	float m_Kd;
	int m_pickCycleTime;//设定周期
	bool m_ifGainTargetRate;//是否已达到目标流量值
	QString m_timeStamp;
	float m_currentRate;
	float m_targetRate;
	float m_maxRate;

	PIDDataPtr m_pidDataPtr;

	void setRegulate(float currentRate, float targetRate);
	void degreeGet(float currentRate, float targetRate);
	void stopSetRegularTimer();
	void savePidParams();
	void installPidParams();
	void initLineEdits();
	void initBtnGroup();
	void forbidInputParams();
	void enableInputParams();
	/******************电动调节阀end************************/

	/******************调节水泵***************************/
	QTimer *m_setPumpTimer;
	float m_pumpKp;
	float m_pumpKi;
	float m_pumpKd;
	int m_pumpCycleTime;

	int m_pumpFreq;

	float m_prePumpErr;
	float m_curPumpErr;
	float m_pumpIntegral;

	void freqGet(float, float);
	/******************调节水泵end************************/


private slots:
	/*******************标准流量计******************************/
	void slotAskInstPulse();//请求瞬时流量
	void slotAskAccumPulse();//请求累积流量

	void slotGetInstStdMeterPulse(const QByteArray &);//瞬时流量槽函数
	void slotGetAccumStdMeterPulse(const QByteArray &);//累积流量槽函数
	/******************标准流量计end***************************/

	/*******************电动调节阀******************************/
	void slotSetRegulate();
	void slotSetPumpFreq();

	void openPump();
	void closePump();
	int openValve(UINT8 portno);
	int closeValve(UINT8 portno);
	void operateBigPidVales();
	void operateMidPidVales();
	void slotValveClicked(int);
	/******************电动调节阀end***************************/
};

#endif // ADJUSTRATEDLG_H
