#ifndef COMMON_H
#define COMMON_H
#include <opencv2/opencv.hpp>
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
#endif // COMMON_H
