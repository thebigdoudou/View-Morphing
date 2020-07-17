#include "close_camera_command.h"
#include "ViewModel/viewmodel.h"

CloseCameraCommand::CloseCameraCommand(std::shared_ptr<ViewModel> vm):viewmodel(vm){

}

void CloseCameraCommand::exec()
{
    //std::string path = std::static_pointer_cast<PathParameters, Parameters>(Command::params)->get_path();
    viewmodel->exec_close_camera_command();
}

