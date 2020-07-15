QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

TARGET = mainwindow
TEMPLATE = app


SOURCES += main.cpp\
    Model/model.cpp \
    Notification/notification.cpp \
    Parameters/parameters.cpp \
    ViewModel/viewmodel.cpp \
    app/app.cpp \
    commands/command.cpp \
    commands/open_file_command.cpp \
    commands/rotate_command.cpp \
    commands/save_file_command.cpp \
    commands/show_pic_command.cpp \
    commands/flip_command.cpp  \
    view/frame.cpp \
    view/mainwindow.cpp \
    view/toolbar.cpp \
    view/photoinfo.cpp \
    view/about.cpp \
    view/mirroreditem.cpp \
    view/mirrorview.cpp \
    view/slideshow.cpp

HEADERS  += view/mainwindow.h \
    Model/model.h \
    Notification/notification.h \
    Parameters/parameters.h \
    ViewModel/viewmodel.h \
    app/app.h \
    commands/command.h \
    commands/open_file_command.h \
    commands/rotate_command.h \
    commands/save_file_command.h \
    commands/show_pic_command.h \
    commands/flip_command.h  \
    common/common.h \
    view/frame.h \
    view/toolbar.h \
    view/photoinfo.h \
    view/about.h \
    view/mirroreditem.h \
    view/mirrorview.h \
    view/slideshow.h

FORMS    += view/mainwindow.ui \
    view/frame.ui \
    view/photoinfo.ui \
    view/about.ui \
    view/mirrorview.ui \
    view/slideshow.ui

RESOURCES += \
    mainwindow.qrc

INCLUDEPATH+=D:\OpenCV\opencv-3.4.9\include
             D:\OpenCV\opencv-3.4.9\include\opencv
             D:\OpenCV\opencv-3.4.9\include\opencv2
LIBS += D:\OpenCV\build_opencv\lib\libopencv_*.a

RC_ICONS = photoview.ico

