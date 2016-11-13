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
    mapframe.cpp \
    patientreportdialog.cpp \
    regionframe.cpp \
    searchwindow.cpp \
    user.cpp \
    waitinglistdialog.cpp \
    main.cpp \
    region.cpp \
    patient.cpp \
    facility.cpp \
    waitinglistentry.cpp \
    passwordhasher.cpp

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
    mapframe.h \
    patientreportdialog.h \
    regionframe.h \
    searchwindow.h \
    user.h \
    waitinglistdialog.h \
    patient.h \
    region.h \
    facility.h \
    waitinglistentry.h \
    passwordhasher.h

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
    patientreportdialog.ui \
    regionframe.ui \
    searchwindow.ui \
    waitinglistdialog.ui \
    mapframe.ui

# recommended: download the most recent precompiled library here: https://download.libsodium.org/libsodium/releases/
LIBSODIUM32_DIR = $$(LIBSODIUM32_DIR)
isEmpty(LIBSODIUM32_DIR): error("'LIBSODIUM32_DIR' environment variable not set")

INCLUDEPATH += \
    $${LIBSODIUM32_DIR}/include

LIBS += \
    -L$${LIBSODIUM32_DIR}/lib -lsodium

libFiles_sodium.path = $$OUT_PWD
libFiles_sodium.files = \
    $${LIBSODIUM32_DIR}/bin/libsodium-18.dll

INSTALLS += \
    libFiles_sodium

CONFIG(debug, debug|release) {
imageFiles.path = $$OUT_PWD/images
imageFiles.files = $$PWD/images/*

sqlFiles.path = $$OUT_PWD
sqlFiles.files = \
    $$PWD/sqlschema.sql \
    $$PWD/sqlcreate.sql

INSTALLS += \
    imageFiles \
    sqlFiles
}


CONFIG(release, debug|release) {
imageFiles.path = $$OUT_PWD/images
imageFiles.files = $$PWD/images/*

sqlFiles.path = $$OUT_PWD
sqlFiles.files = \
    $$PWD/sqlschema.sql \
    $$PWD/sqlcreate.sql

INSTALLS += \
    imageFiles \
    sqlFiles
}

QMAKE_CXXFLAGS += -Werror
