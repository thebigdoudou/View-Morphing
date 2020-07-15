#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <memory>
#include "view/mainwindow.h"
#include "ViewModel/viewmodel.h"
class ViewModel;
class MainWindow;

class Notification
{
private:


public:
    Notification();
    virtual void exec() = 0;
};



class UpdateDisplayDataNotification: public Notification{
private:
    std::shared_ptr<ViewModel> viewmodel;
public:
    UpdateDisplayDataNotification(std::shared_ptr<ViewModel> vm):viewmodel(vm){}
    void exec(){
        viewmodel->notified();
    }
};


class UpdateViewNotification: public Notification{
private:
    std::shared_ptr<MainWindow> view;
public:
    UpdateViewNotification(std::shared_ptr<MainWindow> v):view(v){}
    void exec(){
        view->update();
    }
};


#endif // NOTIFICATION_H
