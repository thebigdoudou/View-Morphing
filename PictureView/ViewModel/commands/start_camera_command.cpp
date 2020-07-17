#include "start_camera_command.h"
#include "ViewModel/viewmodel.h"

StartCameraCommand::StartCameraCommand(std::shared_ptr<ViewModel> vm):viewmodel(vm){

}

void StartCameraCommand::exec()
{
    //std::string path = std::static_pointer_cast<PathParameters, Parameters>(Command::params)->get_path();
    viewmodel->exec_start_camera_command();
}

