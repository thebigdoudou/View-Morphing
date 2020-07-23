#ifndef APP_H
#define APP_H

#include <memory>
#include <view/mainwindow.h>
#include <ViewModel/viewmodel.h>
#include <Model/model.h>

class app
{
public:
    app();
    void run();
private:
    std::shared_ptr<MainWindow> view;
    std::shared_ptr<Model> model;
    std::shared_ptr<ViewModel> viewmodel;
};

#endif // APP_H
