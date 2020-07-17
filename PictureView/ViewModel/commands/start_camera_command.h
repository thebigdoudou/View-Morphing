#ifndef _START_CAM_COMMAND_H_
#define _START_CAM_COMMAND_H_

#include "common/common.h"
#include "ViewModel/viewmodel.h"
#include <string>
#include <memory>

class StartCameraCommand : public Command{
private:
    std::shared_ptr<ViewModel> viewmodel;
public:
    StartCameraCommand(std::shared_ptr<ViewModel> vm);
    //~StartCameraCommand();
    void exec();

};

#endif//_START_CAM_COMMAND_H_
