#ifndef UPDATEVIEWNOTIFICATION_H
#define UPDATEVIEWNOTIFICATION_H
#include<common/common.h>
#include<view/mainwindow.h>

class UpdateViewNotification: public Notification{
private:
    std::shared_ptr<MainWindow> view;
public:
    UpdateViewNotification(std::shared_ptr<MainWindow> v):view(v){}
    void exec(){
        view->update();
    }
};
#endif // UPDATEVIEWNOTIFICATION_H
