#include "baseTopBar.h"
#include "iconhelper.h"
#include <QSpacerItem>
CBaseTopBar::CBaseTopBar(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(25);
    title_label = new QLabel();
    m_clostBtn = new CPushButton();
    m_minBtn = new CPushButton();
    m_maxBtn = new CPushButton();

    layout = new QHBoxLayout();
    title_label->setObjectName(QString::fromUtf8("_titleLbl"));
    m_clostBtn->setToolTip(tr("close"));
    m_minBtn->setToolTip(tr("min"));
    m_maxBtn->setToolTip(tr("max"));
    layout->addWidget(title_label);
    layout->addStretch();

    layout->addWidget(m_minBtn);
    layout->addWidget(m_maxBtn);
    layout->addWidget(m_clostBtn);
    layout->setSpacing(0);
    layout->setMargin(1);

    setLayout(layout);
    connect(m_clostBtn, SIGNAL(clicked()), this, SIGNAL(closeWin()));
    connect(m_minBtn, SIGNAL(clicked()), this, SIGNAL(minWin()));
    connect(m_maxBtn, SIGNAL(clicked()), this, SIGNAL(maxWin()));
}
void CBaseTopBar::setTitleText(QString title)
{
    title_label->setText(title);
}
