#include "save_camera_frame_command.h"
#include "ViewModel/viewmodel.h"

SaveCamFrame::SaveCamFrame(std::shared_ptr<ViewModel> vm):viewmodel(vm){

}

void SaveCamFrame::exec()
{
    std::string path = std::static_pointer_cast<PathParameters, Parameters>(Command::params)->get_path();
    viewmodel->exec_save_camera_frame_command(path);
}

