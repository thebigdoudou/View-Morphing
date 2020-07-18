#include "view/mainwindow.h"
#include "ui_mainwindow.h"
#include "view/UpdateViewNotification.h"
#include <QPushButton>
#include <QWidget>
#include <QGridLayout>
#include <QFileInfo>
#include <QDragEnterEvent>
#include <QDesktopServices>
#include <QDropEvent>
#include <QMimeData>
#include <QDir>
#include <QLabel>
#include <QImage>
#include <QDebug>
#include <QMessageBox>
#include <QPainter>
#include <QFileDialog>
#include <QTranslator>


QStringList FileSuffix = (QStringList() << "png" <<
                          "jpg" << "jpeg" << "bmp" <<
                          "tif" << "tiff" << "webp" <<
                          "gif" << "jp2" << "dds" <<
                          "xpm" << "pnm" << "ppm" <<
                          "pgm" << "wbmp" << "ico" <<
                          "icns");

QStringList FileFilter = (QStringList() << "*.png" <<
                          "*.jpg" << "*.jpeg" << "*.bmp" <<
                          "*.tif" << "*.tiff" << "*.webp" <<
                          "*.gif" << "*.jp2" << "*.dds" <<
                          "*.xpm" << "*.pnm" << "*.ppm" <<
                          "*.pgm" << "*.wbmp" << "*.ico" <<
                          "*.icns");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    toolBar = new ToolBar();
    update_view_notification = std::static_pointer_cast<Notification, UpdateViewNotification>(std::shared_ptr<UpdateViewNotification>(new UpdateViewNotification(std::shared_ptr<MainWindow>(this))));
    ui->statusBar->addPermanentWidget(toolBar,1);
    ui->photo->setPixmap(QPixmap(":/images/drop.png"));
    setCentralWidget(ui->photo);

    ui->statusBar->hide();
    ui->menuBar->setNativeMenuBar(false);
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(update_cam_frame()));//时间到后启动opencam时间
    connect(toolBar->ZoomIn,SIGNAL(clicked()),this,SLOT(ZoomIn()));
    connect(toolBar->ZoomOut,SIGNAL(clicked()),this,SLOT(ZoomOut()));
    connect(toolBar->ZoomFit,SIGNAL(clicked()),this,SLOT(ZoomFit()));
    connect(toolBar->Prev,SIGNAL(clicked()),this,SLOT(PhotoPrev()));
    connect(toolBar->Next,SIGNAL(clicked()),this,SLOT(PhotoNext()));
    connect(toolBar->FullScreen,SIGNAL(clicked()),this,SLOT(FullScreen()));
    connect(toolBar->RotateLeft,SIGNAL(clicked()),this,SLOT(RotateLeft()));
    connect(toolBar->RotateRight,SIGNAL(clicked()),this,SLOT(RotateRight()));
    connect(toolBar->FlipH,SIGNAL(clicked()),this,SLOT(FlipH()));
    connect(toolBar->FlipV,SIGNAL(clicked()),this,SLOT(FlipV()));
    connect(toolBar->Info,SIGNAL(clicked()),this,SLOT(Info()));
    connect(toolBar->Play,SIGNAL(clicked()),this,SLOT(Play()));
    connect(toolBar->Delete,SIGNAL(clicked()),this,SLOT(Delete()));
    connect(toolBar->camera,SIGNAL(clicked()),this,SLOT(OpenCamera()));


    PhotoIndex = 0;
    PhotoExist = false;
    ZoomFlag = false;
    RotateFlipFlag = false;
    ZoomFactor = 1.0;
    ZoomFactorFlag = true;
    CameraFlag = 0;
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    foreach (const QUrl &purl, event->mimeData()->urls())
    {
        QFileInfo FileInfo(purl.toLocalFile());
        if(FileSuffix.contains(FileInfo.suffix(),Qt::CaseInsensitive))
        {
            (*PhotoMap).clear();
            (*PhotoMap)[(*PhotoMap).count()] = FileInfo;
            QList<QFileInfo> fileInfoList = FileInfo.dir().entryInfoList(FileFilter);
            fileInfoList.removeOne(FileInfo);
            while(fileInfoList.count() > 0)
            {
                (*PhotoMap)[(*PhotoMap).count()] = fileInfoList.takeFirst();
            }
            auto file_name = (*PhotoMap).value(0).absoluteFilePath();
            set_open_file_command->set_parameters(std::static_pointer_cast<Parameters, PathParameters>(std::shared_ptr<PathParameters>(new PathParameters(file_name.toStdString()))));
            set_open_file_command->exec();
            PhotoExist = true;
            PhotoIndex = 0;
            ui->statusBar->show();
            ZoomFit();
        }
    }
}

