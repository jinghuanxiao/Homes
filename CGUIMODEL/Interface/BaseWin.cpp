#include "baseWin.h"
#include "frameless_helper.h"
#include <QDesktopWidget>


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifdef Q_OS_WIN32
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#endif

CBaseWidget::CBaseWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    initFrameless();
    message_title = new CBaseTopBar();
    message_title->setTitleText("world");
    content_label = new QLabel();
    content_label->setWordWrap(true);
    content_label->setObjectName("_contentlbl");
    content_label->setFixedWidth(this->width() - 20);
    content_label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    QWidget *wid = new QWidget();
    wid->setObjectName("_popwid");
    wid->setStyleSheet("#_popwid{background-color:#204160; color:white;}");

    QVBoxLayout *v_layout = new QVBoxLayout();
    v_layout->setSpacing(0);
    v_layout->addWidget(message_title);
    v_layout->addWidget(wid);


    QVBoxLayout *v2 = new QVBoxLayout();
    wid->setLayout(v2);
    v2->addWidget(content_label);
    content_label->setText("hello");

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->setMargin(0);
    main_layout->addLayout(v_layout);
    setLayout(main_layout);
    connect(message_title, &CBaseTopBar::closeWin, this,&CBaseWidget::closeWin);
    connect(message_title, &CBaseTopBar::maxWin, this,&CBaseWidget::maxWin);
    connect(message_title, &CBaseTopBar::minWin, this,&CBaseWidget::minWin);

}

CBaseWidget::~CBaseWidget()
{

}
void CBaseWidget::closeWin()
{
    this->close();
}
void CBaseWidget::minWin()
{
    showMinimized();
}

void CBaseWidget::maxWin()
{
    if (!isFullScreen() && !isMaximized())
    {
        showMaximized();
    }else{
        showNormal();
    }
}

void CBaseWidget::initFrameless()
{
    FramelessHelper *pHelper = new FramelessHelper(this);
    pHelper->activateOn(this);  //激活当前窗体
    pHelper->setTitleHeight(this->height()*0.1);  //设置窗体的标题栏高度
    pHelper->setWidgetMovable(true);  //设置窗体可移动
    pHelper->setWidgetResizable(true);  //设置窗体可缩放
}

