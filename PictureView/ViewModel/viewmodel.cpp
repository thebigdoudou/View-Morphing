#include "viewmodel.h"
#include <QImage>
#include "Model/model.h"
#include "common/common.h"
#include "Notification/notification.h"
#include "commands/command.h"
#include "commands/open_file_command.h"
#include "commands/flip_command.h"
#include "commands/save_file_command.h"
#include "commands/show_pic_command.h"
#include "commands/rotate_command.h"
#include <QDebug>
ViewModel::ViewModel():q_image(new QImage),q_PhotoMap(new QMap<int, QFileInfo>){
    open_file_command = std::static_pointer_cast<Command, OpenFileCommand>(std::shared_ptr<OpenFileCommand> (new OpenFileCommand(std::shared_ptr<ViewModel>(this))));

    update_display_data_notification = std::static_pointer_cast<Notification, UpdateDisplayDataNotification>
            (std::shared_ptr<UpdateDisplayDataNotification>(new UpdateDisplayDataNotification(std::shared_ptr<ViewModel>(this))));

    //reset_command = std::static_pointer_cast<Command, ResetCommand>(std::shared_ptr<ResetCommand>(new ResetCommand(std::shared_ptr<ViewModel>(this))));
    flip_command = std::static_pointer_cast<Command, FlipCommand>(std::shared_ptr<FlipCommand>(new FlipCommand(std::shared_ptr<ViewModel>(this))));
    save_file_command = std::static_pointer_cast<Command, SaveFileCommand>(std::shared_ptr<SaveFileCommand>(new SaveFileCommand(std::shared_ptr<ViewModel>(this))));
    show_pic_command = std::static_pointer_cast<Command, ShowPicCommand>(std::shared_ptr<ShowPicCommand>(new ShowPicCommand(std::shared_ptr<ViewModel>(this))));
    rotate_command = std::static_pointer_cast<Command, RotateCommand>(std::shared_ptr<RotateCommand>(new RotateCommand(std::shared_ptr<ViewModel>(this))));
}


std::shared_ptr<Command> ViewModel::get_save_file_command(){
    return save_file_command;
}

void ViewModel::exec_open_file_command(std::string path){
    model->open_file(path);
}

void ViewModel::exec_flip_command(int type){
    model->flip(type);
}
void ViewModel::exec_show_pic_command(int ID){
    //std::cout<<"set_show_pic_command->exec();"<<std::endl;
    model->show_pic(ID);
}
void ViewModel::exec_rotate_command(int angle){
    model->rotate(angle);
}
void ViewModel::exec_save_file_command(std::string path){
     model->save_file(path);
}

void ViewModel::bind(std::shared_ptr<Model> model){
    this->model = model;
}

std::shared_ptr<Command> ViewModel::get_open_file_command(){
    return open_file_command;
}
std::shared_ptr<Command> ViewModel::get_show_pic_command(){
    return show_pic_command;
}

std::shared_ptr<Notification> ViewModel::get_update_display_data_notification(){
    return update_display_data_notification;
}
std::shared_ptr<Command> ViewModel::get_rotate_command(){
    return rotate_command;
}
std::shared_ptr<Command> ViewModel::get_flip_command(){
    return flip_command;
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
