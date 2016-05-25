#ifndef FLOWWEIGHT_H
#define FLOWWEIGHT_H

#ifdef FLOWWEIGHT_DLL
#  ifdef WIN32
#  define FLOWWEIGHT_EXPORT __declspec(dllexport)
#  else
#  define FLOWWEIGHT_EXPORT
#  endif
#else
#  ifdef WIN32
#  define FLOWWEIGHT_EXPORT __declspec(dllimport)
#  else
#  define FLOWWEIGHT_EXPORT
#  endif
#endif

#include <QtGui/QWidget>
#include <QtGui/QDataWidgetMapper>

#include "ui_flowweight.h"
#include "comobject.h"

class CAlgorithm;
class ParaSetDlg;
class ParaSetReader;
class ReadComConfig;


class FLOWWEIGHT_EXPORT FlowWeightDlg : public QWidget
{
	Q_OBJECT

public:
	FlowWeightDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~FlowWeightDlg();

	QDataWidgetMapper *m_meterStdMapper;

	QTimer *m_exaustTimer; //排气定时器

	ComThread m_balanceThread; //天平采集线程
	BalanceComObject *m_balanceObj;

	ComThread m_tempThread;  //温度采集线程
	TempComObject *m_tempObj;
	QTimer *m_tempTimer;

	ComThread m_valveThread;   //阀门控制线程
	ControlComObject *m_controlObj;
	QMap<int, bool> m_valveStatus; //阀门号与阀门状态的映射关系
	QMap<int, QToolButton*> m_valveBtn;	//阀门号与阀门按钮的映射关系
	int m_nowPortNo;	//当前控制阀门端口号

	ComThread *m_meterThread;	//热量表通讯线程
	MeterComObject *m_meterObj;	

	CAlgorithm *m_chkAlg;//检定过程用到的计算方法

	bool m_stopFlag;     //关闭界面后退出

	//检定过程相关的控制参数 begin
	ParaSetReader *m_paraSetReader;
	ParaSetDlg *m_paraSetDlg;
	Verify_Params_PTR m_nowParams; //当前检定参数
	bool m_continueVerify;    //是否连续检定
	bool m_resetZero;         //是否初值回零
	bool m_autopick;          //是否自动采集
	int m_flowPointNum;       //流量点的个数
	int m_exaustSecond;		  //排气时间
	int m_standard;           //表规格
	int m_model;              //表型号
	int m_pickcode;			  //采集代码(热表通讯协议版本号)
	QString m_numPrefix;      //表号前缀(14位表号的前6位）
	float m_flowSC;           //流量检定安全系数
	bool m_adjErr;            //是否调整误差
	bool m_writeNO;           //是否修改表号
	bool m_repeatverify;      //是否重复检测
	//检定过程相关的控制参数 end

	int m_avgTFCount;		  //计算平均温度和平均流量用的累加计数器
	int m_maxMeterNum;        //被检表的最大个数
	int m_oldMaxMeterNum;     //上次被检表的最大个数
	int m_validMeterNum;          //实际被检表的个数
	int m_oldValidMeterNum;		  //上次实际被检表的个数
	QMap<int, int> m_meterPosMap; //被检表下标与表位号的映射关系

	float *m_meterStartValue; //被检表的初值
	float *m_meterEndValue;   //被检表的终值
	float *m_meterTemper;	  //被检表的温度
	float *m_meterDensity;    //被检表的密度
	float *m_meterStdValue;   //被检表的标准值
	float *m_meterError;	  //被检表的误差(当前流量点不同表位的误差)
	float m_balStartV;        //天平初值
	float m_balEndV;          //天平终值
	float m_pipeInTemper;     //入口温度
	float m_pipeOutTemper;    //出口温度
	float m_realFlow;		  //流速(m3/h）
	float **m_meterErr;       //被检表的误差(不同表位、不同流量点的误差)
	int *m_meterResult;       //检表结果 1:合格；0:不合格
	MeterCoe_PTR *m_oldMeterCoe; //热量表原来的各流量点系数

