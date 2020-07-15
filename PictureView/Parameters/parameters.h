#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <string>

class Parameters
{
public:
    Parameters();
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
#endif // PARAMETERS_H
