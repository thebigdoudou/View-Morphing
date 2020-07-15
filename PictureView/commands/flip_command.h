#ifndef FLIP_COMMAND_H
#define FLIP_COMMAND_H

#include "command.h"
#include "ViewModel/viewmodel.h"
#include <string>
#include <memory>

class FlipCommand : public Command{
private:
    std::shared_ptr<ViewModel> viewmodel;
public:
    FlipCommand(std::shared_ptr<ViewModel> vm):viewmodel(vm){}
    ~FlipCommand(){}
    void exec();
};


#endif // FLIP_COMMAND_H
