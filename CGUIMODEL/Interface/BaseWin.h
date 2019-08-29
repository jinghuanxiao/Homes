#ifndef BASEWIN_H
#define BASEWIN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QBitmap>
#include <QTextEdit>
#include "basetopBar.h"

class CBaseWidget : public QWidget
{
    Q_OBJECT

public:
    CBaseWidget(QWidget *parent = 0);
    ~CBaseWidget();
private:
    CBaseTopBar *message_title;
    QLabel *content_label;
private slots:
    void closeWin();
    void minWin();
    void maxWin();

private:
    void initFrameless();
};

#endif // BASEWIN_H
