/***********************************************
**  文件名:     scancodedlg.cpp
**  功能:       扫码写表号
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2015/9/8
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2015/08 第一版
**  内容包含:
**  说明:		
**  更新记录:   
***********************************************/

#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtCore/QThread>
#include <QtSql/QSqlTableModel>
#include <QtGui/QFileDialog>
#include <QtCore/QSignalMapper>
#include <QCloseEvent>

#include "../../include/scancodedlg.h"
#include "commondefine.h"
#include "algorithm.h"
#include "qtexdb.h"
#include "parasetdlg.h"
#include "readcomconfig.h"

ScanCodeDlg::ScanCodeDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	qDebug()<<"ScanCodeDlg thread:"<<QThread::currentThreadId();
	ui.setupUi(this);
	ui.btnParaSet->hide();
	m_readComConfig = new ReadComConfig(); //读串口设置接口（必须在initBalanceCom前调用）

	m_meterObj = NULL;      //热量表通讯


	m_maxMeterNum = 0;       //某规格表最多支持的检表个数
	m_oldMaxMeterNum = 0;
	m_pickcode = PROTOCOL_VER_DELU; //采集代码 默认德鲁

	m_paraSetDlg = NULL;    //参数设置对话框
	m_paraSetReader = new ParaSetReader(); //读参数设置接口
	m_nowParams = NULL;
	if (!readNowParaConfig()) //获取当前检定参数
	{
		qWarning()<<"读取参数配置文件失败!";
	}

// 	QTimer::singleShot(3000, this, SLOT(close()));
	this->resize(600, 600);
}

ScanCodeDlg::~ScanCodeDlg()
{
}

void ScanCodeDlg::showEvent(QShowEvent * event)
{
	qDebug()<<"ScanCodeDlg::showEvent";
}

void ScanCodeDlg::closeEvent(QCloseEvent * event)
{
	qDebug()<<"^^^^^FlowWeightDlg::closeEvent";
/*	int button = QMessageBox::question(this, tr("Question"), tr("Exit Really ?"), \
		QMessageBox::Yes|QMessageBox::Default, QMessageBox::No|QMessageBox::Escape);
	if (button == QMessageBox::No)
	{
		return event->ignore();
	}
	else
	{
		event->accept();
	}
*/
	if (m_paraSetReader) //读检定参数
	{
		delete m_paraSetReader;
		m_paraSetReader = NULL;
	}

	if (m_paraSetDlg)    //参数设置对话框
	{
		delete m_paraSetDlg;
		m_paraSetDlg = NULL;
	}

	if (m_readComConfig) //读串口设置
	{
		delete m_readComConfig;
		m_readComConfig = NULL;
	}

	//热量表通讯
	if (m_meterObj)
	{
		delete []m_meterObj;
		m_meterObj = NULL;

		for (int i=0; i<m_oldMaxMeterNum; i++)
		{
			m_meterThread[i].exit();
		}
	}
	
	emit signalClosed();
}

void ScanCodeDlg::resizeEvent(QResizeEvent * event)
{
	qDebug()<<"resizeEvent...";

	int th = ui.tableWidget->size().height();
	int tw = ui.tableWidget->size().width();
	int hh = ui.tableWidget->horizontalHeader()->size().height();
	int vw = ui.tableWidget->verticalHeader()->size().width();
	vw = (vw <= 0 ? 58 : vw);
	int vSize = (int)((th-hh-5)/(m_maxMeterNum <= 0 ? 12 : m_maxMeterNum));
	int hSize = (int)((tw-vw-5)/COL_COUNT);
	ui.tableWidget->verticalHeader()->setDefaultSectionSize(vSize);
	ui.tableWidget->horizontalHeader()->setDefaultSectionSize(hSize);
}