	Flow_Verify_Record_PTR m_recPtr; //有效的检定记录
	QString m_timeStamp; //时间戳 秒数
	QString m_nowDate;  
	QString m_validDate;
	UINT32 m_newMeterNO;   //新表号
	QMap<int, UINT32> m_mapMeterPosAndNewNO; //检表结果合格的表位与新表号映射关系

	int m_nowOrder;				//当前检定次序

	now_state m_state; //当前运行状态（初始态、读初值态、读终值态）
	table_columns m_now_column; //当前点击列

	ReadComConfig *m_readComConfig; //读串口设置
	PortSet_Ini_STR m_portsetinfo;  //端口配置

	//计算流速用
	uint m_totalcount;  //计数器
	float m_startWeight;//天平初值
	float m_endWeight;  //天平终值
	float m_deltaWeight[FLOW_SAMPLE_NUM];
	QTimer *m_flowRateTimer;  //计时器:用于计算流速

	//天平最大容量和回水底量
	float m_balMaxWht;
	float m_balBottomWht;

	void initBalanceCom();     //天平串口
	void initTemperatureCom(); //温度采集串口
	void initControlCom();     //阀门控制串口
	void initMeterCom();       //热量表串口
	void initValveStatus();	   //初始化阀门状态

	int isComAndPortNormal();   //串口、端口设置是否正常
	int isDataCollectNormal();	//检查数据采集是否正常（天平、温度、电磁流量计等）
	int isMeterPosValid(int meterPos); //判断表位号是否有效(该表位是否需要检表)
	int getValidMeterNum();       //获取有效的检表个数()

	void showEvent(QShowEvent * event);
	void closeEvent(QCloseEvent * event);
	void resizeEvent(QResizeEvent * event);

public slots:

	int readNowParaConfig();	 //获取当前检定参数
	void showNowKeyParaConfig(); //显示当前关键参数设置信息
	void initTableWidget();     //设置表格行数

	void on_btnStart_clicked();   //点击"开始"按钮
	void on_btnExhaust_clicked(); //点击"排气"按钮
	void on_btnGoOn_clicked();    //点击"继续"按钮
	void on_btnStop_clicked();    //点击"终止检测"按钮
	void on_btnExit_clicked();    //点击"退出"按钮
	int startExhaustCountDown();  //开始排气倒计时
	void slotExaustFinished();    //排气时间结束
	int prepareInitBalance();     //开始检定前，准备天平初始重量
	int readAllMeterFlowCoe();    //读取所有被检表的流量系数
	int setAllMeterVerifyStatus();//设置热量表进入检定状态
	int openAllValveAndPump();    //打开所有阀门和水泵
	int closeAllValveAndPumpOpenOutValve(); //关闭所有阀门和水泵、打开防水阀
	int closeAllFlowPointValves();//关闭所有流量点阀门
	int closeWaterOutValve();     //关闭放水阀
	int openWaterOutValve();      //打开放水阀
	int isBalanceValueBigger(float targetV, bool flg=true);    //判断天平质量,flg: true-要求大于目标重量(默认)；false-要求小于目标重量
	int judgeBalanceAndCalcAvgTemperAndFlow(float targetV); //判断天平质量，并累加进出口温度，每秒累加一次，用于计算进出口平均温度
	void stopVerify();            //停止检定
	void startVerify();           //开始检定
	bool judgeBalanceCapacity();   //判断天平容量是否能够满足检定用量 连续检定
	int judgeBalanceCapacitySingle(int order); //判断天平容量是否能够满足检定用量 不连续检定
	int prepareVerifyFlowPoint(int order);     //准备单个流量点的检定
	int startVerifyFlowPoint(int order);       //开始单个流量点的检定
	int openValve(UINT8 portno);    //打开控制阀
	int closeValve(UINT8 portno);   //关闭控制阀
	int operateValve(UINT8 portno); //操作控制阀：打开或者关闭
	int openWaterPump();			//打开水泵
	int closeWaterPump();			//关闭水泵
	int operateWaterPump();			//操作水泵：打开或者关闭
	int getMeterStartValue();     //获取表初值
	int getMeterEndValue();       //获取表终值
	void makeStartValueByLastEndValue(); //将上一次检定后的终值作为本次的初值
	int calcAllMeterError();      //计算所有被检表的误差
	int calcMeterError(int idx);  //计算某个表的误差
	int calcVerifyResult();       //计算检定结果

