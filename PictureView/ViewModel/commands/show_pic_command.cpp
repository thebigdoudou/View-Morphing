#include "show_pic_command.h"
#include "ViewModel/viewmodel.h"
#include <iostream>
ShowPicCommand::ShowPicCommand(std::shared_ptr<ViewModel> vm):viewmodel(vm){

}

void ShowPicCommand::exec()
{
    std::cout<<"ShowPicCommand::exec()"<<std::endl;
    int ID = std::static_pointer_cast<IntParameters, Parameters>(Command::params)->getvalue();
    std::cout<<"ShowPicCommand::exec() ID:"<<ID<<std::endl;
    viewmodel->exec_show_pic_command(ID);
}

