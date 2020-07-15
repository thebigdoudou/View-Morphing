#include "frame.h"
#include "ui_frame.h"

Frame::Frame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Frame)
{
    ui->setupUi(this);
    isClicked = false;
    setMouseTracking(true);
}

Frame::~Frame()
{
    delete ui;
}


void Frame::on_pushButton_clicked()
{
    this->close();
}

void Frame::on_pushButton_2_clicked()
{
    if(isClicked) {
        QMessageBox::information(this, tr("当前在描点模式，无法导入图片!"), tr("当前在描点模式，无法导入图片!"));
        return;
    }
    QString filename ;
    filename = QFileDialog::getOpenFileName(this, tr("Open Image"), " ", tr("Image Files (*.png *.jpg *.bmp)"));
    QImage *img=new QImage, *scaledimg=new QImage;
    if(!(img->load(filename))) {
        QMessageBox::information(this, tr("Fail to open the image!"), tr("Fail to open the image!"));
        delete img;
        return;
    }
    int Owidth = img->width(), Oheight = img->height();
    int Fwidth,Fheight;
    ui->label->setGeometry(20, 200, 400, 300);
    int Mul;
    if(Owidth / 400 >= Oheight / 300) Mul = Owidth / 400;
    else Mul = Oheight / 300;
    Fwidth = Owidth / Mul;
    Fheight = Oheight / Mul;
    *scaledimg = img->scaled(Fwidth, Fheight, Qt::KeepAspectRatio);
    ui->label->setPixmap (QPixmap::fromImage(*scaledimg));
}

void Frame::on_pushButton_3_clicked()
{
    if(isClicked) {
        QMessageBox::information(this, tr("当前在描点模式，无法导入图片!"), tr("当前在描点模式，无法导入图片!"));
        return;
    }
    QString filename ;
    filename = QFileDialog::getOpenFileName(this, tr("Open Image"), " ", tr("Image Files (*.png *.jpg *.bmp)"));
    QImage *img=new QImage, *scaledimg=new QImage;
    if(!(img->load(filename))) {
        QMessageBox::information(this, tr("Fail to open the image!"), tr("Fail to open the image!"));
        delete img;
        return;
    }
    int Owidth = img->width(), Oheight = img->height();
    int Fwidth,Fheight;
    ui->label_2->setGeometry(440, 200, 400, 300);
    int Mul;
    if(Owidth / 400 >= Oheight / 300) Mul = Owidth / 400;
    else Mul = Oheight / 300;
    Fwidth = Owidth / Mul;
    Fheight = Oheight / Mul;
    *scaledimg = img->scaled(Fwidth, Fheight, Qt::KeepAspectRatio);
    ui->label_2->setPixmap (QPixmap::fromImage(*scaledimg));
}

void Frame::on_pushButton_4_clicked()
{
    isClicked = !isClicked;
    if(isClicked) {
        ui->pushButton_4->setText("描点模式");
    }
    else ui->pushButton_4->setText("导入模式");
}

void Frame::mousePressEvent(QMouseEvent *e)
{
    if(!isClicked) return;
    else if(e->button() == Qt::LeftButton) {
        if(e->y() > 200 && e->y() < 500) {
            if(e->x() > 20 && e->x() < 420) {
                position_1.push_back(std::make_pair(e->x() - 20, e->y() - 200));
                this->repaint();
            }
            else if(e->x() > 440 && e->x() < 840) {
                position_2.push_back(std::make_pair(e->x() - 440, e->y() - 200));
                this->repaint();
            }
            else return;
        }
        else return;
    }
}

void Frame::mouseMoveEvent(QMouseEvent *e)
{
    QPoint currentPosition = e->pos();
//    QString result = "";
//    std::vector<std::pair<int, int>>::iterator iter;
//    for(iter = position_1.begin(); iter != position_1.end(); iter++) {
//        result += "\n" + QString::number(iter->first) + ", " + QString::number(iter->second) + "\n";
//    }
    ui->showPosition->setText("当前位置：(" + QString("%1, %2").arg(currentPosition.x()).arg(currentPosition.y()));
}

void Frame::paintEvent(QPaintEvent *e)
{
    //QImage image(1000,1000,QImage::Format_ARGB32);
    //painter.begin(&image);
    painter.begin(this);
    painter.setBrush(Qt::red);
    std::vector<std::pair<int, int>>::iterator iter;
    for(iter = position_1.begin(); iter != position_1.end(); iter++) {
        painter.drawEllipse(iter->first + 20, iter->second + 200, 5, 5);
    }
    for(iter = position_2.begin(); iter != position_2.end(); iter++) {
        painter.drawEllipse(iter->first + 440, iter->second + 200, 5, 5);
    }
    painter.end();
    //ui->label->setPixmap(QPixmap::fromImage(image));
    update();
}
