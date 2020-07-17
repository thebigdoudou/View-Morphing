#ifndef COMMON_H
#define COMMON_H
#include <opencv2/opencv.hpp>
#include <memory>
#include <string>
class Parameters
{
public:
    Parameters(){};
};


class PathParameters: public Parameters{
private:
    std::string path;
public:
    PathParameters(std::string _path):path(_path){
    }
    std::string get_path(){
        return path;
    }
};

class IntParameters :public Parameters {
private:
    int value;
public:
    IntParameters(int v) :value(v) {}
    void setvalue(int v) { value = v; }
    int getvalue() { return value; }
};

class Notification
{
private:


public:
    Notification(){};
    virtual void exec() = 0;
};

class Command
{
protected:
    std::shared_ptr<Parameters> params;
public:
    Command(){};
    void set_parameters(std::shared_ptr<Parameters> parameters){
        params = parameters;
    }

    virtual void exec() = 0;
};


#endif // COMMON_H
