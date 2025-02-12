/***********************************************
**  文件名:     main.cpp
**  功能:       扫码写表号-主程序
**  操作系统:   基于Trolltech Qt4.8.5的跨平台系统
**  生成时间:   2015/9/8
**  专业组:     德鲁计量软件组
**  程序设计者: YS
**  程序员:     YS
**  版本历史:   2015/09 第一版
**  内容包含:
**  说明:
**  更新记录:
***********************************************/

#include <QtGui/QApplication>
#include <QtCore/QTranslator>
#include <QtCore/QThread>
#include <QtCore/QDebug>
#include <QtCore/QTextCodec>
#include <QtCore/QProcess>

#include "scancodedlg.h"
#include "qtexdb.h"

int main( int argc, char ** argv )
{
	QApplication app( argc, argv );
	QString lang = "zh";//默认显示中文
	if (argc == 2)
	{
		lang = QString::fromAscii(argv[1]);
	}

	QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
	QTextCodec::setCodecForCStrings( QTextCodec::codecForName("GB2312"));

	QTranslator translator(0);
	QString adehome = QProcessEnvironment::systemEnvironment().value("ADEHOME");
	if (!adehome.isEmpty()) 
	{
		QString filename = adehome + "\\uif\\i18n\\" + lang + "\\scancodedlg_" + lang + ".qm";
		bool loadok = translator.load(filename, "");
		if (!loadok)
		{
			qDebug()<<"load translator file \""<<filename<<"\" failed!";
		}
		app.installTranslator(&translator);
	}
	qDebug()<<"scancode main thread:"<<QThread::currentThreadId();
	startdb();
	
	ScanCodeDlg w;
	w.show();
	app.exec();

	closedb();
	return 0;
}