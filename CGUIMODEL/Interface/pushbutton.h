#ifndef CPUSHBUTTON_H
#define CPUSHBUTTON_H
#include <QPushButton>
#include <QCoreApplication>
#include <QPainter>

class CPushButton : public QPushButton
{
    Q_OBJECT
public:
    CPushButton(QWidget *parent = 0)
        : QPushButton(parent) { this->setFixedSize(QSize(28, 24));}
    ~CPushButton() {}

};
#endif // CPushButton_H
