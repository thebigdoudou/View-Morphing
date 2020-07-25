#include "Model/model.h"
#include "common/common.h"
#include "UpdateData.h"
#include <QImage>
#include <QDebug>
ViewModel::ViewModel():q_image(new QImage),q_PhotoMap(new QMap<int, QFileInfo>){

    update_display_data_notification = std::static_pointer_cast<Notification, UpdateData>
            (std::shared_ptr<UpdateData>(new UpdateData(std::shared_ptr<ViewModel>(this))));
}

void ViewModel::bind(std::shared_ptr<Model> model){
    this->model = model;
}

Command ViewModel::get_save_file_command(){
    return [this](std::any t)->bool {
        string s = std::any_cast<string>(t);
        return this->model->save_file(s);
    };
}
Command ViewModel::get_update_camera_frame_command(){
    return [this](std::any t)->bool {
        return this->model->UpdateCamFrame();
    };
}
Command ViewModel::get_start_camera_command(){
    return [this](std::any t)->bool{
        return this->model->StartCamera();
    };
}
Command ViewModel::get_close_camera_command(){
    return [this](std::any t)->bool{
        return this->model->CloseCamera();
    };
}
Command ViewModel::get_start_face_detect_command(){
    return [this](std::any t)->bool{
        return this->model->StartFaceDetect();
    };
}
Command ViewModel::get_close_face_detect_command(){
    return [this](std::any t)->bool{
        return this->model->CloseFaceDetect();
    };
}
Command ViewModel::get_save_camera_frame_command(){
    return [this](std::any t)->bool {
        string s = std::any_cast<string>(t);
        return this->model->SaveCamPic(s);
    };
}
Command ViewModel::get_open_file_command(){
    return [this](std::any t)->bool {
        string s = std::any_cast<string>(t);
        return this->model->open_file(s);
    };
}
Command ViewModel::get_show_pic_command(){
    return [this](std::any t)->bool{
        int g=std::any_cast<int>(t);
        return this->model->show_pic(g);
    };
}

std::shared_ptr<Notification> ViewModel::get_update_display_data_notification(){
    return update_display_data_notification;
}
Command ViewModel::get_rotate_command(){
    return [this](std::any t)->bool{
        int angle=std::any_cast<int>(t);
        return this->model->rotate(angle);
    };
}
Command ViewModel::get_flip_command(){
    return [this](std::any t)->bool{
        int type=std::any_cast<int>(t);
        return this->model->flip(type);
    };
}

Command ViewModel::get_del_pic_command(){
    return [this](std::any t)->bool{
        int type=std::any_cast<int>(t);
        return this->model->del_pic();
    };
}

std::shared_ptr<QImage> ViewModel::get_img(){
    return q_image;
}
std::shared_ptr<QMap<int,QFileInfo> > ViewModel::get_map(){
    return q_PhotoMap;
}

void ViewModel::set_update_view_notification(std::shared_ptr<Notification> notification)
{
    update_view_notification = notification;
}

void ViewModel::notified(){
    *q_image = Mat2QImage(model->getImg());
    //std::cout<<q_PhotoMap<<std::endl;
    //std::cout<<&model->getPhotoMap()<<std::endl;
    *q_PhotoMap = model->getPhotoMap();
    update_view_notification->exec();
}

QImage ViewModel:: Mat2QImage(cv::Mat const& src)
{
     cv::Mat temp; // make the same cv::Mat
     cvtColor(src, temp,cv::COLOR_BGR2RGB); // cvtColor Makes a copt, that what i need
     QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
     dest.bits(); // enforce deep copy, see documentation
     // of QImage::QImage ( const uchar * data, int width, int height, Format format )
     return dest;
}

cv::Mat ViewModel:: QImage2Mat(QImage const& src)
{
     cv::Mat tmp(src.height(),src.width(),CV_8UC3,(uchar*)src.bits(),src.bytesPerLine());
     cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
     cvtColor(tmp, result,cv::COLOR_BGR2RGB);
     return result;
}
