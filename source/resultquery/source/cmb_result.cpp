#include <QtSql/QSqlRelationalDelegate>
#include <QtCore/QDebug>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>

#include "cmb_result.h"
#include "report.h"
#include "algorithm.h"

CmbResultDlg::CmbResultDlg(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	model = new QSqlRelationalTableModel(this, g_defaultdb);
}

CmbResultDlg::~CmbResultDlg()
{

}

void CmbResultDlg::showEvent(QShowEvent *)
{
	initCmb();
}

void CmbResultDlg::closeEvent(QCloseEvent *)
{
	emit signalClosed();
}

void CmbResultDlg::initCmb()
{
	//制造单位
	int col_id1 = 0;
	QSqlRelationalTableModel *model1 = new QSqlRelationalTableModel(this, g_defaultdb);  
	model1->setTable("T_Manufacture_Dept");  
	model1->setRelation(col_id1, QSqlRelation("T_Manufacture_Dept","F_ID","F_Desc"));  
	QSqlTableModel *relationModel1 = model1->relationModel(col_id1);   
	ui.cmbManufactDept->setModel(relationModel1);  
	ui.cmbManufactDept->setModelColumn(relationModel1->fieldIndex("F_Desc")); 
	ui.cmbManufactDept->insertItem(ui.cmbManufactDept->count(), "");
	ui.cmbManufactDept->setCurrentIndex(ui.cmbManufactDept->count()-1);

	//送检单位
	int col_id2 = 0;
	QSqlRelationalTableModel *model2 = new QSqlRelationalTableModel(this, g_defaultdb);  
	model2->setTable("T_Verify_Dept");  
	model2->setRelation(col_id2, QSqlRelation("T_Verify_Dept","F_ID","F_Desc"));  
	QSqlTableModel *relationModel2 = model2->relationModel(col_id2);   
	ui.cmbVerifyDept->setModel(relationModel2);  
	ui.cmbVerifyDept->setModelColumn(relationModel2->fieldIndex("F_Desc")); 
	ui.cmbVerifyDept->insertItem(ui.cmbVerifyDept->count(), "");
	ui.cmbVerifyDept->setCurrentIndex(ui.cmbVerifyDept->count()-1);

	//检定员
	int col_id3 = 0;
	QSqlRelationalTableModel *model3 = new QSqlRelationalTableModel(this, g_defaultdb);  
	model3->setTable("T_User_Def_Tab");  
	model3->setRelation(col_id3, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));  
	QSqlTableModel *relationModel3 = model3->relationModel(col_id3);   
	ui.cmbVerifyPerson->setModel(relationModel3);  
	ui.cmbVerifyPerson->setModelColumn(relationModel3->fieldIndex("F_Desc")); 
	ui.cmbVerifyPerson->insertItem(ui.cmbVerifyPerson->count(), "");
	ui.cmbVerifyPerson->setCurrentIndex(ui.cmbVerifyPerson->count()-1);

	//表型号
	int col_id4 = 0;
	QSqlRelationalTableModel *model4 = new QSqlRelationalTableModel(this, g_defaultdb);  
	model4->setTable("T_Meter_Model");  
	model4->setRelation(col_id4, QSqlRelation("T_Meter_Model","F_ID","F_Name"));  
	QSqlTableModel *relationModel4 = model4->relationModel(col_id4);   
	ui.cmbModel->setModel(relationModel4);  
	ui.cmbModel->setModelColumn(relationModel4->fieldIndex("F_Name")); 
	ui.cmbModel->insertItem(ui.cmbModel->count(), "");
	ui.cmbModel->setCurrentIndex(ui.cmbModel->count()-1);

	//表规格
	int col_id5 = 0;
	QSqlRelationalTableModel *model5 = new QSqlRelationalTableModel(this, g_defaultdb);  
	model5->setTable("T_Meter_Standard");  
	model5->setRelation(col_id5, QSqlRelation("T_Meter_Standard","F_ID","F_Name"));  
	QSqlTableModel *relationModel5 = model5->relationModel(col_id5);   
	ui.cmbStandard->setModel(relationModel5);  
	ui.cmbStandard->setModelColumn(relationModel5->fieldIndex("F_Name")); 
	ui.cmbStandard->insertItem(ui.cmbStandard->count(), "");
	ui.cmbStandard->setCurrentIndex(ui.cmbStandard->count()-1);

	//表等级
	ui.cmbGrade->insertItem(ui.cmbGrade->count(), "1");
	ui.cmbGrade->insertItem(ui.cmbGrade->count(), "2");
	ui.cmbGrade->insertItem(ui.cmbGrade->count(), "3");
	ui.cmbGrade->insertItem(ui.cmbGrade->count(), "");
	ui.cmbGrade->setCurrentIndex(ui.cmbGrade->count()-1);

	//是否合格
	ui.cmbIsValid->setCurrentIndex(ui.cmbIsValid->count()-1);

	ui.startDateTime->setDateTime(QDateTime::currentDateTime().addSecs(-3600));//过去一小时
	ui.endDateTime->setDateTime(QDateTime::currentDateTime());
}

