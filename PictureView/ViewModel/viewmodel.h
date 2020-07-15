#ifndef VIEWMODEL_H
#define VIEWMODEL_H
#include <QImage>
#include <QFileInfo>
#include <memory>
#include "Parameters/parameters.h"
#include "commands/command.h"

class Model;
class Notification;
class ViewModelNotification;
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

    void set_update_view_notification(std::shared_ptr<Notification> notification);

    std::shared_ptr<Command> get_open_file_command();
    std::shared_ptr<Command> get_filter_rem_command();
    std::shared_ptr<Command> get_show_pic_command();
    std::shared_ptr<Command> get_save_file_command();
    std::shared_ptr<Command> get_rotate_command();
    std::shared_ptr<Command> get_flip_command();
    std::shared_ptr<Notification> get_update_display_data_notification();
    std::shared_ptr<QImage> get_img();
    std::shared_ptr<QMap<int,QFileInfo> > get_map();

    void notified();
};

#endif // VIEWMODEL_H