//热量表通讯串口
void ScanCodeDlg::initMeterCom()
{
	if (m_meterObj)
	{
		delete []m_meterObj;
		m_meterObj = NULL;

		for (int i=0; i<m_oldMaxMeterNum; i++)
		{
			m_meterThread[i].exit();
		}
	}
	if (m_maxMeterNum <= 0)
	{
		return;
	}

	m_oldMaxMeterNum = m_maxMeterNum;
	m_meterThread = new ComThread[m_maxMeterNum];
	m_meterObj = new MeterComObject[m_maxMeterNum];
	for (int i=0; i<m_maxMeterNum; i++)
	{
		m_meterObj[i].moveToThread(&m_meterThread[i]);
		m_meterObj[i].setProtocolVersion(m_pickcode); //设置表协议类型
		m_meterThread[i].start();
		m_meterObj[i].openMeterCom(&m_readComConfig->ReadMeterConfigByNum(i+1));

		connect(&m_meterObj[i], SIGNAL(readMeterNoIsOK(const QString&, const QString&)), this, SLOT(slotSetMeterNumber(const QString&, const QString&)));
	}
}

//获取当前检定参数;初始化表格控件；初始化热量表通讯串口
int ScanCodeDlg::readNowParaConfig()
{
	if (NULL == m_paraSetReader)
	{
		return false;
	}

	m_nowParams = m_paraSetReader->getParams();
	m_pickcode = m_nowParams->m_pickcode; //采集代码
	m_numPrefix = getNumPrefixOfManufac(m_pickcode); //表号前缀
	m_maxMeterNum = m_nowParams->m_maxMeters;//不同表规格对应的最大检表数量

	initTableWidget();
	initMeterCom();

	return true;
}

//初始化表格控件
void ScanCodeDlg::initTableWidget()
{
	if (m_maxMeterNum <= 0)
	{
		return;
	}
	ui.tableWidget->setRowCount(m_maxMeterNum); //设置表格行数

	QSignalMapper *signalMapper1 = new QSignalMapper();
	QSignalMapper *signalMapper2 = new QSignalMapper();

	QStringList vLabels;
	for (int i=0; i< ui.tableWidget->rowCount(); i++)
	{
		vLabels<<QString(QObject::tr("meterPosNo%1").arg(i+1));

		for (int j=0; j<ui.tableWidget->columnCount(); j++)
		{
			ui.tableWidget->setItem(i, j, new QTableWidgetItem(QString("")));
			ui.tableWidget->item(i, j)->setTextAlignment(Qt::AlignCenter);
		}

		//设为只读
// 		ui.tableWidget->item(i, COL_NOW_METER_NO)->setFlags(Qt::NoItemFlags);

		//设置按钮
		QPushButton *btnReadNO = new QPushButton(QObject::tr("\(%1\)").arg(i+1) + tr("ReadNO"));
		ui.tableWidget->setCellWidget(i, COL_READ_METER_NO, btnReadNO);
		signalMapper1->setMapping(btnReadNO, i);
		connect(btnReadNO, SIGNAL(clicked()), signalMapper1, SLOT(map()));

		QPushButton *btnModNO = new QPushButton(QObject::tr("\(%1\)").arg(i+1) + tr("ModifyNO"));
		ui.tableWidget->setCellWidget(i, COL_MODIFY_METER_NO, btnModNO);
		signalMapper2->setMapping(btnModNO, i);
		connect(btnModNO, SIGNAL(clicked()), signalMapper2, SLOT(map()));
	}
	connect(signalMapper1, SIGNAL(mapped(const int &)),this, SLOT(slotReadNO(const int &)));
	connect(signalMapper2, SIGNAL(mapped(const int &)),this, SLOT(slotModifyMeterNO(const int &)));

	ui.tableWidget->setVerticalHeaderLabels(vLabels);
// 	ui.tableWidget->setFont(QFont("Times", 15, QFont::DemiBold, true));
// 	ui.tableWidget->resizeColumnsToContents();
//	ui.tableWidget->setColumnWidth(COLUMN_METER_NUMBER, 125);
}

