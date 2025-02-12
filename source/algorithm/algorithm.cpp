/***********************************************
**  文件名:     algorithm.cpp
**  功能:       检定算法及读取配置文件等
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2014/6/26
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2014/06 第一版
**  内容包含:
**  说明:		
**  更新记录:   
***********************************************/

#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include <QtCore/QFile>
#include <QProcessEnvironment>
#include <QCoreApplication>
#include <QTime>
#include <qmath.h>

#include "algorithm.h"
#include "commondefine.h"
#include "qtexdb.h"

QDateTime getProbationStartDate()
{
	QString filename = getFullIniFileName("verifyparaset.ini");//配置文件的文件名
	QSettings settings(filename, QSettings::IniFormat);
	settings.setIniCodec("GB2312");//解决向ini文件中写汉字乱码
	QString probation = settings.value("Other/probation").toString();
	QDateTime regDate = QDateTime::fromString(probation, "yyyyMMddhhmmss");
	return regDate;
}

void setProbationStartDate()
{
	QString filename = getFullIniFileName("verifyparaset.ini");//配置文件的文件名
	QSettings settings(filename, QSettings::IniFormat);
	settings.setIniCodec("GB2312");//解决向ini文件中写汉字乱码
	QString probation = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
	settings.setValue("Other/probation", probation);
}

void sleep(unsigned int msec)
{
	QTime n = QTime::currentTime();
	QTime now;
	do
	{
		now = QTime::currentTime();
	} while(n.msecsTo(now) <= msec); 
}

