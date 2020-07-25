

#include <vector>
#include <QDebug>
#include <iostream>
#include "Model/model.h"

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
}
void Model::StartFaceDetect(){
    FaceDectectIsOn=1;
    notify();
}
void Model::CloseFaceDetect(){
    FaceDectectIsOn=0;
    notify();
}
void line_one_face_detections(cv::Mat &img, std::vector<dlib::full_object_detection> fs)
{
    int i, j;
    for(j=0; j<fs.size(); j++)
    {
        cv::Point p1, p2;
        for(i = 0; i<67; i++)
        {
            // 下巴到脸颊 0 ~ 16
            //左边眉毛 17 ~ 21
            //右边眉毛 21 ~ 26
            //鼻梁     27 ~ 30
            //鼻孔        31 ~ 35
            //左眼        36 ~ 41
            //右眼        42 ~ 47
            //嘴唇外圈  48 ~ 59
            //嘴唇内圈  59 ~ 67
            switch(i)
            {
                case 16:
                case 21:
                case 26:
                case 30:
                case 35:
                case 41:
                case 47:
                case 59:
                    i++;
                    break;
                default:
                    break;
            }

            p1.x = fs[j].part(i).x();
            p1.y = fs[j].part(i).y();
            p2.x = fs[j].part(i+1).x();
            p2.y = fs[j].part(i+1).y();
            cv::line(img, p1, p2, cv::Scalar(0,0,255), 2, 4, 0);
        }
    }
}
void Model::UpdateCamFrame(){
    if (!CameraIsOn) return ;
    videoCapture_1 >> CameraFrame;
    if (FaceDectectIsOn) {

        dlib::array2d<dlib::bgr_pixel> dimg;
        dlib::assign_image(dimg, dlib::cv_image<uchar>(CameraFrame));
        vector<dlib::rectangle> dets = detector(dimg);
        std::cout << "Number of faces detected: " << dets.size() << std::endl;
        if (dets.size() == 0) {notify(); return ;}
        std::vector<dlib::full_object_detection> shapes;
        int i = 0;
        for(i = 0; i < dets.size(); i++)
        {
            dlib::full_object_detection shape = sp(dimg, dets[i]); //获取指定一个区域的人脸形状
            shapes.push_back(shape);
        }
        for(i=0; i<dets.size(); i++)
        {
            //画出人脸所在区域
            cv::Rect r;
            r.x = dets[i].left();
            r.y = dets[i].top();
            r.width = dets[i].width();
            r.height = dets[i].height();
            cv::rectangle(CameraFrame, r, cv::Scalar(0, 0, 255), 1, 1, 0);
        }

        line_one_face_detections(CameraFrame, shapes);
    }
    notify();
}
void Model::CloseCamera(){
    CameraIsOn=0;
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

