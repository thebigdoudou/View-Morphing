#ifndef UPDATEDISPLAYDATANOTIFICATION_H
#define UPDATEDISPLAYDATANOTIFICATION_H
#include<ViewModel/viewmodel.h>
#include<common/common.h>
class Notification;

class UpdateDisplayDataNotification:public Notification {
private:
    std::shared_ptr<ViewModel> viewmodel;
public:
    UpdateDisplayDataNotification(std::shared_ptr<ViewModel> vm):viewmodel(vm){};
    void exec(){
        viewmodel->notified();
    }
};
#endif // UPDATEDISPLAYDATANOTIFICATION_H
