#ifndef _CLOSE_CAM_COMMAND_H_
#define _CLOSE_CAM_COMMAND_H_

#include "common/common.h"
#include "ViewModel/viewmodel.h"
#include <string>
#include <memory>

class CloseCameraCommand : public Command{
private:
    std::shared_ptr<ViewModel> viewmodel;
public:
    CloseCameraCommand(std::shared_ptr<ViewModel> vm);
    //~CloseCameraCommand();
    void exec();

};

#endif //_CLOSE_CAM_COMMAND_H_
