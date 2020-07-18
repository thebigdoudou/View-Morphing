#ifndef _UPDATE_CAM_FRAME_COMMAND_H_
#define _UPDATE_CAM_FRAME_COMMAND_H_

#include "common/common.h"
#include "ViewModel/viewmodel.h"
#include <string>
#include <memory>

class UpdateCamFrame : public Command{
private:
    std::shared_ptr<ViewModel> viewmodel;
public:
    UpdateCamFrame(std::shared_ptr<ViewModel> vm);
    //~UpdateCamFrame();
    void exec();

};

#endif//_UPDATE_CAM_FRAME_COMMAND_H_
