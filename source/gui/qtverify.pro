######################################################################
# Automatically generated by qmake (2.01a) ?? ?? 11 22:32:44 2014
######################################################################

TEMPLATE = app
CONFIG  += qt warn_on debug console
TARGET = qtverify
RC_FILE = qtverify.rc

QT += sql

DEPENDPATH += . GeneratedFiles							 

QMAKE_LIBDIR = 	$(RUNHOME)/lib \
                $(RUNHOME)/bin \

								
LIBS += -lalgorithm -lcomsetdlg -lqualitydlg -lqaxserver -lqaxcontainerd -lmasterslaveset -llogindialog \
				-lweightmethod -lqtexdb

# Input
HEADERS += include/mainform.h	\
					 include/dbmysql.h	\
					 include/queryresult.h
					 
FORMS += 	ui/mainform.ui	\
				 	ui/dbmysql.ui		\
				 	ui/queryresult.ui	\
				 
SOURCES += source/main.cpp	\
					 source/mainform.cpp	\
					 source/dbmysql.cpp		\
					 source/queryresult.cpp
					 
RESOURCES += qtverify.qrc

win32{
DEFINES += WIN32 _AFXDLL
DEFINES -= _USRDLL
DESTDIR = $(RUNHOME)\tmp\qtverify\obj
}

MOC_DIR = $(RUNHOME)/tmp/qtverify/moc
OBJECTS_DIR = $(RUNHOME)/tmp/qtverify/obj
UI_DIR = $(RUNHOME)/tmp/qtverify/ui


INCLUDEPATH += 	./include	\
								$${UI_DIR}	\
								$$(RUNHOME_INC)/include		\
								$$(RUNHOME_INC)/include/qextserial \
								F:\mysoft\trunk\plugindemo\GameSystem

TRANSLATIONS += ./language/qtverify_en.ts ./language/qtverify_zh.ts

win32{
	MY_DEST_EXE_VAR = $${DESTDIR} $${TARGET}.exe
	MY_DEST_EXE = $$join( MY_DEST_EXE_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_EXE} $(RUNHOME)\bin	\
										& copy .\language\qtverify_zh.qm $(RUNHOME)\uif\i18n
}
