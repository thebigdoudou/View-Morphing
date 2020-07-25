#ifndef MODEL_H
#define MODEL_H
#include <dlib/opencv.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <memory>
#include <string>
#include <list>
#include <QFileInfo>
#include <QMap>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <common/common.h>


class Model
{
private:

    int CntNum=0;
    int CurrentID=-1;
    QStringList FileSuffix;
    QStringList FileFilter;
    std::list<cv::Mat> images;
    QMap<int, QFileInfo> PhotoMap;
    bool CameraIsOn;
    bool FaceDectectIsOn;
//    QCamera *camera;
//    QCameraViewfinder *viewfinder;
//    QCameraImageCapture *imageCapture;
    cv::Mat CameraFrame;
    cv::VideoCapture videoCapture_1;
    std::shared_ptr<Notification> update_display_data_notification;
    dlib::frontal_face_detector detector;
    dlib::shape_predictor sp;
    void read_img(std::string path);
    void line_one_face_detection(cv::Mat &img, std::vector<dlib::full_object_detection> fs);
public:
    Model(){
//        camera=new QCamera;
//        viewfinder=new QCameraViewfinder;
//        imageCapture=new QCameraImageCapture(camera);
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
        CameraIsOn=0;
        FaceDectectIsOn=0;
        detector = dlib::get_frontal_face_detector();
        dlib::deserialize("C:/Users/15888/Desktop/PhotoView/Model/shape_predictor_68_face_landmarks.dat") >> sp;
    }
    void set_update_display_data_notification(std::shared_ptr<Notification> notification);
    cv::Mat& getImg();
    QMap<int,QFileInfo>& getPhotoMap();
//    cv::Mat& getOrigin();
    cv::Mat& getListImg(int x);
    void notify();
    bool open_file(std::string path);
    bool show_pic(int ID);
    bool save_file(std::string path);
    bool save_fileID(std::string path, int ID);
    bool flip(int type);
    bool flipID(int type, int ID);
    bool del_pic();
    bool rotate(int angle);
    bool rotateID(int angle, int ID);
    bool StartCamera();//开启摄像头
    bool CloseCamera(); //关闭摄像头
    bool StartFaceDetect();
    bool CloseFaceDetect();
    bool UpdateCamFrame();
    bool SaveCamPic(std::string path);
};

#endif // MODEL_H
