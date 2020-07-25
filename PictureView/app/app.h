#ifndef APP_H
#define APP_H
#include <Model/model.h>
#include <memory>
#include <view/mainwindow.h>
#include <ViewModel/viewmodel.h>

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
