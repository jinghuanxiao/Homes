#include "baseWin.h"
#include "frameless_helper.h"
#include <QDesktopWidget>


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifdef Q_OS_WIN32
#include <WinSock2.h>
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#endif

CBaseWidget::CBaseWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    initFrameless();
    m_topBar = new CBaseTopBar();
    m_topBar->setObjectName("WinTopBar");
    m_topBar->setTitleText("world");

    m_winContent = new QWidget();
    m_winContent->setObjectName("winContent");
    m_winContent->setStyleSheet("#_popwid{background-color:#204160; color:white;}");

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setSpacing(0);
    vLayout->addWidget(m_topBar);
    vLayout->addWidget(m_winContent);


    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setMargin(0);
    mainLayout->addLayout(vLayout);
    setLayout(mainLayout);
    connect(m_topBar, &CBaseTopBar::closeWin, this,&CBaseWidget::closeWin);
    connect(m_topBar, &CBaseTopBar::maxWin, this,&CBaseWidget::maxWin);
    connect(m_topBar, &CBaseTopBar::minWin, this,&CBaseWidget::minWin);

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
void CBaseWidget::initGUI()
{

}