void MainWindow::update(){
    QImage image2 = (*q_image);
    ui->photo->setPixmap(QPixmap::fromImage(image2));
}
void MainWindow::update_cam_frame(){
    set_update_camera_frame_command->exec();
     timer->start(20);//启动计时器
}
void MainWindow::ZoomIn()
{
    if(PhotoExist)
    {
        if(!ZoomFlag)
        {
            Zoom();
            ZoomFlag = true;
        }
        ZoomFactor += 0.02;
        if(ZoomFactor >= 10.0)
            ZoomFactor = 10.0;
        QTransform tr = QTransform::fromScale(ZoomFactor,ZoomFactor);
        QImage image2 = (*q_image).transformed(tr,Qt::SmoothTransformation);
        ui->photo->setPixmap(QPixmap::fromImage(image2));

        SetToolBarLabel();
    }
}


void MainWindow::ZoomOut()
{
    if(PhotoExist)
    {
        if(!ZoomFlag)
        {
            Zoom();
            ZoomFlag = true;
        }
        ZoomFactor -= 0.02;
        if(ZoomFactor <= 0.01)
            ZoomFactor = 0.01;
        QTransform tr = QTransform::fromScale(ZoomFactor,ZoomFactor);
        QImage image2 = (*q_image).transformed(tr,Qt::SmoothTransformation);
        ui->photo->setPixmap(QPixmap::fromImage(image2));

        SetToolBarLabel();
    }
}

