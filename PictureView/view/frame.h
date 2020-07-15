#ifndef FRAME_H
#define FRAME_H

#include <QFrame>
#include <vector>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QImage>
#include <QLabel>
#include <QPainter>

namespace Ui {
class Frame;
}

class Frame : public QFrame
{
    Q_OBJECT

public:
    explicit Frame(QWidget *parent = nullptr);
    ~Frame();
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Frame *ui;
    bool isClicked;
    std::vector<std::pair<int, int>> position_1;
    std::vector<std::pair<int, int>> position_2;
    QPainter painter;
};

#endif // FRAME_H
