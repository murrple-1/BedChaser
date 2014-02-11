#-------------------------------------------------
#
# Project created by QtCreator 2011-01-20T13:31:13
#
#-------------------------------------------------

QT       += core gui \
            sql

TARGET = test
TEMPLATE = app

DEFINES += QS_LOG_LINE_NUMBERS

LIBS += -L../deplib/KDChart/lib -lkdchart

DEPENDPATH += ../deplib/QsLog \
    ../deplib/TinyXML \

INCLUDEPATH += ../deplib/QsLog \
    ../deplib/TinyXML \
    ../deplib/KDChart/include

SOURCES += src/gui/waitinglistdialog.cpp \
    src/gui/searchwindow.cpp \
    src/gui/patientreportdialog.cpp \
    src/gui/mapframe.cpp \
    src/gui/mainwindow.cpp \
    src/gui/facilityreportdialog.cpp \
    src/gui/addpatientdialog.cpp \
    src/gui/addfacilitydialog.cpp \
    src/core/object.cpp \
    src/core/exception.cpp \
    src/utils/stringbuilder.cpp \
    src/main.cpp \
    src/core/location.cpp \
    src/core/user.cpp \
    src/core/region.cpp \
    src/core/patient.cpp \
    src/core/map.cpp \
    src/core/memento.cpp \
    src/core/datamanager.cpp \
    src/core/eventmanager.cpp \
    src/core/database.cpp \
    src/core/subscriber.cpp \
    src/core/event.cpp \
    src/logging/loggingthread.cpp \
    src/gui/graphicsthread.cpp \
    src/gui/loginframe.cpp \
    src/gui/adduserdialog.cpp \
    src/gui/editfacilitydialog.cpp \
    src/gui/editpatientdialog.cpp \
    src/gui/edituserdialog.cpp \
    src/gui/changepassworddialog.cpp \
    src/core/locationproxy.cpp \
    src/core/patientproxy.cpp \
    src/core/regionproxy.cpp \
    src/core/patientobject.cpp \
    src/core/locationobject.cpp \
    src/core/regionobject.cpp \
    src/gui/regionframe.cpp \
    src/gui/patientlistdialog.cpp \
    tinystr.cpp \
    tinyxml.cpp \
    tinyxmlerror.cpp \
    tinyxmlparser.cpp \
    QsLogDest.cpp \
    QsLog.cpp \
    QsDebugOutput.cpp \
    src/gui/facilityreportdisplay.cpp

HEADERS  += src/gui/waitinglistdialog.h \
    src/gui/searchwindow.h \
    src/gui/patientreportdialog.h \
    src/gui/mapframe.h \
    src/gui/mainwindow.h \
    src/gui/facilityreportdialog.h \
    src/gui/addpatientdialog.h \
    src/gui/addfacilitydialog.h \
    src/core/object.h \
    src/core/exception.h \
    src/core/config.h \
    src/utils/stringbuilder.h \
    src/core/location.h \
    src/core/user.h \
    src/core/region.h \
    src/core/patient.h \
    src/core/map.h \
    src/core/memento.h \
    src/core/datamanager.h \
    src/core/eventmanager.h \
    src/core/database.h \
    src/core/subscriber.h \
    src/core/event.h \
    src/logging/loggingthread.h \
    src/gui/graphicsthread.h \
    src/gui/loginframe.h \
    src/gui/adduserdialog.h \
    src/gui/editfacilitydialog.h \
    src/gui/editpatientdialog.h \
    src/gui/edituserdialog.h \
    src/gui/changepassworddialog.h \
    src/core/locationproxy.h \
    src/core/patientproxy.h \
    src/core/regionproxy.h \
    src/core/patientobject.h \
    src/core/locationobject.h \
    src/core/regionobject.h \
    src/gui/regionframe.h \
    src/utils/hasher.h \
    src/gui/patientlistdialog.h \
    tinystr.h \
    tinyxml.h \
    QsLogDest.h \
    QsLog.h \
    QsDebugOutput.h \
    src/gui/facilityreportdisplay.h

FORMS    += src/gui/waitinglistdialog.ui \
    src/gui/searchwindow.ui \
    src/gui/patientreportdialog.ui \
    src/gui/mapframe.ui \
    src/gui/mainwindow.ui \
    src/gui/facilityreportdialog.ui \
    src/gui/addpatientdialog.ui \
    src/gui/addfacilitydialog.ui \
    src/gui/loginframe.ui \
    src/gui/adduserdialog.ui \
    src/gui/editfacilitydialog.ui \
    src/gui/editpatientdialog.ui \
    src/gui/edituserdialog.ui \
    src/gui/changepassworddialog.ui \
    src/gui/facilityreportdisplay.ui \
    src/gui/regionframe.ui \
    src/gui/patientlistdialog.ui \