void wait(unsigned int msec)
{
	QTime dieTime = QTime::currentTime().addMSecs(msec);
	while( QTime::currentTime() < dieTime )
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

//获取控制板的端口号配置信息
int getPortSetIni(PortSet_Ini_PTR info)
{
	QString filename = getFullIniFileName("portset.ini");
	QSettings settings(filename, QSettings::IniFormat);

	info->waterInNo = settings.value("Relay/waterInNo").toInt();
	info->bigNo = settings.value("Relay/bigNo").toInt();
	info->middle1No = settings.value("Relay/middle1No").toInt();
	info->middle2No = settings.value("Relay/middle2No").toInt();
	info->smallNo = settings.value("Relay/smallNo").toInt();
	info->waterOutNo = settings.value("Relay/waterOutNo").toInt();
	info->bigWaterInNo = settings.value("Relay/bigWaterInNo").toInt();
	info->bigWaterOutNo = settings.value("Relay/bigWaterOutNo").toInt();
	info->smallWaterInNo = settings.value("Relay/smallWaterInNo").toInt();
	info->smallWaterOutNo = settings.value("Relay/smallWaterOutNo").toInt();
	
	info->regSmallNo = settings.value("Regulate/regSmallNo").toInt();
	info->regMid1No = settings.value("Regulate/regMid1No").toInt();
	info->regMid2No = settings.value("Regulate/regMid2No").toInt();
	info->regBigNo = settings.value("Regulate/regBigNo").toInt();
	info->pumpNo = settings.value("Regulate/pumpNo").toInt();

	info->version = settings.value("CtrlBoard/version").toInt();
	return true;
}

//获取主机-从机设置信息
int getMasterSlaveIni(MasterSlave_Ini_PTR info)
{
	QString filename = getFullIniFileName("masterslaveset.ini");
	QSettings settings(filename, QSettings::IniFormat);

	info->netmode = settings.value("localhost/netmode").toInt();
	info->hostflag = settings.value("localhost/hostflag").toInt();
	strcpy_s(info->mastername, settings.value("master/hostname").toString().toAscii());
	strcpy_s(info->masterIP, settings.value("master/ip").toString().toAscii());
	strcpy_s(info->slave1name, settings.value("slave1/hostname").toString().toAscii());
	strcpy_s(info->slave1IP, settings.value("slave1/ip").toString().toAscii());
	strcpy_s(info->slave2name, settings.value("slave2/hostname").toString().toAscii());
	strcpy_s(info->slave2IP, settings.value("slave2/ip").toString().toAscii());
	strcpy_s(info->slave3name, settings.value("slave3/hostname").toString().toAscii());
	strcpy_s(info->slave3IP, settings.value("slave3/ip").toString().toAscii());
	strcpy_s(info->slave4name, settings.value("slave4/hostname").toString().toAscii());
	strcpy_s(info->slave4IP, settings.value("slave4/ip").toString().toAscii());

	return true;
}

QString getFullIniFileName(QString filename)
{
	QString adehome = QProcessEnvironment::systemEnvironment().value("ADEHOME");
	if (adehome.isEmpty())
	{
		qWarning()<<"Get $(ADEHOME) Failed! Please set up this system variable.";
		return "";
	}
	QString fullname;
#ifdef __unix
	fullname = adehome + "\/ini\/" + filename;
#else
	fullname = adehome + "\\ini\\" + filename;
#endif
	return fullname;
}

//获取所有采集代码对应的中文名称
QStringList getPickCodeStringList()
{
	QString filename = getFullIniFileName("pickcode.ini");
	QString str;
	QStringList strlist;
	QFile file(filename);
	if (file.open(QIODevice::ReadOnly))
	{
		QTextStream stream(&file);
		while (!stream.atEnd())
		{
			str = stream.readLine().simplified(); //去除首尾空格
			if (str.isEmpty() || str.startsWith("#"))
			{
				continue;
			}
			strlist += str.section("=", 1);
		}
	}
	return strlist;
}

float detA(float a00, float a01, float a10, float a11)
{
	return a00*a11 - a01*a10;
}

/************************************************************************/
/* 一般只需三组温度-阻值即可计算出此铂电阻的温度系数和0℃温度                 */
/************************************************************************/
plaParam_PTR getPlaParam(pla_T_R_PTR pla_p, int num)
{
	plaParam_PTR p_param;
	p_param = new plaParam_STR;
	float coe[2][3];//方程系数, coe[i,j]前两列对应于线性方程组的第i个方程第j个未知数的系数, 第三列是常数项
	coe[0][0] = detA(pla_p[0].resis, pla_p[0].tmp, pla_p[1].resis, pla_p[1].tmp);
	coe[0][1] = detA(pla_p[0].resis, pla_p[0].tmp*pla_p[0].tmp, pla_p[1].resis, pla_p[1].tmp*pla_p[1].tmp);
	coe[0][2] = pla_p[1].resis - pla_p[0].resis;
	coe[1][0] = detA(pla_p[0].resis, pla_p[0].tmp, pla_p[2].resis, pla_p[2].tmp);
	coe[1][1] = detA(pla_p[0].resis, pla_p[0].tmp*pla_p[0].tmp, pla_p[2].resis, pla_p[2].tmp*pla_p[2].tmp);
	coe[1][2] = pla_p[2].resis - pla_p[0].resis;

	float M;//克莱姆法则系数方阵的行列式的值
	float A;//第一未知数a的值
	float B;//第二未知数b的值
	M = detA(coe[0][0], coe[0][1], coe[1][0], coe[1][1]);
	A = detA(coe[0][2], coe[0][1], coe[1][2], coe[1][1]);
	B = detA(coe[0][0], coe[0][2], coe[1][0], coe[1][2]);
	p_param->a = A/M;
	p_param->b = B/M;
	p_param->r0 = pla_p[0].resis/(1 + p_param->a*pla_p[0].tmp + p_param->b*pla_p[0].tmp*pla_p[0].tmp);
	p_param->c;//参数c一般不做计算，只有0℃以下才用到
	return p_param;
}

float getPlaRt(float r0, float a, float b, float tmp)
{
	return r0*(1+a*tmp+b*tmp*tmp);
}

float getPlaTr(float r0, float a, float b, float resis)
{
	if (b==0.0 && a != 0.0)
	{
		return (resis/r0 - 1)/a;
	}
	else if (b==0.0 && a == 0.0)
	{
		return -1;
	}

// 	float ret = (qSqrt(a*a + 4*b*(resis/r0 - 1)) - a)/(2*b);
	float ret = qSqrt(resis/r0/b - 1/b + a*a/(4*b*b)) - (0.5*a/b);
	return ret;
}

float calcTemperByResis(float resis)
{
	QString filename = getFullIniFileName("stdplasensor.ini");
	QSettings settings(filename, QSettings::IniFormat);
	QString pt = settings.value("in_use/pt").toString();
	float rtp = settings.value(pt+"/in_rtp").toFloat();
	float a = settings.value(pt+"/in_a").toFloat();
	float b = settings.value(pt+"/in_b").toFloat();
	float temp = getPlaTr(rtp, a, b, resis);
	return temp;
}

float getDeltaTmpErr(float std_delta_t, float min_delta_t)
{
	return qAbs(0.5 + 3*min_delta_t/std_delta_t);
}

float getSingleTmpErr(float std_delta_t)
{
	return (0.3 + 0.005*qAbs(std_delta_t));
}

/************************************************************************/
/*根据JJG-2001 Page4, 表1（热能表热量的误差限）
/*grade, 表的等级, 1级, 2级, 3级等
/*delta_t_min, 表的最小温差
/*deta_t, 实际检测时的温差
/*dn_flow_rate, 表的常用(额定)流量, 计量单位与flow_rate相同
/*flow_rate, 实际检测时表的流量
/************************************************************************/
float calcMeterHeatErrLmt(int grade, float delta_t_min, float delta_t, float dn_flow_rate, float flow_rate)
{
	float ret;
	float coe_a, coe_b, coe_c;
	switch(grade)
	{
	case GRADE_ONE:
		coe_a = 2.0f;
		coe_b = 4.0f;
		coe_c = 0.01f;
		break;
	case GRADE_TWO:
		coe_a = 3.0f;
		coe_b = 4.0f;
		coe_c = 0.02f;
		break;
	case GRADE_THREE:
		coe_a = 4.0f;
		coe_b = 4.0f;
		coe_c = 0.05f;
		break;
	default:
		break;
	}
	ret = qAbs(coe_a + coe_b*(delta_t_min/delta_t) + coe_c*(dn_flow_rate/flow_rate));
	return ret;
}

/************************************************************************/
/*根据JJG-2001 Page4, 表2（流量传感器的误差限Eq）
/*grade, 表的等级, 1级, 2级, 3级等
/*dn_flow_rate, 表的常用(额定)流量, 计量单位与flow_rate相同
/*flow_rate, 实际检测时表的流量
/************************************************************************/
float calcMeterFlowErrLmt(int grade, float dn_flow_rate, float flow_rate)
{
	float ret;
	float coe_a, coe_b;
	switch(grade)
	{
	case GRADE_ONE:
		coe_a = 1.0f;
		coe_b = 0.01f;
		break;
	case GRADE_TWO:
		coe_a = 2.0f;
		coe_b = 0.02f;
		break;
	case GRADE_THREE:
		coe_a = 3.0f;
		coe_b = 0.05f;
		break;
	default:
		break;
	}
	ret = qAbs(coe_a + coe_b*(dn_flow_rate/flow_rate));
	if (ret > 5.0)
	{
		ret = 5.0;
	}

	return ret;
}

//根据热表规格计算其常用流量
float getNormalFlowByStandard(int standard)
{
	float normalFlow = 0.0;
	switch (standard)
	{
	case DN15:
		normalFlow = 1.5f;
		break;
	case DN20:
		normalFlow = 2.5f;
		break;
	case DN25:
		normalFlow = 3.5f;
		break;
	case DN32:
		normalFlow = 6.0f;
		break;
	case DN40:
		normalFlow = 10.0f;
		break;
	case DN50:
		normalFlow = 15.0f;
		break;
	default:
		break;
	}

	return normalFlow;
}

//根据热量表通讯返回的两字节数据，计算出对应的浮点型数值
float calcFloatValueOfCoe(QString coe)
{
	bool ok;
	float dec = coe.right(3).toInt(&ok, 16)/4096.0;
	float coeV = coe.left(1).toFloat() + dec; 

	return coeV;
}

//根据热量表通讯返回的两字节数据，计算出对应的误差值
float calcErrorValueOfCoe(QString coe)
{
	float coeV = calcFloatValueOfCoe(coe); 
	float errV = 100/coeV - 100;

	return errV;
}

/* 计算ModBus-RTU传输协议的CRC校验值
 * ref: http://www.ccontrolsys.com/w/How_to_Compute_the_Modbus_RTU_Message_CRC
 * 生成多项式为 x^16+x^15+x^2+x^0, 即系数字串为 (1 1000 0000 0000 0101),
 * 舍弃16次幂的系数后为 (1000 0000 0000 0101, 即0x8005),
 * 再反序得到 (1010 0000 0000 0001, 即0xA001)
 * buf, 指向消息头的指针;
 * len, 消息体的长度
 */
UINT16 calcModRtuCRC(uchar *buf, int len)
{
	UINT16 crc = 0xFFFF;

	for (int pos = 0; pos < len; pos++) {
		crc ^= (UINT16)buf[pos];          // XOR byte into least sig. byte of crc

		for (int i = 8; i > 0; i--) {    // Loop over each bit
			if ((crc & 0x0001) != 0) {      // If the LSB is set, that is the LSB is 1
				crc >>= 1;                  // Shift right, ignore LSB(LSB is the MSB before reverse)
				crc ^= POLY;				// and XOR 0xA001
			}
			else                            // Else LSB is not set, that is the LSB is 0
				crc >>= 1;                  // Just shift right, a XOR 0 = a, so not need to do XOR
		}
	}
	return crc;
}

UINT16 CRC16ModRTU_Table_Driven (const uchar *nData, UINT16 wLength)
{
	static const UINT16 wCRCTable[] = {
		0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
		0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
		0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
		0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
		0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
		0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
		0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
		0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
		0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
		0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
		0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
		0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
		0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
		0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
		0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
		0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
		0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
		0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
		0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
		0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
		0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
		0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
		0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
		0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
		0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
		0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
		0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
		0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
		0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
		0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
		0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
		0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040 
	};

		uchar nTemp;
		UINT16 wCRCWord = 0xFFFF;

		while (wLength--)
		{
			nTemp = *nData++ ^ wCRCWord;
			wCRCWord >>= BYTE_LENGTH;
			wCRCWord  ^= wCRCTable[nTemp];
		}
		return wCRCWord;
}

/* 将CRC计算结果转换为QByteArray
 * 返回值QByteArray sendbuf;
 * sendbuf.at(0) 是低位;  sendbuf.at(1) 是高位
 * crc, 计算得到的校验值, 高位在前, 低位在后
 */
QByteArray getCRCArray(UINT16 crc)
{
	QByteArray sendbuf;
	sendbuf.append((char)crc);//低位
	sendbuf.append((char)(crc>>BYTE_LENGTH));//高位
	return sendbuf;
}

int get9150ARouteI(int i, QByteArray valueArray)
{
	if(valueArray.length() < EDA9150A_ROUTE_BYTES)
		return -1;

	if ( (EDA9150A_ROUTE_BYTES*i) > valueArray.length())//i不能超过被读取的通道数量
	{
		return -1;
	}

	QByteArray data;
	for (int k=0;k<EDA9150A_ROUTE_BYTES;k++)
		data.append(valueArray.at(EDA9150A_ROUTE_BYTES*i+k));

	int value = 0;	
	for (int k=0;k<EDA9150A_ROUTE_BYTES;k++)
	{
		value |= ( ((uchar)data.at(k)) << ((EDA9150A_ROUTE_BYTES-1-k)*BYTE_LENGTH) );
	}
	return value;
}

int get9017RouteI(int i, QByteArray valueArray)
{
	if(valueArray.length() < EDA9017_ROUTE_BYTES)
		return -1;

	if ( (EDA9017_ROUTE_BYTES*i) > valueArray.length())//i不能超过被读取的通道数量
	{
		return -1;
	}

	QByteArray data;
	for (int k=0;k<EDA9017_ROUTE_BYTES;k++)
		data.append(valueArray.at(EDA9017_ROUTE_BYTES*i+k));

	int value = 0;	
	for (int k=0;k<EDA9017_ROUTE_BYTES;k++)
	{
		value |= ( ((uchar)data.at(k)) << ((EDA9017_ROUTE_BYTES-1-k)*BYTE_LENGTH) );
	}
	return value;
}

float getInstStdValue(float elecValue, float upperValue)
{
	if (ELEC_ZERO<=elecValue && elecValue <= ELEC_UPPER)
	{
		float deltaStd = ELEC_UPPER - ELEC_ZERO;
		float deltaCur = elecValue - ELEC_ZERO;
		return (deltaCur/deltaStd)*upperValue;
	}

	return 0.0f;//如果超出正常电流值的范围, 返回异常流速
}


/*
** 计算水表的标准误差
*/
float getWaterMeterStdError(float Q2, int grade, float temper, float flow)
{
	float stdErr = 0.02;
	switch (grade)
	{
	case 1: //一级水表
		if (temper>=0.1 && temper<=30)
		{
			if (flow >= Q2) //高区
			{
				stdErr = 0.01;
			}
			else //低区
			{
				stdErr = 0.03;
			}
		}
		else
		{
			if (flow >= Q2) //高区
			{
				stdErr = 0.02;
			}
			else //低区
			{
				stdErr = 0.03;
			}
		}
		break;
	case 2: //二级水表
		if (temper>=0.1 && temper<=30)
		{
			if (flow >= Q2) //高区
			{
				stdErr = 0.02;
			}
			else //低区
			{
				stdErr = 0.05;
			}
		}
		else
		{
			if (flow >= Q2) //高区
			{
				stdErr = 0.03;
			}
			else //低区
			{
				stdErr = 0.05;
			}
		}
		break;
	default:
		break;
	}

	return stdErr*100;
}

/**********************************************************
类名：CAlgorithm
功能：检定算法类
***********************************************************/
CAlgorithm::CAlgorithm()
{

}

CAlgorithm::~CAlgorithm()
{

}

float CAlgorithm::calc(float a, float b)
{
	float sum = a + b;
	qDebug("%.2f + %.2f = %.2f \n", a, b, sum);
	return sum;
}

/*********************************************************************************************
* 按表位号计算其温度(距离均布法)                                      
* inlet: 进水口温度值                                                              
* outlet: 出水口温度值																						   
* num: 表位号(从1开始至最大检表数量), 以此计算此热表离进口的距离        
/********************************************************************************************/
float CAlgorithm::getMeterTempByPos(float inlet, float outlet, int num)
{
	//获取被检表的规格
	QSettings ParaSet(getFullIniFileName("verifyparaset.ini"), QSettings::IniFormat);//参数配置文件
	int standard = ParaSet.value("head/standard").toInt();//被检表规格
    int totalCount = getMaxMeterByIdx(standard); //该规格热表对应的最大检表数量
	float delta = (inlet - outlet)/(totalCount + 2); //双管路设计，假设入口前、拐弯处、出口后各有一块热量表
	float temper = inlet - (num + (int)(2*(num-1)/totalCount))*delta;
	return temper;
}

/************************************************************************
* 根据水温-密度表(JGG 225-2010 热量表检定规程)
* 进行多项式拟合(MATLAB, 9次方)
* float temp: 温度值 ( 1 ≤ temp ≤ 150 , 单位千克/升, kg/L)
* f(x) = p1*x^9 + p2*x^8 + p3*x^7 + p4*x^6 + 
* p5*x^5 + p6*x^4 + p7*x^3 + p8*x^2 + p9*x + p10               
/************************************************************************/
double CAlgorithm::getDensityByFit(float temp)
{
	//p1~p10为多项式系数
	double const p1 =  -3.562e-18;
	double const p2 =   2.303e-15;
	double const p3 =  -5.989e-13;
	double const p4 =   7.617e-11;
	double const p5 =  -3.716e-09;
	double const p6 =  -2.719e-07;
	double const p7 =   6.455e-05;
	double const p8 =   -0.008346;
	double const p9 =     0.05982;
	double const p10 =  1000.12;
	//exp2~exp9为参数的幂值
	double exp2 = temp * temp;
	double exp3 = exp2 * temp;
	double exp4 = exp3 * temp;
	double exp5 = exp4 * temp;
	double exp6 = exp5 * temp;
	double exp7 = exp6 * temp;
	double exp8 = exp7 * temp;
	double exp9 = exp8 * temp;

	return  (p1*exp9 + p2*exp8 + p3*exp7 + p4*exp6 + p5*exp5 + p6 * exp4 + p7*exp3 +  + p8*exp2 +  + p9*temp + p10) / 1000.0;
}

/*****************************************************************************
* 查表求对应水温的密度值(单位千克/升, kg/L)
* 设当前水温为temp
* temp的整数部分为 low, 
* low温度值查表可得density[low - 1](density的索引从0开始)
* (若temp的小数部分不为零, 那么认为在温度low-1至low之间
* 密度值是线性变化的)
/****************************************************************************/
double CAlgorithm::getDensityByQuery(float temp)
{
	if (temp<1 || temp>149)
	{
		return -1;
	}
	int low = getInt(temp);

	return (density[low -1] +  getDecimal(temp) * (density[low] - density[low - 1])) / 1000.0;
}

/*
** 查表求对应水温的焓值(单位 kJ/kg)
*/
double CAlgorithm::getEnthalpyByQuery(float temp)
{
	int low = getInt(temp);
	float ret = enthalpy[low -1] +  getDecimal(temp) * (enthalpy[low] - enthalpy[low - 1]);
	return ret;
}

/*
** 根据欧标EN1434《热能表》计算水的K系数
** 默认K系数单位MJ/m3℃
*/
double CAlgorithm::calcKCoeOfWater(float inTemper, float outTemper, int installPos, float pressure)
{
	float kCoe = 0.0;
	float vIn = 0.0, vOut = 0.0;
	float tao = 0.0;
	float hIn = getEnthalpyByQuery(inTemper);
	float hOut = getEnthalpyByQuery(outTemper);
 	float pai = pressure/16.53;
	float kIn = inTemper + 273.13;
	float kOut = outTemper + 273.13;
	float R = 461.526;
	float lanmuda = 0.0;
	int i = 0;
	float tmp;

	if (installPos==INSTALLPOS_IN) //安装位置 入口
	{
		tao = 1386/kIn;
		for (i=0; i<34; i++)
		{
			tmp = -n[i]*I[i]*pow(7.1-pai, I[i]-1)*pow(tao-1.222, J[i]);
			lanmuda += tmp;
		}
		vIn = pai*lanmuda*R*kIn/pressure/1000;
		kCoe = (hIn - hOut)/(inTemper - outTemper)/vIn;
	}
	else if (installPos==INSTALLPOS_OUT)	//安装位置 出口
	{
		tao = 1386/kOut;
		for (i=0; i<34; i++)
		{
			tmp = -n[i]*I[i]*pow(7.1-pai, I[i]-1)*pow(tao-1.222, J[i]);
			lanmuda += tmp;
		}
		vOut = pai*lanmuda*R*kOut/pressure/1000;
		kCoe = (hIn - hOut)/(inTemper - outTemper)/vOut;
	}

	return kCoe;
}

/*
** 根据欧标EN1434《热能表》Part-1 计算水的比焓值
** 单位KJ/kg
** temp 温度, ℃
** pressure 压强, MPa
*/
double CAlgorithm::calcEnthalpyOfWater(float temp, float pressure)
{
	float T = temp + 273.15;//开尔文温度标
	float tao = 1386/T;
	float pai = pressure/16.53;
	float gamaTao = getGamaTao(pai, tao);

	float H = tao*gamaTao*ENTHALPY_R*T;

	return H/1000.0;
}

double CAlgorithm::getGamaPai(float pai, float tao)
{
	float gama = 0.0;
	for (int i=0; i<34; i++)
		gama += (-1)*n[i]*I[i]*pow(7.1-pai, I[i]-1)*pow(tao-1.222, J[i]);

	return gama;
}

double CAlgorithm::getGamaTao(float pai, float tao)
{
	float gama = 0.0;
	for (int i=0; i<34; i++)
		gama += n[i]*pow(7.1-pai, I[i])*J[i]*pow(tao - 1.222, J[i] - 1);

	return gama;
}

/*
** 根据欧标EN1434《热能表》Part-1 计算水的比焓值
** 单位(kWh/MJ)
** inTemper 进口温度, ℃
** outTemper 出口温度, ℃
** volum 体积, L
** installPos 安装位置, 进口/出口
** unit 使用的热值单位, kWh/MJ
** pressure 压强, MPa
*/
double CAlgorithm::calcEnergyByEnthalpy(float inTemper, float outTemper, float volum,  int installPos, int unit, float pressure)
{
	float inEnthalpy, outEnthalpy;
	float density;
	float mass;
	float energy;

	inEnthalpy = calcEnthalpyOfWater(inTemper, pressure);//KJ/kg
	outEnthalpy = calcEnthalpyOfWater(outTemper, pressure);//KJ/kg
	if (installPos == INSTALLPOS_IN)
	{
		density = getDensityByQuery(inTemper);//kg/L
	}
	else if (installPos == INSTALLPOS_OUT)
	{
		density = getDensityByQuery(outTemper);//kg/L
	}
	
	mass = density*volum;//kg
	energy = mass*(inEnthalpy-outEnthalpy);//KJ
	if (unit == UNIT_KWH)
	{
		energy /= 3600.0;
	}
	else if (unit == UNIT_MJ)
	{
		energy /= 1000.0;
	}
	return energy;
}

/************************************************************************
* 计算浮点数的整数部分           
/************************************************************************/
int CAlgorithm::getInt(float p)
{
	if (p > 0)
	{
		return int(p);
	}
	else if (p == 0)
	{
		return 0;
	}
	else
	{
		return (int(p) - 1);
	}
}
/************************************************************************
* 计算浮点数的小数部分           
/************************************************************************/
float CAlgorithm::getDecimal(float p)
{
	return (p - getInt(p));
}

/************************************************************************
* 按表位号获取对应表位的标准体积流量 (单位升, L)                       
* mass:  质量(单位千克, kg，天平质量或标准表折算后的质量),未修正
* inlet: 进水口温度
* outlet: 出水口温度
* num: 表位号(从1开始至最大检表数量)
* method：检定方法 （0：质量法；1：标准表法）
* balCap:天平容量，对应不同的系数（0：150kg天平，系数0.9971； 1：600kg天平，系数0.9939
************************************************************************/
double CAlgorithm::getStdVolByPos(float mass, float inlet, float outlet, int num, int method, int balCap)
{	
	float temp = getMeterTempByPos(inlet, outlet, num);//获取温度
#ifdef FIT
	float den = getDensityByFit(temp);//获取密度
#else
	float den = getDensityByQuery(temp);//获取密度
#endif

	float stdVol = 0.0;
	if (method == WEIGHT_METHOD)
	{
		if (balCap == BALANCE_CAP150)
		{
			stdVol = mass*0.9971 / den; //标准体积(质量法需要考虑天平进水管的浮力修正：150kg天平修正系数0.9971)
		}
		else //BALANCE_CAP600
		{
			stdVol = mass*0.9939 / den; //标准体积(质量法需要考虑天平进水管的浮力修正：600kg天平修正系数0.9939）
		}
	}
	else //STANDARD_METHOD
	{
		stdVol = mass / den;
	}
	return stdVol;
}

/*
** 根据焓差计算标准热量（JJG-2001)
** 单位(kWh或MJ)
** inTemper 进口标准温度, ℃
** outTemper 出口标准温度, ℃
** mass 质量, kg
** unit 使用的热值单位, 0:MJ ; 1:kWh
** method 检定方法，0:质量法；1:标准表法
** balCap:天平容量，对应不同的系数（0：150kg天平，系数0.9971； 1：600kg天平，系数0.9939
** pressure:气压
*/
double CAlgorithm::calcStdEnergyByEnthalpy(float inTemper, float outTemper, float mass, int unit, int method, int balCap, float pressure)
{
	float inEnthalpy, outEnthalpy, energy;

// 	inEnthalpy = calcEnthalpyOfWater(inTemper, pressure);//KJ/kg
// 	outEnthalpy = calcEnthalpyOfWater(outTemper, pressure);//KJ/kg
	inEnthalpy = getEnthalpyByQuery(inTemper);//KJ/kg
	outEnthalpy = getEnthalpyByQuery(outTemper);//KJ/kg

	float massA = 0.0;
	if (method == WEIGHT_METHOD)
	{
		if (balCap == BALANCE_CAP150)
		{
			massA = mass * 0.9971;
		}
		else //BALANCE_CAP600
		{
			massA = mass * 0.9939;
		}
	}
	else //STANDARD_METHOD
	{
		massA = mass;
	}
	energy = massA*(inEnthalpy-outEnthalpy);//KJ
	if (unit == UNIT_KWH)
	{
		energy /= 3600.0;
	}
	else if (unit == UNIT_MJ)
	{
		energy /= 1000.0;
	}
	return energy;
}

