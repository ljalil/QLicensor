#-------------------------------------------------
#
# Project created by QtCreator 2015-01-30T10:56:13
#
#-------------------------------------------------

QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QLicensor
TEMPLATE = app


SOURCES += Core/main.cpp\
        QLicensorWindow/qlicensorwindow.cpp \
        Core/licenseinformation.cpp \
    Core/licenseapplier.cpp \
    Dialogs/LicenseViewer/licenseviewer.cpp \
    Dialogs/AboutDialog/aboutdialog.cpp

HEADERS  += QLicensorWindow/qlicensorwindow.h \
    Core/licenseinformation.h \
    Core/licenseapplier.h \
    Core/licensemetadata.h \
    Dialogs/LicenseViewer/licenseviewer.h \
    Dialogs/AboutDialog/aboutdialog.h

FORMS    += QLicensorWindow/qlicensorwindow.ui \
    Dialogs/LicenseViewer/licenseviewer.ui \
    Dialogs/AboutDialog/aboutdialog.ui

RESOURCES += \
    resources.qrc
