#include "toolbar.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIcon>

ToolBar::ToolBar(QWidget *parent) : QWidget(parent)
{
    ZoomIn = new QPushButton(this);
    ZoomOut = new QPushButton(this);
    ZoomFit = new QPushButton(this);
    FullScreen = new QPushButton(this);
    Prev = new QPushButton(this);
    Next = new QPushButton(this);
    RotateLeft = new QPushButton(this);
    RotateRight = new QPushButton(this);
    Delete = new QPushButton(this);
    FlipH = new QPushButton(this);
    FlipV = new QPushButton(this);
    Play = new QPushButton(this);
    Info = new QPushButton(this);
    camera = new QPushButton(this);
    FaceDetect = new QPushButton(this);

    ZoomIn->setObjectName("ZoomIn");
    ZoomOut->setObjectName("ZoomOut");
    ZoomFit->setObjectName("ZoomFit");
    FullScreen->setObjectName("FullScreen");
    Prev->setObjectName("Prev");
    Next->setObjectName("Next");
    RotateLeft->setObjectName("RotateLeft");
    RotateRight->setObjectName("RotateRight");
    Delete->setObjectName("Delete");
    Info->setObjectName("Info");
    FlipV->setObjectName("FlipV");
    FlipH->setObjectName("FlipH");
    Play->setObjectName("Play");
    camera->setObjectName("Carema");
    FaceDetect->setObjectName("FaceDetect");
    //Resize = new QPushButton(this);

    ZoomIn->setIcon(QIcon(":/images/zoomin.png"));
    ZoomOut->setIcon(QIcon(":/images/zoomout.png"));
    ZoomFit->setIcon(QIcon(":/images/zoomfit.png"));
    FullScreen->setIcon(QIcon(":/images/resize.png"));
    Prev->setIcon(QIcon(":/images/prev.png"));
    Next->setIcon(QIcon(":/images/next.png"));
    RotateLeft->setIcon(QIcon(":/images/rotateleft.png"));
    RotateRight->setIcon(QIcon(":/images/rotateright.png"));
    Delete->setIcon(QIcon(":/images/delete.png"));
    Info->setIcon(QIcon(":/images/info.png"));
    FlipV->setIcon(QIcon(":/images/flipvertical.png"));
    FlipH->setIcon(QIcon(":/images/fliphorizontal.png"));
    Play->setIcon(QIcon(":/images/play.png"));
    camera->setIcon(QIcon(":/images/camera.png"));
    FaceDetect->setIcon(QIcon(":/images/face.png"));
    //Resize->setIcon(QIcon(":/images/resize.png"));

    ZoomIn->setToolTip(tr("Zoom In"));
    ZoomOut->setToolTip(tr("Zoom Out"));
    ZoomFit->setToolTip(tr("Fit to Window"));
    FullScreen->setToolTip(tr("Full Screen"));
    Prev->setToolTip(tr("Prev"));
    Next->setToolTip(tr("Next"));
    RotateLeft->setToolTip(tr("Rotate Left"));
    RotateRight->setToolTip(tr("Rotate Right"));
    Delete->setToolTip(tr("Delete"));
    Info->setToolTip(tr("Infomation"));
    FlipV->setToolTip(tr("Flip Vertical"));
    FlipH->setToolTip(tr("Flip Horizontal"));
    Play->setToolTip(tr("Play"));
    camera->setToolTip(tr("Camera"));
    FaceDetect->setToolTip(tr("FaceDetect"));

    label = new QLabel;
    label->setObjectName("label");
    QHBoxLayout *labelLayout = new QHBoxLayout;
    labelLayout->addStretch();
    labelLayout->addWidget(label);
    labelLayout->addStretch();
    labelLayout->setContentsMargins(0,0,0,0);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addStretch(28);
    mainLayout->addWidget(ZoomIn,4);
    mainLayout->addWidget(ZoomOut,4);
    mainLayout->addWidget(ZoomFit,4);
    mainLayout->addWidget(Prev,4);
    mainLayout->addWidget(Next,4);
    mainLayout->addWidget(RotateLeft,4);
    mainLayout->addWidget(RotateRight,4);
    mainLayout->addWidget(FlipH,4);
    mainLayout->addWidget(FlipV,4);
    //mainLayout->addWidget(Resize);
    mainLayout->addWidget(Play,4);
    mainLayout->addWidget(Info,4);
    mainLayout->addWidget(Delete,4);
    mainLayout->addWidget(camera,4);
    mainLayout->addWidget(FullScreen,4);
    mainLayout->addWidget(FaceDetect,4);
    mainLayout->addStretch(28);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(3);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addLayout(labelLayout);
    layout->addLayout(mainLayout);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(2);
    setWindowFlags(Qt::FramelessWindowHint);
}

