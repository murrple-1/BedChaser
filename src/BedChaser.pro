QT += widgets sql

TARGET = BedChaser
TEMPLATE = app


SOURCES += \
    addfacilitydialog.cpp \
    addpatientdialog.cpp \
    adduserdialog.cpp \
    changepassworddialog.cpp \
    datamanager.cpp \
    editfacilitydialog.cpp \
    editpatientdialog.cpp \
    edituserdialog.cpp \
    exception.cpp \
    facilityreportdialog.cpp \
    facilityreportdisplay.cpp \
    loginframe.cpp \
    mainwindow.cpp \
    map.cpp \
    mapframe.cpp \
    patientlistdialog.cpp \
    patientreportdialog.cpp \
    regionframe.cpp \
    searchwindow.cpp \
    user.cpp \
    waitinglistdialog.cpp \
    main.cpp \
    region.cpp \
    patient.cpp \
    location.cpp

HEADERS  += \
    addfacilitydialog.h \
    addpatientdialog.h \
    adduserdialog.h \
    changepassworddialog.h \
    datamanager.h \
    editfacilitydialog.h \
    editpatientdialog.h \
    edituserdialog.h \
    exception.h \
    facilityreportdialog.h \
    facilityreportdisplay.h \
    loginframe.h \
    mainwindow.h \
    map.h \
    mapframe.h \
    patientlistdialog.h \
    patientreportdialog.h \
    regionframe.h \
    searchwindow.h \
    user.h \
    waitinglistdialog.h \
    location.h \
    patient.h \
    region.h

FORMS    += \
    addfacilitydialog.ui \
    addpatientdialog.ui \
    adduserdialog.ui \
    changepassworddialog.ui \
    editfacilitydialog.ui \
    editpatientdialog.ui \
    edituserdialog.ui \
    facilityreportdialog.ui \
    facilityreportdisplay.ui \
    loginframe.ui \
    mainwindow.ui \
    mapframe.ui \
    patientlistdialog.ui \
    patientreportdialog.ui \
    regionframe.ui \
    searchwindow.ui \
    waitinglistdialog.ui

QMAKE_CXXFLAGS += -Werror