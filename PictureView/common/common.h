#ifndef COMMON_H
#define COMMON_H
#include <opencv2/opencv.hpp>
#include <memory>
#include<any>
#include<functional>
using namespace std;

typedef std::function<bool(std::any&&)> Command;
class Notification
{
private:

public:
    Notification(){};
    virtual void exec() = 0;
};
#endif // COMMON_H
