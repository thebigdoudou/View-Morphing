#ifndef _SAVE_CAM_FRAME_COMMAND_H_
#define _SAVE_CAM_FRAME_COMMAND_H_

#include "common/common.h"
#include "ViewModel/viewmodel.h"
#include <string>
#include <memory>

class SaveCamFrame : public Command{
private:
    std::shared_ptr<ViewModel> viewmodel;
public:
    SaveCamFrame(std::shared_ptr<ViewModel> vm);
    //~SaveCamFrame();
    void exec();

};

#endif //_SAVE_CAM_FRAME_COMMAND_H_