void CmbResultDlg::on_btnQuery_clicked()
{
	getCondition();
	queryData();
}

void CmbResultDlg::on_btnExport_clicked()
{
	if (NULL==model)
	{
		QMessageBox::warning(this, tr("Warning"), tr("no data need to be exported!"));
		return;
	}

	QString defaultPath = QProcessEnvironment::systemEnvironment().value("ADEHOME") + "//report//cmb//" + QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
	QString file = QFileDialog::getSaveFileName(this, tr("Save File"), defaultPath, tr("Microsoft Excel (*.xls)"));//获取保存路径
	if (!file.isEmpty())
	{
		try
		{
			getCondition();
			CReport rpt(m_conStr);
			rpt.setIniName("rptconfig_cmb.ini");
			rpt.writeRpt();
			rpt.saveTo(file);
			QMessageBox::information(this, tr("OK"), tr("export excel file successful!"));
		}
		catch (QString e)
		{
			QMessageBox::warning(this, tr("Error"), e);
		}
	}
}

void CmbResultDlg::getCondition()
{
	m_conStr.clear();

	m_conStr.append( QString(" F_TimeStamp>=\'%1\' and F_TimeStamp<=\'%2\'").arg(ui.startDateTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"))\
		.arg(ui.endDateTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"))); //起止时间
	int idx, count;

	idx = ui.cmbManufactDept->currentIndex();
	count = ui.cmbManufactDept->count();
	if (idx != (count-1))//制造单位
	{
		m_conStr.append(QString(" and F_ManufactDept=%1").arg(ui.cmbManufactDept->currentIndex()));
	}

	idx = ui.cmbVerifyDept->currentIndex();
	count = ui.cmbVerifyDept->count();
	if (idx != (count-1))//送检单位
	{
		m_conStr.append(QString(" and F_VerifyDept=%1").arg(ui.cmbVerifyDept->currentIndex()));
	}

	idx = ui.cmbVerifyPerson->currentIndex();
	count = ui.cmbVerifyPerson->count();
	if (idx != (count-1))//检定员
	{
		m_conStr.append(QString(" and F_VerifyPerson=%1").arg(ui.cmbVerifyPerson->currentIndex()));
	}

	idx = ui.cmbModel->currentIndex();
	count = ui.cmbModel->count();
	if (idx != (count-1))//表型号
	{
		m_conStr.append(QString(" and F_Model=%1").arg(ui.cmbModel->currentIndex()));
	}

	idx = ui.cmbStandard->currentIndex();
	count = ui.cmbStandard->count();
	if (idx != (count-1))//表规格
	{
		m_conStr.append(QString(" and F_Standard=%1").arg(ui.cmbStandard->currentIndex()));
	}

	idx = ui.cmbGrade->currentIndex();
	count = ui.cmbGrade->count();
	if (idx != (count-1))//表等级
	{
		m_conStr.append(QString(" and F_Grade=%1").arg(ui.cmbGrade->currentIndex()+1));
	}

	idx = ui.cmbInstallPos->currentIndex();
	count = ui.cmbInstallPos->count();
	if (idx != (count-1))//安装位置
	{
		m_conStr.append(QString(" and F_InstallPos=%1").arg(ui.cmbInstallPos->currentIndex()));
	}

	idx = ui.cmbIsValid->currentIndex();
	count = ui.cmbIsValid->count();
	if (idx != (count-1))//是否合格
	{
		m_conStr.append(QString(" and F_Result=%1").arg(ui.cmbIsValid->currentIndex()));
	}

	if (!ui.lnEditMeterNO->text().isEmpty())//表号
	{
		m_conStr.append(QString(" and F_MeterNo like \"\%%1\%\"").arg(ui.lnEditMeterNO->text()));
	}
}

