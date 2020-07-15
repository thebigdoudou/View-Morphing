#ifndef APP_H
#define APP_H

#include <memory>
class ViewModel;
class MainWindow;
class Model;
class Notification;
class OpenFileCommand;

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
