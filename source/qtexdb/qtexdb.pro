######################################################################
# Automatically generated by qmake (2.01a) ?? ?? 11 22:37:20 2014
######################################################################

TEMPLATE = lib
CONFIG += dll console debug
TARGET = qtexdb
DEFINES	+= QTEXDB_DLL 

DEPENDPATH += .
INCLUDEPATH += ./	\
               $$(RUNHOME_INC)/include

QMAKE_LIBDIR +=  ./             \
        	  		 $(RUNHOME)/lib \
	          		 $(RUNHOME)/bin \


# Input
HEADERS += $$(RUNHOME_INC)/include/qtexdb.h
SOURCES += qtexdb.cpp


win32{
DEFINES += WIN32 _AFXDLL
DEFINES -= _USRDLL
DESTDIR = $(RUNHOME)\tmp\qtexdb\obj
}

win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $(RUNHOME)\lib \
                  & copy $${MY_DEST_DLL} $(RUNHOME)\dll
}