void CmbResultDlg::queryData()
{
	model->setEditStrategy(QSqlTableModel::OnFieldChange); //属性变化时写入数据库
	model->setTable("T_Combined_Verify_Record");
	model->setFilter(m_conStr); //设置查询条件

	////设置外键
	model->setRelation(3, QSqlRelation("T_Meter_Standard","F_ID","F_Name"));
	model->setRelation(4, QSqlRelation("T_Meter_Model","F_ID","F_Name"));
	model->setRelation(7, QSqlRelation("T_Manufacture_Dept","F_ID","F_Desc"));
	model->setRelation(8, QSqlRelation("T_Verify_Dept","F_ID","F_Desc"));
	model->setRelation(9, QSqlRelation("T_User_Def_Tab","F_ID","F_Desc"));
	model->setRelation(27, QSqlRelation("T_Yes_No_Tab","F_ID","F_Desc"));

	////设置水平标题
	model->setHeaderData(1, Qt::Horizontal, QObject::tr("TimeStamp"));//时间戳（'yyyy-MM-dd HH:mm:ss.zzz')
	model->setHeaderData(2, Qt::Horizontal, QObject::tr("MeterNo"));//表号(14位数字: 6 + 8)
	model->setHeaderData(3, Qt::Horizontal, QObject::tr("Standard"));//表规格(DN15/DN20/DN25)，外键(T_Meter_Standard.F_ID)
	model->setHeaderData(4, Qt::Horizontal, QObject::tr("Model"));//表型号，外键(T_Meter_Model.F_ID)
	model->setHeaderData(5, Qt::Horizontal, QObject::tr("PickCode"));//采集代码（1,2,3）
	model->setHeaderData(6, Qt::Horizontal, QObject::tr("Grade"));//计量等级（1,2,3）
	model->setHeaderData(7, Qt::Horizontal, QObject::tr("ManufactDept"));//制造单位，外键(T_Manufacture_Dept.F_ID)
	model->setHeaderData(8, Qt::Horizontal, QObject::tr("VerifyDept"));//送检单位，外键(T_Verify_Dept.F_ID)
	model->setHeaderData(9, Qt::Horizontal, QObject::tr("VerifyPerson"));//检定员，外键(T_User_Def_Tab.F_ID)
	model->setHeaderData(10, Qt::Horizontal, QObject::tr("DeltaTemp "));//温差(K)
	model->setHeaderData(11, Qt::Horizontal, QObject::tr("VerifyVolume "));//检定量(L)
	model->setHeaderData(12, Qt::Horizontal, QObject::tr("DeltaTempMin "));//最小温差(K)
	model->setHeaderData(13, Qt::Horizontal, QObject::tr("InstallPos"));//安装位置(0:进口；1:出口)
	model->setHeaderData(14, Qt::Horizontal, QObject::tr("HeatUnit"));//热量单位(1:kWh; 0:MJ)
	model->setHeaderData(15, Qt::Horizontal, QObject::tr("StdTempIn"));//入口温度-标准温度计(℃)
	model->setHeaderData(16, Qt::Horizontal, QObject::tr("StdTempOut"));//出口温度-标准温度计(℃)
	model->setHeaderData(17, Qt::Horizontal, QObject::tr("StdResistIn"));//入口电阻-标准温度计(Ω)
	model->setHeaderData(18, Qt::Horizontal, QObject::tr("StdResistOut"));//出口电阻-标准温度计(Ω)
	model->setHeaderData(19, Qt::Horizontal, QObject::tr("Kcoe"));//K系数
	model->setHeaderData(20, Qt::Horizontal, QObject::tr("StdValueE"));//理论值(热量，kwh)
	model->setHeaderData(21, Qt::Horizontal, QObject::tr("MeterV0"));//热量表初值(体积)，单位L
	model->setHeaderData(22, Qt::Horizontal, QObject::tr("MeterV1"));//热量表终值(体积)，单位L
	model->setHeaderData(23, Qt::Horizontal, QObject::tr("MeterE0"));//热量表初值(热量)，单位kWh
	model->setHeaderData(24, Qt::Horizontal, QObject::tr("MeterE1"));//热量表终值(热量)，单位kWh
	model->setHeaderData(25, Qt::Horizontal, QObject::tr("DispError"));//示值误差，单位%
	model->setHeaderData(26, Qt::Horizontal, QObject::tr("StdError"));//要求误差(合格标准),单位%
	model->setHeaderData(27, Qt::Horizontal, QObject::tr("Result"));//检定结果(1：合格，0：不合格)

	model->select();
	ui.tableView->setModel(model);
	ui.tableView->resizeColumnsToContents(); //列宽度自适应
	ui.tableView->setItemDelegate(new QSqlRelationalDelegate(ui.tableView)); //外键字段只能在已有的数据中编辑
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //使其不可编辑

	ui.tableView->hideColumn(0);
	ui.tableView->hideColumn(28);
	ui.tableView->hideColumn(29);
	ui.tableView->hideColumn(30);
}

void CmbResultDlg::on_btnExit_clicked()
{
	this->close();
}