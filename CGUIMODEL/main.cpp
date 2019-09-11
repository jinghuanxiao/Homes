#include "baseWin.h"
#include <QApplication>
#include <QFile>
#include <QLabel>
class CMainWin:public CBaseWidget
{
public:
    CMainWin(QWidget *parent = 0) {}
public:
    void initGUI(){
        QVBoxLayout *vLayout = new QVBoxLayout();
        QLabel *text = new QLabel("hello");
        vLayout->addWidget(text);
        m_winContent->setLayout(vLayout);
    }

private:

};
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss(":/Qss/stylesheet.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
    CMainWin w;
    w.initGUI();
    w.show();

    return a.exec();
}
