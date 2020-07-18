#ifndef VIEWMODEL_H
#define VIEWMODEL_H
#include <QImage>
#include <QFileInfo>
#include <memory>
#include "common/common.h"


class Model;
class Command;

class ViewModel
{
private:
    std::shared_ptr<QImage> q_image;
    std::shared_ptr<QMap<int,QFileInfo> > q_PhotoMap;
    std::shared_ptr<Model> model;

    std::shared_ptr<Command> open_file_command;
    std::shared_ptr<Command> show_pic_command;
    std::shared_ptr<Command> flip_command;
    std::shared_ptr<Command> save_file_command;
    std::shared_ptr<Command> rotate_command;
    std::shared_ptr<Command> start_camera_command;
    std::shared_ptr<Command> close_camera_command;
    std::shared_ptr<Command> save_camera_frame_command;
    std::shared_ptr<Command> update_camera_frame_command;

    std::shared_ptr<Notification> update_display_data_notification;
    std::shared_ptr<Notification> update_view_notification;

public:
    ViewModel();
    void bind(std::shared_ptr<Model> model);
    void exec_open_file_command(std::string path);
    void exec_flip_command(int type);
    void exec_show_pic_command(int ID);
    void exec_save_file_command(std::string path);
    void exec_rotate_command(int angle);
    void exec_close_camera_command();
    void exec_start_camera_command();
    void exec_save_camera_frame_command(std::string path);
    void exec_update_camera_frame_command();
    void set_update_view_notification(std::shared_ptr<Notification> notification);

    std::shared_ptr<Command> get_open_file_command();
    std::shared_ptr<Command> get_show_pic_command();
    std::shared_ptr<Command> get_start_camera_command();
    std::shared_ptr<Command> get_close_camera_command();
    std::shared_ptr<Command> get_save_camera_frame_command();
    std::shared_ptr<Command> get_update_camera_frame_command();
    std::shared_ptr<Command> get_save_file_command();
    std::shared_ptr<Command> get_rotate_command();
    std::shared_ptr<Command> get_flip_command();
    std::shared_ptr<Notification> get_update_display_data_notification();
    std::shared_ptr<QImage> get_img();
    std::shared_ptr<QMap<int,QFileInfo> > get_map();

    void notified();
    QImage Mat2QImage(cv::Mat const& src);
    cv::Mat QImage2Mat(QImage const& src);
};

#endif // VIEWMODEL_H
