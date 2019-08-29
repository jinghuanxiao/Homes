#ifndef BASETOPBAR_H
#define BASETOPBAR_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QHBoxLayout>
#include "pushbutton.h"


class CBaseTopBar : public QWidget
{
    Q_OBJECT
 public:
    CBaseTopBar(QWidget *parent = 0);
    ~CBaseTopBar() {}

    void setTitleText(QString title);
private:

    QLabel *title_label;
    CPushButton *m_clostBtn;
    CPushButton *m_maxBtn;
    CPushButton *m_minBtn;
    QHBoxLayout *layout;

signals:
    void closeWin();
    void minWin();
    void maxWin();
};
#endif // CBaseTopBar_H
