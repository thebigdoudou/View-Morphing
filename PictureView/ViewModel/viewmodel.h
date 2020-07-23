#ifndef VIEWMODEL_H
#define VIEWMODEL_H
#include <QImage>
#include <QFileInfo>
#include <memory>
#include "common/common.h"


class Model;

class ViewModel
{
private:
    std::shared_ptr<QImage> q_image;
    std::shared_ptr<QMap<int,QFileInfo> > q_PhotoMap;
    std::shared_ptr<Model> model;

    std::shared_ptr<Notification> update_display_data_notification;
    std::shared_ptr<Notification> update_view_notification;

public:
    ViewModel();
    void bind(std::shared_ptr<Model> model);
    void set_update_view_notification(std::shared_ptr<Notification> notification);

    Command get_open_file_command();
    Command get_show_pic_command();
    Command get_start_camera_command();
    Command get_close_camera_command();
    Command get_save_camera_frame_command();
    Command get_update_camera_frame_command();
    Command get_save_file_command();
    Command get_rotate_command();
    Command get_flip_command();
    std::shared_ptr<Notification> get_update_display_data_notification();
    std::shared_ptr<QImage> get_img();
    std::shared_ptr<QMap<int,QFileInfo> > get_map();

    void notified();
    QImage Mat2QImage(cv::Mat const& src);
    cv::Mat QImage2Mat(QImage const& src);
};

#endif // VIEWMODEL_H
