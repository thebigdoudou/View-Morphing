#include "app.h"
#include "view/mainwindow.h"
#include "ViewModel/viewmodel.h"
#include "Model/model.h"
#include <memory>

app::app():view(new MainWindow),model(new Model), viewmodel(new ViewModel)
{
    viewmodel->bind(model);

    view->set_img(viewmodel->get_img());
    view->set_map(viewmodel->get_map());

    view->open_file_command(viewmodel->get_open_file_command());

    view->show_pic_command(viewmodel->get_show_pic_command());
    //view->del_pic_command(viewmodel->get_reset_command());
    view->start_camera_command(viewmodel->get_start_camera_command());
    view->close_camera_command(viewmodel->get_close_camera_command());
    view->save_camera_frame_command(viewmodel->get_save_camera_frame_command());
    view->update_camera_frame_command(viewmodel->get_update_camera_frame_command());
    view->save_file_command(viewmodel->get_save_file_command());
    view->rotate_command(viewmodel->get_rotate_command());
    view->flip_command(viewmodel->get_flip_command());

    viewmodel->set_update_view_notification(view->get_update_view_notification());
    model->set_update_display_data_notification(viewmodel->get_update_display_data_notification());
}

void app::run()
{
    view->show();
}
