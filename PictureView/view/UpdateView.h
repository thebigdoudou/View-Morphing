#ifndef UPDATEVIEWNOTIFICATION_H
#define UPDATEVIEWNOTIFICATION_H
#include<common/common.h>
#include<view/mainwindow.h>

class UpdateView: public Notification{
private:
    std::shared_ptr<MainWindow> view;
public:
    UpdateView(std::shared_ptr<MainWindow> v):view(v){}
    void exec(){
        view->update();
    }
};
#endif // UPDATEVIEWNOTIFICATION_H