void MainWindow::ZoomFit()
{
    if(PhotoExist)
    {
        qreal pw = (*q_image).width();
        qreal ph = (*q_image).height();
        qreal ww = ui->photo->width();
        qreal wh = ui->photo->height();
        QImage image2;

        if(pw <= ww && ph <= wh)
        {
            image2 = (*q_image);
        }
        else
        {
            image2 = (*q_image).scaled(ui->photo->width(),ui->photo->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        }
        ui->photo->setPixmap(QPixmap::fromImage(image2));

        Zoom();
        SetToolBarLabel();
    }
}


void MainWindow::PhotoNext()
{
    //std::cout<<"PhotoNext"<<std::endl;
    if(PhotoExist)
    {
        //std::cout<<"PhotoNext"<<std::endl;
        qInfo()<<PhotoIndex;
        if(RotateFlipFlag)
        {
            QMessageBox SaveMsg(this);
            int answer;
            SaveMsg.setWindowTitle(tr("Save Changes"));
            SaveMsg.setText(tr("The Photo has been edited."));
            SaveMsg.setInformativeText(tr("Do you want to save your changes?"));
            SaveMsg.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            SaveMsg.setDefaultButton(QMessageBox::Save);
            SaveMsg.setButtonText(QMessageBox::Save, tr("Save"));
            SaveMsg.setButtonText(QMessageBox::Discard, tr("Discard"));
            SaveMsg.setButtonText(QMessageBox::Cancel, tr("Cancel"));
            answer = SaveMsg.exec();
            if(answer == QMessageBox::Save)
            {
                on_actionSave_triggered();
            }
            else if (answer == QMessageBox::Discard)
            {
                if(++PhotoIndex >= (*PhotoMap).count())
                {
                    PhotoIndex = 0;
                }

                SwitchPhoto(PhotoIndex);
            }
            else if (answer == QMessageBox::Cancel)
            {
                ;
            }
        }
        else
        {
            //std::cout<<"PhotoNext"<<std::endl;
            if(++PhotoIndex >= (*PhotoMap).count())
            {
                PhotoIndex = 0;
            }

            SwitchPhoto(PhotoIndex);
        }
    }
}

void MainWindow::PhotoPrev()
{
    if(PhotoExist)
    {
        if(RotateFlipFlag)
        {
            QMessageBox SaveMsg(this);
            int answer;
            SaveMsg.setWindowTitle(tr("Save Changes"));
            SaveMsg.setText(tr("The Photo has been edited."));
            SaveMsg.setInformativeText(tr("Do you want to save your changes?"));
            SaveMsg.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            SaveMsg.setDefaultButton(QMessageBox::Save);
            SaveMsg.setButtonText(QMessageBox::Save, tr("Save"));
            SaveMsg.setButtonText(QMessageBox::Discard, tr("Discard"));
            SaveMsg.setButtonText(QMessageBox::Cancel, tr("Cancel"));
            answer = SaveMsg.exec();
            if(answer == QMessageBox::Save)
            {
                on_actionSave_triggered();
            }
            else if (answer == QMessageBox::Discard)
            {
                if(--PhotoIndex < 0)
                {
                    PhotoIndex = (*PhotoMap).count()-1;
                }

                SwitchPhoto(PhotoIndex);
            }
            else if (answer == QMessageBox::Cancel)
            {
                ;
            }
        }
        else
        {
            if(--PhotoIndex < 0)
            {
                PhotoIndex = (*PhotoMap).count()-1;
            }

            SwitchPhoto(PhotoIndex);
        }
    }
}


void MainWindow::SwitchPhoto(int index)
{
//    (*q_image).load((*PhotoMap).value(index).absoluteFilePath());
//    ZoomFlag = false;
//    RotateFlipFlag = false;
//    ZoomFit();
    //std::cout<<"SwitchPhoto index"<<index<<std::endl;
    set_show_pic_command->set_parameters(std::static_pointer_cast<Parameters, IntParameters>(std::shared_ptr<IntParameters>(new IntParameters(index))));
    //std::cout<<"SwitchPhoto index"<<index<<std::endl;
    set_show_pic_command->exec();
    ZoomFlag = false;
    RotateFlipFlag = false;
    ZoomFit();
}

void MainWindow::resizeEvent (QResizeEvent *)
{
    if(PhotoExist == true)
    {
        ZoomFit();
    }
}

void MainWindow::OpenCamera(){
    if(CameraFlag==0){
        timer->start(20);//启动计时器
        set_start_camera_command->exec();
        CameraFlag=1;
    }
    else{
        set_close_camera_command->exec();
        CameraFlag=0;
        timer->stop();
    }
}

void MainWindow::FullScreen()
{
    if(CameraFlag)
    {
        auto path = GetFileInfo().path();
        auto file_name = QFileDialog::getSaveFileName(this, tr("打开文件"), path,
                                                      tr("image(*.png *.jpg *.bmp *.tiff);;AllFile(*)"));
        if(file_name.isEmpty()){
            QMessageBox::information(this, tr("Failed to Open this!"), tr("OK"));
            return;
        }
        qInfo() << file_name;
        set_save_camera_frame_command->set_parameters(std::static_pointer_cast<Parameters, PathParameters>(std::shared_ptr<PathParameters>(new PathParameters(file_name.toStdString()))));
        set_save_camera_frame_command->exec();
    }
}


void MainWindow::RotateLeft()
{
    if(PhotoExist)
    {
        set_rotate_command->set_parameters(std::static_pointer_cast<Parameters, IntParameters>(std::shared_ptr<IntParameters>(new IntParameters(0))));
        set_rotate_command->exec();
    }
}

void MainWindow::RotateRight()
{
    if(PhotoExist)
    {
        set_rotate_command->set_parameters(std::static_pointer_cast<Parameters, IntParameters>(std::shared_ptr<IntParameters>(new IntParameters(1))));
        set_rotate_command->exec();
    }
}

void MainWindow::FlipV()
{
    if(PhotoExist)
    {
        set_flip_command->set_parameters(std::static_pointer_cast<Parameters, IntParameters>(std::shared_ptr<IntParameters>(new IntParameters(0))));
        set_flip_command->exec();
    }
}

void MainWindow::FlipH()
{
    if(PhotoExist)
    {
        set_flip_command->set_parameters(std::static_pointer_cast<Parameters, IntParameters>(std::shared_ptr<IntParameters>(new IntParameters(1))));
        set_flip_command->exec();
    }
}

void MainWindow::Play()
{
    if(PhotoExist)
    {
        if(ui->actionEffect1->isChecked())
        {
            if((*PhotoMap).count() > 0)
            {
                mirrorView = new MirrorView();
                connect(mirrorView,SIGNAL(neededPhoto(int)),this,SLOT(photoNeeded(int)));
                connect(mirrorView,SIGNAL(hideMe()),this,SLOT(hideMirrorView()));
                mirrorView->setImageList((*PhotoMap).keys());
                int imageCount = 7;
                if(imageCount > (*PhotoMap).keys().count())
                    imageCount  = (*PhotoMap).keys().count();

                for(int i = 0; i < imageCount; ++i)
                {
                    mirrorView->loadImage((*PhotoMap).keys().at(i),
                                          QPixmap((*PhotoMap).value((*PhotoMap).keys().at(i)).absoluteFilePath()));
                }
                mirrorView->showFullScreen();
            }
        }

        if(ui->actionEffect2->isChecked())
        {
            if((*PhotoMap).count() > 0)
            {
                slideShow = new SlideShow(this);
                connect(slideShow,SIGNAL(hideMe()),this,SLOT(hideSlideShow()));
                slideShow->showFullScreen();
            }
        }
    }
}

void MainWindow::hideMirrorView()
{
    mirrorView->close();
    delete mirrorView;
    mirrorView = NULL;
}

void MainWindow::hideSlideShow()
{
    slideShow->close();
    delete slideShow;
    slideShow = NULL;
}

void MainWindow::photoNeeded(int index)
{
    if((*PhotoMap).keys().contains(index))
    {
        if((*PhotoMap).value(index).exists())
            mirrorView->loadImage(index,QPixmap((*PhotoMap).value(index)
                                                .absoluteFilePath()));
        else
            mirrorView->removeIndex(index);
    }
}

void MainWindow::Info()
{
    if(PhotoExist)
    {
        PhotoInfo *photoInfo = new PhotoInfo(this);
        photoInfo->exec();
    }
}

void MainWindow::Delete()
{
    if(PhotoExist)
    {
        set_del_pic_command->set_parameters(std::static_pointer_cast<Parameters, IntParameters>(std::shared_ptr<IntParameters>(new IntParameters(PhotoIndex))));
        set_del_pic_command->exec();
        if(PhotoIndex==(*PhotoMap).count())
        {
            PhotoIndex=0;
        }
    }
}


void MainWindow::on_actionHomePage_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/thebigdoudou/View-Morphing/tree/master/PictureView"));
}

