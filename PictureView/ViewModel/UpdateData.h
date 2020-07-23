#ifndef UPDATEDISPLAYDATANOTIFICATION_H
#define UPDATEDISPLAYDATANOTIFICATION_H
#include<ViewModel/viewmodel.h>
#include<common/common.h>

class UpdateData:public Notification {
private:
    std::shared_ptr<ViewModel> viewmodel;
public:
    UpdateData(std::shared_ptr<ViewModel> vm):viewmodel(vm){};
    void exec(){
        viewmodel->notified();
    }
};
#endif // UPDATEDISPLAYDATANOTIFICATION_H
