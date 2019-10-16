#include "baseWin.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
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

#include "HttpClient.h"

void progress_callback(void *userdata, double download_speed, double remaining_time, double progress_percentage)
{
    //qDebug()<<download_speed<<remaining_time<<progress_percentage;
    int hours = 0, minutes = 0, seconds = 0;

    if (download_speed != 0)
    {
        hours = remaining_time / 3600;
        minutes = (remaining_time - hours * 3600) / 60;
        seconds = remaining_time - hours * 3600 - minutes * 60;
    }

    string unit = "B";
    if (download_speed > 1024 * 1024 * 1024)
    {
        unit = "G";
        download_speed /= 1024 * 1024 * 1024;
    }
    else if (download_speed > 1024 * 1024)
    {
        unit = "M";
        download_speed /= 1024 * 1024;
    }
    else if (download_speed > 1024)
    {
        unit = "kB";
        download_speed /= 1024;
    }

    char speedFormat[15] = { 0 };
    char timeFormat[10] = { 0 };
    char progressFormat[8] = { 0 };

#ifdef _WIN32
    sprintf_s(speedFormat, sizeof(speedFormat), "%.2f%s/s", download_speed, unit.c_str());
    sprintf_s(timeFormat, sizeof(timeFormat), "%02d:%02d:%02d", hours, minutes, seconds);
    sprintf_s(progressFormat, sizeof(progressFormat), "%.2f", progress_percentage);
#else
    sprintf(speedFormat, "%.2f%s/s", download_speed, unit.c_str());
    sprintf(timeFormat, "%02d:%02d:%02d", hours, minutes, seconds);
    sprintf(progressFormat, "%.2f", progress_percentage);
#endif

    //AnyClass *eg = static_cast<AnyClass *>(userdata);
    //eg->func(speedFormat, timeFormat, progressFormat);
}


size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    LOG(INFO) << "I am world!";
    return 0;
}
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
        QString path = "C:/Users/Administrator/Documents/JinDun/Recording/2019_10_15/0d9fdf17-e5f2-46c3-82f4-8f6c8cf06c26_05338228119.wav";
        QString getUUid = path.section("/",7,7).split(".")[0].split("_")[0];
        qDebug()<<"getUUid:"<<getUUid;
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

   // HttpClient::getInstance()->HttpGet("https://curl.haxx.se/download/curl-7.66.0.zip","curl-7.66.0.zip", NULL, NULL);
    QFile qss(":/Qss/stylesheet.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
    CMainWin w;
    w.initGUI();
    w.show();

    return a.exec();
}
