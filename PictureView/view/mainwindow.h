﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPushButton>
#include <QFileInfo>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QImage>
#include "common/common.h"
#include "toolbar.h"
#include "about.h"
#include "photoinfo.h"
#include "mirrorview.h"
#include "slideshow.h"


class Notification;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void update();

    void set_img(std::shared_ptr<QImage> image);
    void set_map(std::shared_ptr<QMap<int,QFileInfo>> PhotoMap);

    void open_file_command(Command&&);
    void show_pic_command(Command&&);
    void save_file_command(Command&&);
    void start_camera_command(Command&&);
    void close_camera_command(Command&&);
    void start_face_detect_command(Command&&);
    void close_face_detect_command(Command&&);
    void save_camera_frame_command(Command&&);
    void update_camera_frame_command(Command&&);
    void del_pic_command(Command&&);
    void flip_command(Command&&);
    void rotate_command(Command&&);

    std::shared_ptr<Notification> get_update_view_notification();

    void SwitchPhoto(int index);
    QFileInfo GetFileInfo();
    QMap<int,QFileInfo> GetAllFileInfo();
    void Zoom();
    void SetToolBarLabel();
    void SwitchLanguage();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void resizeEvent (QResizeEvent *);
    void closeEvent (QCloseEvent *event);

private slots:
    void ZoomIn();
    void ZoomOut();
    void ZoomFit();
    void PhotoNext();
    void PhotoPrev();
    void FullScreen();
    void RotateRight();
    void RotateLeft();
    void FlipH();
    void FlipV();
    void Play();
    void Info();
    void Delete();
    void update_cam_frame();
    void hideMirrorView();
    void hideSlideShow();
    void photoNeeded(int index);
    void OpenCamera();
    void DetectFace();

    void on_actionHomePage_triggered();
    void on_actionAbout_triggered();
    void on_actionExit_triggered();
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    void on_actionEffect1_triggered();
    void on_actionEffect2_triggered();

private:
    //COMMANDS
    std::shared_ptr<QImage>  q_image;
    std::shared_ptr<QMap<int,QFileInfo> > PhotoMap;

    Command set_open_file_command;
    Command set_show_pic_command;
    Command set_save_file_command;
    Command set_del_pic_command;
    Command set_flip_command;
    Command set_rotate_command;
    Command set_start_camera_command;
    Command set_close_camera_command;
    Command set_start_face_detect_command;
    Command set_close_face_detect_command;
    Command set_save_camera_frame_command;
    Command set_update_camera_frame_command;
    std::shared_ptr<Notification> update_view_notification;

    Ui::MainWindow *ui;
    ToolBar *toolBar;

    MirrorView* mirrorView;
    SlideShow* slideShow;

    bool ZoomFlag;
    bool RotateFlipFlag;

    bool ZoomFactorFlag;
    qreal ZoomFactor;
    bool PhotoExist;
    bool CameraFlag;
    bool FaceFlag;
    int PhotoIndex;
    QTimer *timer;
};

#endif // MAINWINDOW_H
