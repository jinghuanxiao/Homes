#include "baseWin.h"
#include <QApplication>
#include <QFile>
#include <QLabel>
#include <string>
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include<WinSock2.h>
#include<Windows.h>

#include "curl/curl.h"

#include "glog/logging.h"

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
    google::InitGoogleLogging("smartvoice");
    google::SetLogDestination(google::INFO,"loginfo");
    FLAGS_alsologtostderr = true;
    FLAGS_logbufsecs = 0;
    LOG(INFO) << "I am world!";
    google::ShutdownGoogleLogging();
//    CURL *curl = curl_easy_init();
//    if(curl) {
//      CURLcode res;
//      curl_easy_setopt(curl, CURLOPT_URL, "http://www.baidu.com");
//      res = curl_easy_perform(curl);
//      curl_easy_cleanup(curl);
//    }
    QFile qss(":/Qss/stylesheet.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
    CMainWin w;
    w.initGUI();
    w.show();

    return a.exec();
}
