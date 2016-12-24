#-------------------------------------------------
#
# Project created by QtCreator 2016-12-24T06:32:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QChristmasTree
TEMPLATE = app

CONFIG += mobility
MOBILITY = 

unix:!android {

    INCLUDEPATH += include/


    SOURCES +=  src/main.cpp\
                src/mainwindow.cpp

    HEADERS  += include/mainwindow.h
    FORMS    += forms/mainwindow.ui

    #RESOURCES += resources/icons.qrc

    CONFIG(release, debug|release): LIBS += -L$$PWD/C:/Cygwin64/opt/LibraryBuilds/tjlutils/Debug/debug/release/ -ltjlutils
    LIBS += -L$$PWD/C:/Cygwin64/opt/LibraryBuilds/tjlutils/Debug/ -ltjlutils

    INCLUDEPATH += $$PWD/C:/Cygwin64/opt/LibraryBuilds/tjlutils/Debug/debug
    DEPENDPATH += $$PWD/C:/Cygwin64/opt/LibraryBuilds/tjlutils/Debug/debug
}

android {
    LIB_SOURCE_BASE = /opt/GitHub/tjlutils

    INCLUDEPATH += include/ \
                   $${LIB_SOURCE_BASE}/generalutilities/include/ \
                   $${LIB_SOURCE_BASE}/udpclient/include/ \
                   $${LIB_SOURCE_BASE}/tstream/include/


    SOURCES +=  src/main.cpp\
                src/mainwindow.cpp \
                $${LIB_SOURCE_BASE}/generalutilities/src/generalutilities.cpp \
                $${LIB_SOURCE_BASE}/udpclient/src/udpclient.cpp \
                $${LIB_SOURCE_BASE}/tstream/src/tstream.cpp

    HEADERS  += include/mainwindow.h\
                $${LIB_SOURCE_BASE}/generalutilities/include/generalutilities.h \
                $${LIB_SOURCE_BASE}/udpclient/include/udpclient.h \
                $${LIB_SOURCE_BASE}/tstream/include/tstream.h

    FORMS    += forms/mainwindow.ui

    #RESOURCES += resources/icons.qrc

}

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

HEADERS += \
    include/custompushbutton.h

SOURCES +=

