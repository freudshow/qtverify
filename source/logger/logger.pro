######################################################################
# Automatically generated by qmake (2.01a) ?? ?? 11 22:37:20 2014
######################################################################
TEMPLATE = lib
CONFIG += dll debug
DEFINES	+= LOGGER_DLL
TARGET = logger
DEPENDPATH += .
INCLUDEPATH  	+=    ./      \
									 include \ 
									 $$(ADEHOME_INC)/include \

QMAKE_LIBDIR +=  ./             \
        	  		 $(ADEHOME)/lib \
	          		 $(ADEHOME)/bin \


# Input
HEADERS += $$(ADEHOME_INC)/include/logger.h
SOURCES += logger.cpp

win32{
DEFINES += WIN32 _AFXDLL
DEFINES -= _USRDLL
DESTDIR = $(ADEHOME)\tmp\logger\obj
}

win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $(ADEHOME)\lib \
                        & copy $${MY_DEST_DLL} $(ADEHOME)\dll
}
