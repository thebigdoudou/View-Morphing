#include "model.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include "ViewModel/viewmodel.h"
#include "Notification/notification.h"
#include "Model/model.h"
#include <QDebug>
#include <iostream>
#include <QDir>

void Model::open_file(std::string path){

//    std::cout << path << std::endl;
    cv::Mat img=cv::imread(path);

    if(img.empty()){
        qInfo() << "image file read faile";
    }else{
        CurrentID=CntNum;
        CntNum++;
        images.push_back(img);
        notify();
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
    CurrentID=ID;
    notify();
}
cv::Mat& Model::get(){
    return getListImg(CurrentID);
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

//void Model::filterReminiscence(){
//    cv::Mat tmpImg(image.size(),CV_8UC3);
//    if(tmpImg.empty() == true){
//        std::cout<<"Can not create tmpImg! "<<std::endl;
//        return ;
//    }
//    for (int y=0; y<image.rows; y++)
//    {
//        uchar* P0  = image.ptr<uchar>(y);
//        uchar* P1  = tmpImg.ptr<uchar>(y);
//        for (int x=0; x<image.cols; x++)
//        {
//            float B=P0[3*x];
//            float G=P0[3*x+1];
//            float R=P0[3*x+2];
//            float newB=0.272*R+0.534*G+0.131*B;
//            float newG=0.349*R+0.686*G+0.168*B;
//            float newR=0.393*R+0.769*G+0.189*B;
//            if(newB<0)newB=0;
//            if(newB>255)newB=255;
//            if(newG<0)newG=0;
//            if(newG>255)newG=255;
//            if(newR<0)newR=0;
//            if(newR>255)newR=255;
//            P1[3*x] = (uchar)newB;
//            P1[3*x+1] = (uchar)newG;
//            P1[3*x+2] = (uchar)newR;
//        }
//    }
//    interImg = tmpImg;
//    image = tmpImg;
//    if(image.empty()){
//        qInfo() << "false";
//    }else{
//        notify();
//    }
//}


//void Model::reset() {
//	image = originImg;
//    interImg = originImg;
//	if (image.empty())
//	{
//		qInfo() << "false";
//	}
//	else {
//		notify();
//	}
//}
void Model::save_file(std::string path){
    save_fileID(path, CurrentID);
}
void Model::save_fileID(std::string path, int ID){
    std::cout << path << std::endl;
    std::cout << ID << std::endl;
    cv::Mat &img=getListImg(ID);
    cv::imwrite(path, img);

}
//void Model::save_bmp_file(std::string path){
//    cv::imwrite(path, image);
//}
void Model::rotate(int angle){
    rotateID(angle, CurrentID);
}
void Model::rotateID(int angle, int ID)
{
    std::cout<<angle<<ID<<std::endl;
    cv::Mat &img=getListImg(ID);

//    cv:: Point2f center( (float)(img.cols/2) , (float) (img.rows/2));
//    cv::Mat trans_mat = getRotationMatrix2D( center, angle, 1 );
//    float radian = (float) (angle /180.0 * CV_PI);
//    float sinVal = abs(sin(radian));
//    float cosVal = abs(cos(radian));
//    cv::Size targetSize(img.rows, img.cols);
//    warpAffine(img, img, trans_mat, targetSize);
     transpose(img, img);
     flip(img, img, angle);
    //setListImg(ID, img);
    notify();
}
