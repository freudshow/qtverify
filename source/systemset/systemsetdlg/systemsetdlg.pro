DEFINES	+= SYSTEMSETDLG_DLL
TEMPLATE	= lib
QT         += xml sql
TARGET    = systemsetdlg
CONFIG += qt dll debug

QMAKE_LIBDIR +=  ./           \
        	     $(ADEHOME)/lib \
	             $(ADEHOME)/bin

LIBS += -lqtexdb -lalgorithm -lcomobject -lreadstdmeter -lreport -lqwtd

DESTDIR = $(ADEHOME)\tmp\systemset\systemsetdlg\obj
#MOC_DIR = $(ADEHOME)/tmp/systemset/systemsetdlg/moc
OBJECTS_DIR = $(ADEHOME)/tmp/systemset/systemsetdlg/obj
UI_DIR = $(ADEHOME_INC)/include

INCLUDEPATH = ./         \
              include    \ 
              $$(ADEHOME_INC)/include	\
			  $$(ADEHOME_INC)/include/qextserial

HEADERS += $$(ADEHOME_INC)/include/systemsetdlg_global.h   \
           $$(ADEHOME_INC)/include/setcomdlg.h   \
           $$(ADEHOME_INC)/include/setportfrm.h  \
           $$(ADEHOME_INC)/include/readcomconfig.h \
           $$(ADEHOME_INC)/include/stdmtrparaset.h \
           $$(ADEHOME_INC)/include/stdmtrcoecorrect.h \
           $$(ADEHOME_INC)/include/parasetdlg.h \
           $$(ADEHOME_INC)/include/parasetdlg100.h \
           $$(ADEHOME_INC)/include/stdplasensor.h \
           $$(ADEHOME_INC)/include/chkplasensor.h \
		       $$(ADEHOME_INC)/include/stdcorrectpra.h

SOURCES += source/setcomdlg.cpp \
           source/setportfrm.cpp \
           source/readcomconfig.cpp \
           source/stdmtrparaset.cpp \
           source/stdmtrcoecorrect.cpp \
           source/parasetdlg.cpp \
           source/parasetdlg100.cpp \
           source/stdplasensor.cpp \
           source/chkplasensor.cpp \
		       source/stdcorrectpra.cpp

RESOURCES += systemsetdlg.qrc			 

FORMS	+= ui/setcomdlg.ui  \
         ui/setportfrm.ui \
         ui/stdmtrparaset.ui \
         ui/stdmtrcoecorrect.ui \
         ui/parasetdlg.ui \
         ui/parasetdlg100.ui \
         ui/stdplasensor.ui \
         ui/chkplasensor.ui \
		     ui/stdcorrectpra.ui

win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(ADEHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(ADEHOME)\dll \
                  & copy .\language\systemsetdlg_zh.qm $(ADEHOME)\uif\i18n\zh	\
                  & copy .\language\systemsetdlg_en.qm $(ADEHOME)\uif\i18n\en
}

TRANSLATIONS =  \
		language/systemsetdlg_zh.ts language/systemsetdlg_en.ts