//自动读取表号成功 显示表号
void ScanCodeDlg::slotSetMeterNumber(const QString& comName, const QString& meterNo)
{
	int meterPos = m_readComConfig->getMeterPosByComName(comName);
	int row = meterPos - 1;
	if (row < 0)
	{
		return;
	}
	ui.tableWidget->item(row, COL_OLD_METER_NO)->setText(meterNo.right(8)); //表号
	QString newMeterNO = ui.tableWidget->item(row, COL_NEW_METER_NO)->text();
	if (!newMeterNO.isEmpty() && newMeterNO!=meterNo.right(8))
	{
		ui.tableWidget->item(row, COL_OLD_METER_NO)->setForeground(QBrush(Qt::red));
	}
}

//参数设置
void ScanCodeDlg::on_btnParaSet_clicked()
{
	if (NULL == m_paraSetDlg)
	{
		m_paraSetDlg = new ParaSetDlg();
	}
	else
	{
		delete m_paraSetDlg;
		m_paraSetDlg = new ParaSetDlg();
	}
	connect(m_paraSetDlg, SIGNAL(saveSuccessSignal()), this, SLOT(readNowParaConfig()));
	m_paraSetDlg->show();
}

void ScanCodeDlg::on_btnExit_clicked()
{
	this->close();
}

/*
** 响应处理表格内容变化
   输入参数：
      row：行数，从0开始
	  column：列数，从0开始
*/
void ScanCodeDlg::on_tableWidget_cellChanged(int row, int column)
{
	if (column != COL_NEW_METER_NO)
	{
		return;
	}
	bool ok;
	ui.tableWidget->item(row, column)->text().toInt(&ok);
	if (ui.tableWidget->item(row, column)->text().size()!=8 || !ok)
	{
		return;
	}
	slotModifyMeterNO(row);
}

//请求读表号（所有表、广播地址读表）
void ScanCodeDlg::on_btnAllReadNO_clicked()
{
	qDebug()<<"on_btnAllReadNO_clicked...";
	for (int i=0; i<m_maxMeterNum; i++)
	{
		slotReadNO(i);
	}
}

//修改表号（所有表）
void ScanCodeDlg::on_btnAllModifyNO_clicked()
{
	qDebug()<<"on_btnAllModifyNO_clicked...";
	for (int i=0; i<m_maxMeterNum; i++)
	{
		slotModifyMeterNO(i);
	}
}

/*
** 修改表号
** 输入参数：
	row:行号，由row可以知道当前热表对应的串口、表号、误差等等
   注意：表号为14位
*/
void ScanCodeDlg::slotModifyMeterNO(const int &row)
{
// 	qDebug()<<"slotModifyMeterNO row ="<<row;
	QString oldNO = ui.tableWidget->item(row, COL_OLD_METER_NO)->text();
	QString nowMeterNO = m_numPrefix + (oldNO.isEmpty() ? "00000000" : oldNO);
	QString newMeterNO = m_numPrefix + ui.tableWidget->item(row, COL_NEW_METER_NO)->text();
	m_meterObj[row].askModifyMeterNO(nowMeterNO, newMeterNO);
// 	qDebug()<<"slotModifyMeterNO: "<<nowMeterNO<<", "<<newMeterNO;
	ui.tableWidget->setCurrentCell(row+1, COL_NEW_METER_NO);
	if (row == (ui.tableWidget->rowCount()-1))
	{
		on_btnAllReadNO_clicked();
	}
}

/*
** 读表号
** 输入参数：
row:行号，由row可以知道当前热表对应的串口、表号、误差等等
*/
void ScanCodeDlg::slotReadNO(const int &row)
{
	ui.tableWidget->item(row, COL_OLD_METER_NO)->setText("");
	ui.tableWidget->item(row, COL_OLD_METER_NO)->setForeground(QBrush());
	qDebug()<<"slotReadNO row ="<<row;
	m_meterObj[row].askReadMeterNO();
}
