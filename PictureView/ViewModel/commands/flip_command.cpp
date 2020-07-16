#include "flip_command.h"

void FlipCommand::exec()
{
    int type = std::static_pointer_cast<IntParameters, Parameters>(Command::params)->getvalue();
    viewmodel->exec_flip_command(type);
}