	void slotFreshBalanceValue(const float& balValue);  //刷新天平数值
	void slotAskPipeTemperature();//请求管路温度
	void slotFreshComTempValue(const QString& tempStr); //刷新温度值
	void slotFreshFlowRate(); //计算流速

	void slotSetValveBtnStatus(const UINT8 &portno, const bool &status); //继电器返回成功对应的槽函数
	void slotSetRegulateOk();     //调节阀返回成功对应的槽函数

	void slotSetMeterNumber(const QString& comName, const QString& meterNumber);
	void slotSetMeterFlow(const QString& comName, const QString& flow);
	void slotFreshBigCoe(const QString& comName, const QString& bigCoe); //刷新大流量系数
	void slotFreshMid2Coe(const QString& comName, const QString& mid2Coe); //刷新中流2流量系数
	void slotFreshMid1Coe(const QString& comName, const QString& mid1Coe); //刷新中流1流量系数
	void slotFreshSmallCoe(const QString& comName, const QString& smallCoe); //刷新小流量系数
	void slotMeterCommunicateSuccess(const QString& comName); //热量表通讯成功
	void setValveBtnBackColor(QToolButton *btn, bool status); //设置阀门按钮背景色
	void setRegBtnBackColor(QPushButton *btn, bool status);	  //设置调节阀按钮背景色

	void on_btnParaSet_clicked();	   //参数设置
	void on_btnWaterIn_clicked();      //进水阀
	void on_btnWaterOut_clicked();     //放水阀
	void on_btnValveBig_clicked();     //大流量阀
	void on_btnValveMiddle1_clicked(); //中流一
	void on_btnValveMiddle2_clicked(); //中流二
	void on_btnValveSmall_clicked();   //小流量阀

	void on_btnWaterPump_clicked(); //水泵
	void on_btnSetFreq_clicked();   //设置变频器频率

	void on_tableWidget_cellChanged(int row, int column);
	int saveAllVerifyRecords(); //保存所有被检表的检定记录
	void clearTableContents();

	void on_btnAllReadData_clicked();    //读表数据(所有表）
	void on_btnAllReadNO_clicked();      //读表号(所有表）
	void on_btnAllVerifyStatus_clicked();//设置检定状态(所有表）
	void on_btnAllAdjError_clicked(); //调整误差(所有表)
	void on_btnAllModifyNO_clicked(); //修改表号(所有表）
	void on_btnAllStartModifyCoe_clicked(); //下发流量修正开始命令(所有表）-只针对航天德鲁新表GB26831协议

	void slotModifyMeterNO(const int &row); //修改表号
	void slotAdjustError(const int &row);   //调整误差
	void slotReadData(const int &row);      //读表数据(单个表)
	void slotVerifyStatus(const int &row);  //检定状态
	void slotReadNO(const int &row);        //读表号
	void slotStartModifyCoe(const int &row);//下发流量修正开始命令

	void saveStartMeterNO(); //保存起始表号

	int isAllMeterInVerifyStatus(); //是否所有表已进入检定状态
	int isAllMeterHasStartModifyCoe(); //是否所有表已下发流量修正开始命令
	int isAllMeterHasReadStartValue(); //是否所有表已读取到初值
	int isAllMeterHasReadEndValue(); //是否所有表已读取到终值

private slots:

signals:
	void signalClosed();

private:
	Ui::FlowWeightClass ui;
	void exportReport();//导出报告
};

#endif //FLOWWEIGHT_H