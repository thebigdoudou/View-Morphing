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
win64{
INCLUDEPATH+=D:\OpenCV\opencv-3.4.9\include
             D:\OpenCV\opencv-3.4.9\include\opencv
             D:\OpenCV\opencv-3.4.9\include\opencv2
}
macx{
INCLUDEPATH+=usr/local/Cellar/opencv/4.3.0_5/include/opencv4
INCLUDEPATH+=/usr/local/include/opencv4
}
win64{
LIBS += D:\OpenCV\build_opencv\lib\libopencv_*.a
}
macx{
LIBS += -L/usr/local/lib -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dnn -lopencv_dpm -lopencv_fuzzy -lopencv_line_descriptor -lopencv_optflow -lopencv_plot -lopencv_reg -lopencv_saliency -lopencv_stereo -lopencv_structured_light -lopencv_rgbd -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_face -lopencv_xfeatures2d -lopencv_shape -lopencv_video -lopencv_ximgproc -lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_xobjdetect -lopencv_objdetect -lopencv_ml -lopencv_xphoto -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_photo -lopencv_imgproc -lopencv_core
}
RC_ICONS = photoview.ico

