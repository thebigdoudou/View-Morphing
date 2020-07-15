#include "app/app.h"
#include <QApplication>
#include <QStyleFactory>
#include <QStyle>
#include <QFile>
#include <QTranslator>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/images/white.css");
    file.open(QFile::ReadOnly);
    QString qss = QLatin1String(file.readAll());
    qApp->setStyleSheet(qss);
    qApp->setPalette(QPalette(QColor("#F0F0F0")));

    app w;
    w.run();

    return a.exec();
}