void MainWindow::on_actionAbout_triggered()
{
    About *about = new About(this);
    about->exec();
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::exit(0);
}

void MainWindow::on_actionSave_triggered()
{
    if(PhotoExist)
    {
        auto path = GetFileInfo().path();
        auto file_name = QFileDialog::getSaveFileName(this, tr("打开文件"), path,
                                                      tr("image(*.png *.jpg *.bmp *.tiff);;AllFile(*)"));
        if(file_name.isEmpty()){
            QMessageBox::information(this, tr("Failed to Open this!"), tr("OK"));
            return;
        }
        qInfo() << file_name;
        set_save_file_command->set_parameters(std::static_pointer_cast<Parameters, PathParameters>(std::shared_ptr<PathParameters>(new PathParameters(file_name.toStdString()))));
        set_save_file_command->exec();
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QFileDialog OpenPhoto(this);
    OpenPhoto.setFileMode(QFileDialog::ExistingFile);
    OpenPhoto.setNameFilter("All Supported Files (*.png ; *.jpg ; *.jpeg ; *.bmp ; *.tif ; *.tiff ; *.webp ;"
                               "*.gif ; *.jp2 ; *.dds ; *.xpm ; *.pnm ; *.ppm ; *.pgm ; *.wbmp ; *.xbm ; *.pbm ;"
                               "*.ico ; *.icns);; All Files(*)");

    OpenPhoto.setWindowTitle(tr("Open Photo"));
    if(OpenPhoto.exec())
    {
        QStringList PhotoFile;
        PhotoFile = OpenPhoto.selectedFiles();
        PhotoExist = true;

        auto file_name = PhotoFile.at(0);
        set_open_file_command->set_parameters(std::static_pointer_cast<Parameters, PathParameters>(std::shared_ptr<PathParameters>(new PathParameters(file_name.toStdString()))));
        set_open_file_command->exec();

        PhotoIndex = 0;
        ui->statusBar->show();
        ZoomFit();
    }
}

void MainWindow::on_actionEffect1_triggered()
{
    ui->actionEffect2->setChecked(false);
    ui->actionEffect1->setChecked(true);
}

void MainWindow::on_actionEffect2_triggered()
{
    ui->actionEffect1->setChecked(false);
    ui->actionEffect2->setChecked(true);
}

QFileInfo MainWindow::GetFileInfo()
{
    return (*PhotoMap).value(PhotoIndex);
}

QMap<int,QFileInfo> MainWindow::GetAllFileInfo()
{
    return (*PhotoMap);
}


void MainWindow::Zoom()
{
    qreal pw = (*q_image).width();
    qreal ph = (*q_image).height();
    qreal ww = ui->photo->width();
    qreal wh = ui->photo->height();

    qreal widthFactor = ww / pw;
    qreal heightFactor = wh / ph;

    ZoomFactorFlag = widthFactor <= heightFactor ? true : false;

    if(pw <= ww && ph <= wh)
    {
        ZoomFactor = 1.0;
    }
    else
    {
        if(ZoomFactorFlag)
        {
            ZoomFactor = widthFactor;
        }
        else
        {
            ZoomFactor = heightFactor;
        }
    }

}

void MainWindow::SetToolBarLabel()
{
    QString str;
    int zoom = ZoomFactor * 100;
    str = tr("Zoom ") + QString::number(zoom) + "% | " + (*PhotoMap).value(PhotoIndex).fileName()
           + " | " + QString::number((*q_image).width()) + " x " + QString::number((*q_image).height());
    toolBar->label->setText(str);
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    if(RotateFlipFlag)
    {
        QMessageBox SaveMsg(this);
        int answer;
        SaveMsg.setWindowTitle(tr("Save Changes"));
        SaveMsg.setText(tr("The Photo has been edited."));
        SaveMsg.setInformativeText(tr("Do you want to save your changes?"));
        SaveMsg.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        SaveMsg.setDefaultButton(QMessageBox::Save);
        SaveMsg.setButtonText(QMessageBox::Save, tr("Save"));
        SaveMsg.setButtonText(QMessageBox::Discard, tr("Discard"));
        SaveMsg.setButtonText(QMessageBox::Cancel, tr("Cancel"));
        answer = SaveMsg.exec();
        if(answer == QMessageBox::Save)
        {
            on_actionSave_triggered();
        }
        else if (answer == QMessageBox::Discard)
        {
            close();
        }
        else if (answer == QMessageBox::Cancel)
        {
            event->ignore();
        }
    }
}

///* Binding Commands */
void MainWindow::set_img(std::shared_ptr<QImage> image){
    this->q_image = image;
}

void MainWindow::set_map(std::shared_ptr<QMap<int,QFileInfo>> PhotoMap)
{
    this->PhotoMap = PhotoMap;
}

void MainWindow::open_file_command(std::shared_ptr<Command> command){
    set_open_file_command = command;
}

void MainWindow::show_pic_command(std::shared_ptr<Command> command){
    set_show_pic_command = command;
}

void MainWindow::save_file_command(std::shared_ptr<Command> command){
    set_save_file_command = command;
}
void MainWindow::start_camera_command(std::shared_ptr<Command> command){
    set_start_camera_command = command;
}
void MainWindow::close_camera_command(std::shared_ptr<Command> command){
    set_close_camera_command = command;
}
void MainWindow::save_camera_frame_command(std::shared_ptr<Command> command){
    set_save_camera_frame_command = command;
}
void MainWindow::update_camera_frame_command(std::shared_ptr<Command> command){
    set_update_camera_frame_command = command;
}
void MainWindow::del_pic_command(std::shared_ptr<Command> command){
    set_del_pic_command = command;
}
void MainWindow::flip_command(std::shared_ptr<Command> command){
    set_flip_command = command;
}
void MainWindow::rotate_command(std::shared_ptr < Command > command) {
    set_rotate_command = command;
}


std::shared_ptr<Notification> MainWindow::get_update_view_notification(){
    return update_view_notification;
}
