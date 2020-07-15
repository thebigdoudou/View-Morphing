#ifndef MODEL_H
#define MODEL_H

#include <opencv2/opencv.hpp>
#include <common/common.h>
#include <memory>
#include <string>
#include <list>
#include <QFileInfo>
#include <QMap>
class ViewModel;
class Notification;

class Model
{
private:

    int CntNum=0;
    int CurrentID=-1;
    QStringList FileSuffix;
    QStringList FileFilter;
    std::list<cv::Mat> images;
    QMap<int, QFileInfo> PhotoMap;
    std::shared_ptr<Notification> update_display_data_notification;
    void read_img(std::string path);
public:
    Model(){
        FileSuffix = (QStringList() << "png" <<
                                  "jpg" << "jpeg" << "bmp" <<
                                  "tif" << "tiff" << "webp" <<
                                  "gif" << "jp2" << "dds" <<
                                  "xpm" << "pnm" << "ppm" <<
                                  "pgm" << "wbmp" << "ico" <<
                                  "icns");

        FileFilter = (QStringList() << "*.png" <<
                                  "*.jpg" << "*.jpeg" << "*.bmp" <<
                                  "*.tif" << "*.tiff" << "*.webp" <<
                                  "*.gif" << "*.jp2" << "*.dds" <<
                                  "*.xpm" << "*.pnm" << "*.ppm" <<
                                  "*.pgm" << "*.wbmp" << "*.ico" <<
                                  "*.icns");
        CntNum=0;
        CurrentID=-1;
    }
    void set_update_display_data_notification(std::shared_ptr<Notification> notification);
    void open_file(std::string path);
    cv::Mat& getImg();
    QMap<int,QFileInfo>& getPhotoMap();
//    cv::Mat& getOrigin();
    cv::Mat& getListImg(int x);
    void notify();
    void show_pic(int ID);
    void save_file(std::string path);
    void save_fileID(std::string path, int ID);
    void flip(int type);
    void flipID(int type, int ID);
//	void reset();
    void rotate(int angle);
    void rotateID(int angle, int ID);
    QImage Mat2QImage(cv::Mat const& src);
    cv::Mat QImage2Mat(QImage const& src);
};

#endif // MODEL_H
