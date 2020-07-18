#include "update_camera_frame_command.h"
#include "ViewModel/viewmodel.h"

UpdateCamFrame::UpdateCamFrame(std::shared_ptr<ViewModel> vm):viewmodel(vm){

}

void UpdateCamFrame::exec()
{
    //std::string path = std::static_pointer_cast<PathParameters, Parameters>(Command::params)->get_path();
    viewmodel->exec_update_camera_frame_command();
}

