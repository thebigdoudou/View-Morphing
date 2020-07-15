#ifndef SHOW_PIC_COMMAND_H
#define SHOW_PIC_COMMAND_H
#include "command.h"
#include <memory>
#include <string>
class ViewModel;


class ShowPicCommand : public Command
{
private:
    std::shared_ptr<ViewModel> viewmodel;
public:
    ShowPicCommand(std::shared_ptr<ViewModel> vm);
    void exec();
};

#endif // SHOW_PIC_COMMAND_H
