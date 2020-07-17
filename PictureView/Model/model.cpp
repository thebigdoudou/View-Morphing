#include "model.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include "Model/model.h"
#include <QDebug>
#include <iostream>

#include <QDir>
//take all file in the current directory to the working space (data structure: list of images, Qmap)
void Model::open_file(std::string path){
    QString qpath = QString::fromStdString(path);
    QFileInfo FileInfo(qpath);
    if(FileSuffix.contains(FileInfo.suffix(),Qt::CaseInsensitive))
    {
        PhotoMap.clear();
        PhotoMap[PhotoMap.count()] = FileInfo;
        read_img(FileInfo.absoluteFilePath().toStdString());
        QList<QFileInfo> fileInfoList = FileInfo.dir().entryInfoList(FileFilter);
        fileInfoList.removeOne(FileInfo);
        while(fileInfoList.count() > 0)
        {
            QFileInfo curQFileInfo=fileInfoList.takeFirst();
            (PhotoMap)[(PhotoMap).count()] = curQFileInfo;
            read_img(curQFileInfo.absoluteFilePath().toStdString());
        }
        CurrentID=0;
    }
    notify();
}
void Model::read_img(std::string path){
    std::cout << path << std::endl;
    cv::Mat img=cv::imread(path);

    if(img.empty()){
        qInfo() << "image file read faile";
    }else{
        //CurrentID=CntNum;
        CntNum++;
        images.push_back(img);

    }
}
cv::Mat& Model::getListImg(int x){
    std::cout<<"x:  "<<x<<std::endl;
    int tmp=0;
    for (std::list<cv::Mat>::iterator it = images.begin(); it != images.end(); ++it){
        if (tmp==x) return *it;
        tmp++;
    }
}
//void Model::setListImg(int ID, cv::Mat &img){
//    static int tmp=0;
//    for (std::list<cv::Mat>::iterator it = images.begin(); it != images.end(); ++it){
//        if (tmp==x) *it
//        tmp++;
//    }
//}
void Model::show_pic(int ID){
    std::cout<<"show_pic: "<<ID<<std::endl;
    CurrentID=ID;
    notify();
}
cv::Mat& Model::getImg(){
    // TO FIX
    if (CameraIsOn) return CameraFrame;
    else
    return getListImg(CurrentID);
}
QMap<int,QFileInfo>& Model::getPhotoMap(){
    return PhotoMap;
}



//cv::Mat& Model::getOrigin(){
//    return originImg;
//}

//void Model::bind(std::shared_ptr<ViewModel> viewmodel){
//    this->viewmodel = viewmodel;
//}

void Model::set_update_display_data_notification(std::shared_ptr<Notification> notification){
    this->update_display_data_notification = notification;
}

void Model::notify(){
    update_display_data_notification->exec();
}

void Model::save_file(std::string path){
    save_fileID(path, CurrentID);
}
void Model::save_fileID(std::string path, int ID){
    std::cout << path << std::endl;
    std::cout << ID << std::endl;
    cv::Mat &img=getListImg(ID);
    cv::imwrite(path, img);
}
void Model::StartCamera(){
    CameraIsOn=1;
    videoCapture_1.set(cv::CAP_PROP_FRAME_HEIGHT, 960);
    videoCapture_1.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
    videoCapture_1.set(cv::CAP_PROP_FPS, 25.0);
    videoCapture_1.open(0);
    while (1) {
        videoCapture_1 >> CameraFrame;
        imshow("摄像头1", CameraFrame);
        notify();
    }
}
void Model::CloseCamera(){
    videoCapture_1.release();
    notify();
}
void Model::SaveCamPic(std::string Path){
    cv::imwrite(Path, CameraFrame);
    notify();
}

//void Model::save_bmp_file(std::string path){
//    cv::imwrite(path, image);
//}
void Model::rotate(int angle){
    rotateID(angle, CurrentID);
}
void Model::flip(int type){
    std::cout<<"dfs"<<std::endl;
    flipID(type, CurrentID);
}
void Model::flipID(int type, int ID){
    cv::Mat &img=getListImg(ID);
    cv::flip(img, img, type);
    notify();
}

void Model::rotateID(int angle, int ID)
{
    std::cout<<angle<<ID<<std::endl;
    cv::Mat &img=getListImg(ID);
    cv::transpose(img, img);
    cv::flip(img, img, angle);
    notify();
}

